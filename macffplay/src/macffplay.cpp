#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <queue>

extern "C" {
#include <rockchip/vpu_api.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/mem.h>
#include "bytestream.h"

#include "rockchip_x11_gles.h"
}

#include "macffplay.h"
#include "ffplay.h"
#include "native-state-x11.h"

NativeStateX11 avWindow;
int screenWidth = -1;
int screenHeight = -1;
int fullscreen = 0; // starting not fullscreen
int windowWidth = 1920; // initial values used to
int windowHeight = 1080; // determine window size (smaller than values)

struct VpuCodecContext* vpu_ctx = NULL;
RK_S32 fileSize =0, pkt_size =0;
RK_S32 ret = 0, frame_count=0;
DecoderOut_t    decOut;
VideoPacket_t access_unit;
VideoPacket_t* pkt =NULL;
DecoderOut_t *pOut = NULL;
VPU_FRAME *frame = NULL;
RK_S64 fakeTimeUs =0;
RK_U8* pExtra = NULL;
RK_U32 extraSize = 0;
int extraSent = 0;
DecoderFormat_t fmt;

typedef struct vpu_buf_t {
    // mem part
    VPUMemLinear_t *vpu_mem;
    int size;
    int dma_fd;
    // frame specifics
    OMX_RK_VIDEO_CODINGTYPE videoformat;
    int frameformat;
    int width;
    int height;
    int aligned_width;
    int aligned_height;
} vpu_buf_t;

#define N_VPUBUFS 8

vpu_display_mem_pool* vpu_display_pool=NULL;
int vpu_display_pool_count = 0;
vpu_buf_t* mems[N_VPUBUFS];
std::queue<vpu_buf_t*> free_queue;

AVBSFContext *AVbsf = NULL;

void decodeYUV420SP(int *rgb, unsigned char *yuv420sp, int width, int height, int aligned_width, int aligned_height) {
    int frameSize = aligned_width * aligned_height;
    int j, yp, uvp, u, v, i, y, y1192, r, g, b, rgbp;

    for (j = 0, yp = 0, rgbp = 0; j < height; j++) {
        uvp = frameSize + (j >> 1) * aligned_width, u = 0, v = 0;
        yp = j * aligned_width;
        for (i = 0; i < width; i++, yp++, rgbp++) {
            y = (0xff & ((int) yuv420sp[yp])) - 16;
            if (y < 0) {
                y = 0;
            }
            if ((i & 1) == 0) {
                v = (0xff & yuv420sp[uvp++]) - 128;
                u = (0xff & yuv420sp[uvp++]) - 128;
            }

            y1192 = 1192 * y;
            r = (y1192 + 1634 * v);
            g = (y1192 - 833 * v - 400 * u);
            b = (y1192 + 2066 * u);

            if (r < 0) {
                r = 0;
            } else if (r > 262143) {
                r = 262143;
            }
            if (g < 0) {
                g = 0;
            } else if (g > 262143) {
                g = 262143;
            }
            if (b < 0) {
                b = 0;
            } else if (b > 262143) {
                b = 262143;
            }

            rgb[rgbp] = 0xff000000 | ((r << 6) & 0xff0000) | ((g >> 2) & 0xff00)
                        | ((b >> 10) & 0xff);
        }
    }
}

