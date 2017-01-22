/*
 * Copyright © 2016 Rockchip Co., Ltd.
 * Jacob Chen, <jacob2.chen@rock-chips.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _ROCKCHIP_X11_GLES_H_
#define _ROCKCHIP_X11_GLES_H_

#include <va/va_backend.h>
#include <stdbool.h>
///#include "common.h"
///#include "rockchip_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

VAStatus rockchip_x11_gles_PutSurface (
    ///VADisplay dpy,
    ///VASurfaceID surface,
    void *display, /* X Display */
    void *draw, /* X Drawable */
    short srcx,
    short srcy,
    unsigned short srcw,
    unsigned short srch,
    short destx,
    short desty,
    unsigned short destw,
    unsigned short desth,
    VARectangle *cliprects, /* client supplied destination clip list */
    unsigned int number_cliprects, /* number of clip rects in the clip list */
    unsigned int flags, /* PutSurface flags */
    int obj_surface_bo_dma_fd,
    int obj_surface_width,
    int  obj_surface_height
);

bool rockchip_x11_gles_init(VADriverContextP ctx);
void rockchip_x11_gles_destory(VADriverContextP ctx);

#ifdef __cplusplus
}
#endif

#endif
