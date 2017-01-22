#ifndef __MACPLAYER_H
#define __MACPLAYER_H

#ifdef __cplusplus

#include <mindroid/os/Message.h>
#include <mindroid/os/LooperThread.h>
#include <mindroid/os/Ref.h>
using namespace mindroid;

static const int TMSG_CALLBACK = 10;
static const int RENDER_DISPLAY = 11;
static const int DECODERTHREAD_START = 12;
static const int DECODING_DONE = 13;
static const int TEXTURE_RENDERED = 14;
static const int VIDEO_RESIZED = 15;
static const int KEY_INPUT = 16;
static const int INIT_DISPLAY = 17;
static const int TOGGLE_FULLSCREEN = 18;
static const int X11_INPUT = 19;

struct ThreadMessageCallback
{
    void (*callback)(void *userptr);
    void *userptr;
};

extern void* g_mainthread;
extern sp<Handler> g_mainHandler;
extern sp<Handler> g_displayHandler;

/// the C-part
extern "C" {
#endif

#include <pthread.h>
#include <sched.h>
#include "libavcodec/avcodec.h"
#include "log.h"

static const int DEFAULT_SCHED = SCHED_FIFO;
static const int PRIO_VIDEO = 50;		// video thread pckt to V frame
static const int PRIO_AUDIO = 70;		// audio thread pckt to A frame
static const int PRIO_VIDEOUPDATE = 99;		// V frame rendered to texture
static const int PRIO_DECODING = 80;		// filling A+V queues w pckts
static const int PRIO_DISPLAY = 99;		// main/display thready
static const int PRIO_AUDIOCALLBACK = 90;	// audiocallback thread (SDL)

void* hybris_codec_open(AVCodecContext *avctx,
                        enum AVCodecID codec_id, int width, int height,
                        unsigned char* pExtraData, int extraDataSize,
                        int profile, int ptsinvalid );

void hybris_codec_close(void* vpHybrisCodec);

int hybris_codec_flush(void* pHybrisCodec, AVCodecContext *avctx);

int hybris_codec_decode(void* pHybrisCodec, AVCodecContext *avctx,
                        AVFrame *picture, int *got_picture_ptr,
                        const AVPacket *avpkt);

void setSchedulingParams( int priority );
void printSchedulingParams( void );

#ifdef __cplusplus
}
#endif

#endif