int write_truecolor_tga( int* data, int width, int height, int number ) {
    char filename[256];
    sprintf( filename, "frame.%d.tga", number );
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) return 0;

    printf("write %d frame(tga) data to %s\n", number, filename );
    char header[ 18 ] = { 0 }; // char = byte
    header[ 2 ] = 2; // truecolor
    header[ 12 ] = width & 0xFF;
    header[ 13 ] = (width >> 8) & 0xFF;
    header[ 14 ] = height & 0xFF;
    header[ 15 ] = (height >> 8) & 0xFF;
    header[ 16 ] = 24; // bits per pixel

    fwrite((const char*)&header, 1, sizeof(header), fp);
    int x,y;
    for (y = height -1; y >= 0; y--)
        for (x = 0; x < width; x++)
        {
            char b = (data[x+(y*width)] & 0x0000FF);
            char g = (data[x+(y*width)] & 0x00FF00) >> 8;
            char r = (data[x+(y*width)] & 0xFF0000) >> 16;
            putc((int)(r & 0xFF),fp);
            putc((int)(g & 0xFF),fp);
            putc((int)(b & 0xFF),fp);
        }

    static const char footer[ 26 ] =
        "\0\0\0\0" // no extension area
        "\0\0\0\0" // no developer directory
        "TRUEVISION-XFILE" // yep, this is a TGA file
        ".";
    fwrite((const char*)&footer, 1, sizeof(footer), fp);

    fclose(fp);
    return 1;
}

extern "C" int hybris_codec_decode(void* vpHybrisCodec, AVCodecContext *avctx, AVFrame *picture, int *got_picture_ptr, const AVPacket *avpkt) {
    if(!vpu_ctx) return -1;

    int ret = 0;
    AVPacket filter_packet = { 0 };
    AVPacket filtered_packet = { 0 };

    if (AVbsf) {
        if ((ret = av_packet_ref(&filter_packet, avpkt)) < 0) {
            ///INFO("av_packet_ref failed");
            return -1;
        } else if ((ret = av_bsf_send_packet(AVbsf, &filter_packet)) < 0) {
            ///INFO("av_bsf_send_packet failed");
            av_packet_unref(&filter_packet);
            return ret;
        } else if ((ret = av_bsf_receive_packet(AVbsf, &filtered_packet)) < 0) {
            ///INFO("av_bsf_receive_packet failed");
            return ret;
        } else avpkt = &filtered_packet;
    }

    AVPacket packet;
    memcpy(&packet,avpkt,sizeof(AVPacket));

    if(!extraSent) {
        extraSent++;

        unsigned char *data = NULL;
        unsigned int pkt_size = 0;
        data = AVbsf->par_out->extradata;
        pkt_size = AVbsf->par_out->extradata_size;

        if (pkt->data ==NULL) {
            pkt->data = (RK_U8*)(malloc)(pkt_size);
            if (pkt->data ==NULL) {
                ERROR("malloc() error\n");
                return -1;
            }
            pkt->capability = pkt_size;
        }
        if (pkt->capability <((RK_U32)pkt_size)) {
            pkt->data = (RK_U8*)(realloc)((void*)(pkt->data), pkt_size);
            if (pkt->data ==NULL) {
                ERROR("realloc() error\n");
                return -1;
            }
            pkt->capability = pkt_size;
        }
        memcpy(pkt->data,data,pkt_size);
        pkt->size = pkt_size;
        pkt->dts = packet.dts;
        pkt->pts = packet.pts;
        pkt->nFlags = VPU_API_DEC_INPUT_SYNC;

        ///INFO("IN vpu_ctx->decode_sendstream(codecdata)");
        if((ret = vpu_ctx->decode_sendstream(vpu_ctx, pkt)) != 0) {
            ERROR("vpu_ctx->decode_sendstream(codecdata) failed");
            return -1;
        }
        ///INFO("OUT vpu_ctx->decode_sendstream(codecdata)");
    }

    *got_picture_ptr = 0;
    av_frame_unref(picture);

    unsigned char *data = NULL;
    unsigned int pkt_size = 0;
    data = packet.data;
    pkt_size = packet.size;

    if (pkt->data ==NULL) {
        pkt->data = (RK_U8*)(malloc)(pkt_size);
        if (pkt->data ==NULL) {
            ERROR("malloc() error\n");
            return -1;
        }
        pkt->capability = pkt_size;
    }
    if (pkt->capability <((RK_U32)pkt_size)) {
        pkt->data = (RK_U8*)(realloc)((void*)(pkt->data), pkt_size);
        if (pkt->data ==NULL) {
            ERROR("realloc() error\n");
            return -1;
        }
        pkt->capability = pkt_size;
    }
    memcpy(pkt->data,data,pkt_size);
    pkt->size = pkt_size;
    pkt->dts = packet.dts;
    pkt->pts = packet.pts;
    pkt->nFlags = VPU_API_DEC_INPUT_SYNC;

    ///INFO("IN vpu_ctx->decode_sendstream()");
    if((ret = vpu_ctx->decode_sendstream(vpu_ctx, pkt)) != 0) {
        ERROR("vpu_ctx->decode_sendstream() failed");
        return -1;
    }
    ///INFO("OUT vpu_ctx->decode_sendstream()");

    {
        DecoderOut_t dec_out;
        VPU_FRAME vpu_frame;
        VPUMemLinear_t vpu_mem;
        memset (&dec_out, 0, sizeof (DecoderOut_t));
        memset (&vpu_frame, 0, sizeof (VPU_FRAME));
        dec_out.data = (RK_U8*)&vpu_frame;

        ///INFO("IN vpu_ctx->decode_getframe()");
        if ((ret = vpu_ctx->decode_getframe (vpu_ctx, &dec_out)) < 0) {
            if( ret != VPU_API_EOS_STREAM_REACHED ) {
                INFO("VPU_API_EOS_STREAM_REACHED");
                return -1;
            }
            ERROR("vpu_ctx->decode_getframe() failed");
            return -1;
        } else {
            ///INFO("OUT vpu_ctx->decode_getframe()");

            if(dec_out.size != 0) {
                *got_picture_ptr = 1;
                avctx->frame_number++;

                ///INFO("FRAME vpu_ctx->decode_getframe()");
                memcpy( &vpu_mem, &vpu_frame.vpumem,sizeof(vpu_mem));
                vpu_buf_t* mem = mems[vpu_mem.index];
                /*
                if(!(avctx->frame_number % 100)) {
                    int* pARGB = (int*)malloc(
                        sizeof(int)*mem->width*mem->height );
                        decodeYUV420SP(pARGB, (RK_U8*)(vpu_frame.vpumem.vir_addr),
                	mem->width, mem->height,
                	mem->aligned_width, mem->aligned_height);
                    write_truecolor_tga( pARGB, mem->width, mem->height,
                			    avctx->frame_number ) ;
                    free(pARGB);
                }
                */
                g_displayHandler->obtainMessage(RENDER_DISPLAY,vpu_mem.index,
                                                0)->sendToTarget();

                picture->pkt_dts = packet.dts;
                picture->pts = packet.pts;

                if(!avctx->has_b_frames) av_frame_set_pkt_pos(picture, avpkt->pos);
                if(!picture->sample_aspect_ratio.num)
                    picture->sample_aspect_ratio = avctx->sample_aspect_ratio;
                if(!picture->width) picture->width = avctx->width;
                if(!picture->height) picture->height = avctx->height;
                if(picture->format == AV_PIX_FMT_NONE) picture->format = avctx->pix_fmt;
            }
        }
    }

    return avpkt->size;
}

extern "C" int hybris_codec_flush(void* pHybrisCodec, AVCodecContext *avctx) {
    int ret = 0;
    if(!vpu_ctx) return -1;
    ret = vpu_ctx->flush (vpu_ctx);
    return ret;
}

int init_bsf(AVCodecContext *avctx ) {
    const char *filter_name = avctx->codec_id == AV_CODEC_ID_HEVC ?
                              "hevc_mp4toannexb" : "h264_mp4toannexb";
    const AVBitStreamFilter *filter;
    int ret;

    if (AVbsf) return -1;

    filter = av_bsf_get_by_name(filter_name);
    if (!filter) return 0;

    ret = av_bsf_alloc(filter, &AVbsf);
    if (ret < 0) return 0;

    ret = avcodec_parameters_from_context(AVbsf->par_in, avctx);
    if (ret < 0) return 0;

    AVbsf->time_base_in = avctx->time_base;

    ret = av_bsf_init(AVbsf);
    if (ret < 0) return 0;

    return -1;
}

extern "C" void* hybris_codec_open(AVCodecContext *avctx, enum AVCodecID codec_id, int width, int height, uint8_t*  pExtraData, int extraDataSize, int profile, int ptsinvalid )
{
    int ret = vpu_open_context(&vpu_ctx);
    if (ret || (vpu_ctx==NULL)) {
        ERROR("vpu_open_context failed, ret = %x", ret);
        return 0;
    }

    AVbsf = NULL;
    VPU_VIDEO_CODINGTYPE videoCoding = VPU_VIDEO_CodingUnused;
    switch(codec_id) {
    case AV_CODEC_ID_MPEG4:
    case AV_CODEC_ID_MSMPEG4V3:
        videoCoding = VPU_VIDEO_CodingMPEG4;
        break;
    case AV_CODEC_ID_H264:
        videoCoding = VPU_VIDEO_CodingAVC;
        init_bsf(avctx);
        break;
    case AV_CODEC_ID_HEVC:
        videoCoding = VPU_VIDEO_CodingHEVC;
        init_bsf(avctx);
        break;
    default:
        ERROR("codec_id (%x) not supported!", codec_id);
        hybris_codec_close(0);
        return 0;
        break;
    }
    vpu_ctx->videoCoding = (OMX_RK_VIDEO_CODINGTYPE)videoCoding;
    vpu_ctx->codecType = CODEC_DECODER;
    vpu_ctx->width = width;
    vpu_ctx->height = height;
    vpu_ctx->no_thread = 0;
    vpu_ctx->enableparsing = 1;

    ///if ((ret = vpu_ctx->init(vpu_ctx, pExtraData, extraDataSize))!=0) { extraSent++; 
    if ((ret = vpu_ctx->init(vpu_ctx, NULL, 0))!=0) {
        ERROR("vpu_ctx->init() failed, ret = %x", ret);
        hybris_codec_close(0);
        return 0;
    }

    vpu_ctx->control (vpu_ctx, VPU_API_DEC_GETFORMAT, &fmt);
    /*
    INFO("Format input vpu: pixelfmt:%d, aligned_width:%d, aligned_height:%d, stride:%d, sizeimage:%d",
            (int)fmt.format,
            fmt.aligned_width, fmt.aligned_height, fmt.aligned_stride,
            fmt.aligned_frame_size);
    */
    int vpu_size = fmt.aligned_frame_size;
    if((vpu_display_pool = open_vpu_memory_pool()) == NULL ) {
        ERROR("create_vpu_memory_pool_allocator() failed, ret = %x", ret);
        hybris_codec_close(0);
        return 0;
    }
    vpu_ctx->control(vpu_ctx,VPU_API_SET_VPUMEM_CONTEXT,(void*)
                     vpu_display_pool);

    VPU_SYNC sync;
    sync.flag = 0;
    /* If no buffers is ready, DONT block the dequeue operation */
    vpu_ctx->control(vpu_ctx, VPU_API_SET_OUTPUT_BLOCK, (void *)&sync);

    int i;
    for (i = 0; i < N_VPUBUFS; i++) {
    VPUMemLinear_t *vpu_mem =
        (VPUMemLinear_t*)malloc(sizeof(VPUMemLinear_t));
        if( !vpu_mem )  {
            ERROR("malloc() failed");
            hybris_codec_close(0);
            return 0;
        }

        VPUMemLinear_t temp_vpu_mem;
        /* Create vpumem from mpp/libvpu included mvc data */
        VPUMallocLinearOutside (&temp_vpu_mem, vpu_size);
        memcpy( vpu_mem, &temp_vpu_mem, sizeof (VPUMemLinear_t) );
        vpu_mem->index = vpu_display_pool_count;

        ret = vpu_display_pool->commit_vpu (vpu_display_pool, vpu_mem);
        /* Release the old buffer reference in the other memory group */
        VPUFreeLinear (&temp_vpu_mem);
        if (ret > 0) {
            vpu_display_pool->inc_used (vpu_display_pool, vpu_mem);
        }

        vpu_buf_t* vpu_buf = mems[i] = (vpu_buf_t*)malloc(sizeof(vpu_buf_t ) );
        if( vpu_buf == NULL ) {
            ERROR("malloc() failed");
            hybris_codec_close(0);
            return 0;
        }

        vpu_buf->vpu_mem = vpu_mem;
        vpu_buf->size = vpu_mem->size;
        vpu_buf->dma_fd = VPUMemGetFD(vpu_mem);
        vpu_buf->videoformat = vpu_ctx->videoCoding ;
        vpu_buf->frameformat = fmt.format;
        vpu_buf->width = fmt.width;
        vpu_buf->height = fmt.height;
        vpu_buf->aligned_width = fmt.aligned_width;
        vpu_buf->aligned_height = fmt.aligned_height;

        free_queue.push( mems[i] );
        vpu_display_pool_count++;
    }

    for (i = 0; i < N_VPUBUFS; i++)  {
    VPUFreeLinear(mems[i]->vpu_mem);
    }

    memset(&access_unit, 0, sizeof(VideoPacket_t));
    pkt = &access_unit;
    pkt->data = NULL;
    pkt->pts = VPU_API_NOPTS_VALUE;
    pkt->dts = VPU_API_NOPTS_VALUE;

    // reduce dimensions to fit in X11 display
    while(width>=windowWidth||height>=windowHeight) {
        // after this width & height arent real video dimensions anymore
        width /= 2;
        height /= 2;
    }
    g_displayHandler->obtainMessage(INIT_DISPLAY,width,height)->sendToTarget();

    return (void*)-1;
}

extern "C" void hybris_codec_close( void* vpHybrisCodec ) {
    VideoPacket_t pkt;
    RK_S32 is_eos = 0;
    pkt.size = 0;
    pkt.data = NULL;
    pkt.nFlags = VPU_API_DEC_OUTPUT_EOS;
    vpu_ctx->decode_sendstream (vpu_ctx, &pkt);
    vpu_ctx->control (vpu_ctx, VPU_API_DEC_GET_EOS_STATUS, &is_eos);

    if( vpu_ctx ) vpu_close_context(&vpu_ctx);
    vpu_ctx = NULL;

    while(!free_queue.empty()) free_queue.pop();
    for (int i = 0; i <vpu_display_pool_count ; i++) {
        vpu_buf_t* mem = mems[i];
        mems[i] = NULL;
        if (mem) free (mem);
    }
    vpu_display_pool_count = 0;

    if( vpu_display_pool ) close_vpu_memory_pool(vpu_display_pool);
    vpu_display_pool = NULL;

    if (AVbsf) av_bsf_free(&AVbsf);
    AVbsf = NULL;

    return;
}

#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#define NB_ENABLE 0
#define NB_DISABLE 1

void advance_cursor() {
    static int pos=0;
    char cursor[4]= {'/','-','\\','|'};
    printf("%c\b", cursor[pos]);
    fflush(stdout);
    pos = (pos+1) % 4;
}

void nonblock(int state)
{
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state==NB_ENABLE) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    } else if (state==NB_DISABLE) {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

sp<Handler> g_mainHandler;
sp<Handler> g_displayHandler;
void* g_mainthread = NULL;
sp<Thread> g_decoderThread = NULL;

int mac_argc = 0;
char** mac_argv = NULL;

class DecoderThread : public Thread {
    virtual void run() {
        ///INFO("DecoderThread START");

        ffplay(mac_argc, mac_argv, windowWidth, windowHeight );
        g_mainHandler->obtainMessage(DECODING_DONE)->sendToTarget();

        ///INFO("DecoderThread END");
    }
};

class StdinThread : public Thread {
    virtual void run() {
        ///INFO("StdinThread START");

        nonblock(NB_ENABLE);
        while(!ffplay_stopped()) {
            unsigned char key = (unsigned char)fgetc(stdin);
            ///INFO("KEY = '%c' = %x", key, key);
            if( key == ' ' || key == 'f' )
                g_displayHandler->obtainMessage(TOGGLE_FULLSCREEN)->
                sendToTarget();
            ffplay_key(key);
        }
        nonblock(NB_DISABLE);

        ///INFO("StdinThread END");
    }
};

class MainHandler : public Handler {
public:
    virtual void handleMessage(const sp<Message>& msg) {
        switch (msg->what) {
        case DECODERTHREAD_START:
            ///INFO("DECODERTHREAD_START");
            g_decoderThread->start();
            break;

        case DECODING_DONE:
            ///INFO("DECODING_DONE");
            Looper::myLooper()->quit();
            break;
        }
    }
};

NativeState::WindowProperties restore_properties;
NativeState::WindowProperties cur_properties;
void *m_dpy, *m_window, *m_invisibleCursor;

bool resize_window(int width, int height) {
    bool request_fullscreen = (width == -1 && height == -1);

    int vid = XVisualIDFromVisual(XDefaultVisual((Display*)avWindow.display(),
                                  DefaultScreen(avWindow.display())));
    NativeState::WindowProperties properties(width, height,
            request_fullscreen, vid);
    NativeState::WindowProperties cur_properties;
    avWindow.window(cur_properties);

    if ((cur_properties.fullscreen == properties.fullscreen &&
            cur_properties.width > 0 && cur_properties.height > 0) ||
            (cur_properties.width == properties.width &&
             cur_properties.height == properties.height)) return true;

    if (!avWindow.create_window(properties)) {
        ERROR("Error: Couldn't create native window!\n");
        return false;
    }
    avWindow.visible(true);

    avWindow.window(cur_properties);
    windowWidth = cur_properties.width;
    windowHeight = cur_properties.height ;
    if(request_fullscreen) {
        windowWidth = screenWidth;
        windowHeight = screenHeight;
    }

    // invisible cursor
    m_dpy = avWindow.display();
    m_window = avWindow.window(cur_properties);

    // first, free previous cursor
    if(m_invisibleCursor) {
        XUndefineCursor((Display*)m_dpy, (Window)m_window);
        XFreeCursor((Display*)m_dpy, (Cursor)m_invisibleCursor);
        m_invisibleCursor = 0;
    }

    Pixmap bitmapNoData;
    XColor black;
    static char noData[] = { 0,0,0,0,0,0,0,0 };
    black.red = black.green = black.blue = 0;

    bitmapNoData = XCreateBitmapFromData((Display*)m_dpy,
                                         (Drawable)m_window, noData, 8, 8);
    m_invisibleCursor = (void*)XCreatePixmapCursor((Display*)m_dpy,
                        bitmapNoData, bitmapNoData, &black, &black, 0, 0);
    XFreePixmap((Display*)m_dpy, bitmapNoData);
    XDefineCursor((Display*)m_dpy,(Window)m_window,
                  (Cursor)m_invisibleCursor);

    return true;
}

class DisplayHandler : public Handler {
public:
    virtual void handleMessage(const sp<Message>& msg) {
        Screen*  scrn;
        unsigned long event;


        switch (msg->what) {
        case INIT_DISPLAY:
            windowWidth = msg->arg1;
            windowHeight = msg->arg2;

            avWindow.init_display();
            scrn = DefaultScreenOfDisplay(avWindow.display());
            screenHeight = scrn->height;
            screenWidth  = scrn->width;

            resize_window(windowWidth,windowHeight);

            g_displayHandler->sendMessageDelayed(
                g_displayHandler->obtainMessage(X11_INPUT),0);
            break;

        case TOGGLE_FULLSCREEN:
            rockchip_x11_gles_destory(NULL);
            if(fullscreen) {
                windowWidth = restore_properties.width ;
                windowHeight = restore_properties.height ;
                resize_window(windowWidth,windowHeight);
                fullscreen = 0;
            } else {
                avWindow.window(restore_properties);
                windowWidth = windowHeight = -1;
                resize_window(windowWidth,windowHeight);
                fullscreen = 1;
            }
            break;

        case X11_INPUT:
            if(ffplay_stopped()) return;

            event = avWindow.handle_event();
            if(event) {
                if((event)>0x80000000) {
                    unsigned int resize_width = event & 0x7fff;
                    unsigned int resize_height = (event >> 16) & 0x7fff;

                    if(!fullscreen) {
                        windowWidth = resize_width;
                        windowHeight = resize_height;
                        resize_window(windowWidth,windowHeight);
                    }
                } else {
                    unsigned char key = (unsigned char)event;
                    ///INFO("X11KEY = '%c' = %x", key, key);
                    if( key == ' ' || key == 'f' )
                        g_displayHandler->obtainMessage(TOGGLE_FULLSCREEN)->
                        sendToTarget();
                    ffplay_key(key);
                }
                g_displayHandler->sendMessageDelayed(
                    g_displayHandler->obtainMessage(X11_INPUT),0);
            } else g_displayHandler->sendMessageDelayed(
                    g_displayHandler->obtainMessage(X11_INPUT),10);
            break;

        case RENDER_DISPLAY:
            advance_cursor();

            vpu_buf_t* mem = (vpu_buf_t*)mems[msg->arg1];
            int videoWidth = mem->width;
            int videoHeight = mem->height;
            float windowRatio = ((float)windowWidth) / ((float)windowHeight);
            float videoRatio = ((float)videoWidth) / ((float)videoHeight);
            long int xoffset = 0, yoffset = 0, renderWidth, renderHeight;

            if( windowRatio > videoRatio ) {
                // windowHeight is OK & ~ videoHeight, renderWidth < windowWidth
                renderHeight = windowHeight;
                renderWidth = (windowHeight * videoWidth) / videoHeight;
                yoffset = 0; // windowHeight is OK and ~ videoHeight
                xoffset = (windowWidth - renderWidth) / 2;
            } else {
                // windowWidth is OK & ~ videoWidth, renderHeight < windowHeight
                renderWidth = windowWidth;
                renderHeight = (windowWidth * videoHeight) / videoWidth;
                xoffset = 0;
                yoffset = (windowHeight - renderHeight) / 2;
            }

            rockchip_x11_gles_PutSurface(
                (void*)avWindow.display(),
                (void*)avWindow.window(cur_properties),
                0,0,mem->width,mem->height,
                xoffset,yoffset,renderWidth,renderHeight,
                NULL,0,0,
                mem->dma_fd,
                mem->aligned_width,
                mem->aligned_height );

            VPUFreeLinear(mem->vpu_mem);
            break;
        }
    }
};

int main(int argc, char *argv[]) {
    mac_argc = argc;
    mac_argv = argv;

    // render to local display
    setenv("DISPLAY", ":0.0", 1);

    g_mainthread = (void*)pthread_self();
    Looper::prepare();

    sp<Handler> mainHandler = new MainHandler();
    g_mainHandler = mainHandler;
    sp<Handler> displayHandler = new DisplayHandler();
    g_displayHandler = displayHandler;

    sp<DecoderThread> decoderThread = new DecoderThread();
    g_decoderThread = decoderThread;

    g_mainHandler->obtainMessage(DECODERTHREAD_START)->sendToTarget();

    sp<StdinThread> stdinThread = new StdinThread();
    stdinThread->start();

    Looper::loop();

    return 0;
}
