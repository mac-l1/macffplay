/*
 * Copyright © 2010-2011 Linaro Limited
 * Copyright © 2013 Canonical Ltd
 *
 * This file is part of the glmark2 OpenGL (ES) 2.0 benchmark.
 *
 * glmark2 is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * glmark2 is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * glmark2.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *  Alexandros Frantzis
 */
#include "native-state-x11.h"
#include "log.h"

#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <cstring>
#include <cctype>

/******************
 * Public methods *
 ******************/

NativeStateX11::~NativeStateX11()
{
    if (xdpy_)
    {
        if (xwin_)
            XDestroyWindow(xdpy_, xwin_);

        XCloseDisplay(xdpy_);
    }
}

bool
NativeStateX11::init_display()
{
    if (!xdpy_)
        xdpy_ = XOpenDisplay(NULL);

    return (xdpy_ != 0);
}

void*
NativeStateX11::display()
{
    return (void*)xdpy_;
}

bool
NativeStateX11::create_window(WindowProperties const& properties)
{
    static const char *win_name("macffplay");

    if (!xdpy_) {
        ERROR("Error: X11 Display has not been initialized!\n");
        return false;
    }

    /* Recreate an existing window only if it has actually been resized */
    if (xwin_) {
        if (properties_.fullscreen != properties.fullscreen ||
                (properties.fullscreen == false &&
                 (properties_.width != properties.width ||
                  properties_.height != properties.height)))
        {
            XDestroyWindow(xdpy_, xwin_);
            xwin_ = 0;
        }
        else
        {
            return true;
        }
    }

    /* Set desired attributes */
    properties_.fullscreen = properties.fullscreen;
    properties_.visual_id = properties.visual_id;

    if (properties_.fullscreen) {
        /* Get the screen (root window) size */
        XWindowAttributes window_attr;
        XGetWindowAttributes(xdpy_, RootWindow(xdpy_, DefaultScreen(xdpy_)),
                             &window_attr);
        properties_.width = window_attr.width;
        properties_.height = window_attr.height;
    }
    else {
        properties_.width = properties.width;
        properties_.height = properties.height;
    }

    XVisualInfo vis_tmpl;
    XVisualInfo *vis_info = 0;
    int num_visuals;

    /* The X window visual must match the supplied visual id */
    vis_tmpl.visualid = properties_.visual_id;
    vis_info = XGetVisualInfo(xdpy_, VisualIDMask, &vis_tmpl,
                              &num_visuals);
    if (!vis_info) {
        ERROR("Error: Could not get a valid XVisualInfo!\n");
        return false;
    }

    /*
    INFO("Creating XWindow W: %d H: %d VisualID: 0x%x",
         properties_.width, properties_.height, vis_info->visualid);
    */

    /* window attributes */
    XSetWindowAttributes attr;
    unsigned long mask;
    Window root = RootWindow(xdpy_, DefaultScreen(xdpy_));

    attr.background_pixel = 0;
    attr.border_pixel = 0;
    attr.colormap = XCreateColormap(xdpy_, root, vis_info->visual, AllocNone);
    attr.event_mask = KeyPressMask|ExposureMask|StructureNotifyMask;
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    xwin_ = XCreateWindow(xdpy_, root, 0, 0, properties_.width, properties_.height,
                          0, vis_info->depth, InputOutput,
                          vis_info->visual, mask, &attr);

    XFree(vis_info);

    if (!xwin_) {
        ERROR("Error: XCreateWindow() failed!\n");
        return false;
    }

    /* set hints and properties */
    Atom fs_atom = None;
    if (properties_.fullscreen) {
        fs_atom = XInternAtom(xdpy_, "_NET_WM_STATE_FULLSCREEN", True);
        if (fs_atom == None)
            INFO("Warning: Could not set EWMH Fullscreen hint.\n");
    }
    if (fs_atom != None) {
        XChangeProperty(xdpy_, xwin_,
                        XInternAtom(xdpy_, "_NET_WM_STATE", True),
                        XA_ATOM, 32, PropModeReplace,
                        reinterpret_cast<unsigned char*>(&fs_atom),  1);
    }
    else {
        bool force_pos = false;
        XSizeHints* hint = XAllocSizeHints();

        hint->flags |= PSize | (force_pos ? PPosition : 0);
        hint->x = 100;
        hint->y = 100;
        hint->width = properties_.width;
        hint->height = properties_.height;
        hint->max_width = 0;
        hint->max_height = 0;
        hint->flags |= PAspect;
        hint->min_aspect.x = hint->width;
        hint->min_aspect.y = hint->height;
        hint->max_aspect.x = hint->width;
        hint->max_aspect.y = hint->height;
        // Set min height/width to 4 to avoid off-by-one errors.
        hint->flags |= PMinSize;
        hint->min_width = hint->min_height = 4;
        // Will use the top/left corner of the window for positioning, instead
        // of the top/left corner of the client. _NET_MOVERESIZE_WINDOW could be
        // used to get a different reference point, while keeping gravity.
        hint->flags |= PWinGravity;
        hint->win_gravity = CenterGravity;

        XSetWMProperties(xdpy_, xwin_, NULL, NULL,
                         NULL, 0, hint, NULL, NULL);
        //NULL, 0, &sizehints, NULL, NULL);
        XFree(hint);
    }

    /* Set the window name */
    XStoreName(xdpy_ , xwin_,  win_name);

    /* Gracefully handle Window Delete event from window manager */
    Atom wmDelete = XInternAtom(xdpy_, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(xdpy_, xwin_, &wmDelete, 1);

    return true;
}

void*
NativeStateX11::window(WindowProperties& properties)
{
    properties = properties_;
    return (void*)xwin_;
}

void
NativeStateX11::visible(bool visible)
{
    if (visible)
        XMapWindow(xdpy_, xwin_);
}

#define KEY_BUFF_SIZE 256
static char     key_buff[KEY_BUFF_SIZE];

#define MP_KEY_MODIFIER_SHIFT 1
#define MP_KEY_MODIFIER_CTRL 2
#define MP_KEY_MODIFIER_ALT 4
#define MP_KEY_MODIFIER_META 8

static int get_mods(unsigned int state)
{
    int modifiers = 0;
    if (state & ShiftMask) modifiers |= MP_KEY_MODIFIER_SHIFT;
    if (state & ControlMask) modifiers |= MP_KEY_MODIFIER_CTRL;
    if (state & Mod1Mask) modifiers |= MP_KEY_MODIFIER_ALT;
    if (state & Mod4Mask) modifiers |= MP_KEY_MODIFIER_META;
    return modifiers;
}

unsigned long
NativeStateX11::handle_event()
{
    XEvent event;

    if (!XPending(xdpy_))
        return 0;

    XNextEvent(xdpy_, &event);

    if (event.type == KeyPress) {
        XKeyEvent      *xke = (XKeyEvent *)&event;
        KeySym          ks;
        char           *tmp;

        int count = XLookupString(xke, key_buff, KEY_BUFF_SIZE, &ks, NULL);
        key_buff[count] = '\0';

        if (count == 0) {
            tmp = XKeysymToString(ks);
            if (tmp) strcpy(key_buff, tmp);
            else strcpy(key_buff, "");
        }
        if( strlen(key_buff) == 1 ) {
            switch (get_mods(event.xkey.state)) {
            case 0:
                for ( char* p = key_buff; *p; ++p) *p = tolower(*p);
                break;
            case MP_KEY_MODIFIER_SHIFT:
                for ( char* p = key_buff; *p; ++p) *p = toupper(*p);
                break;
            default:
                return 0;
                break;
            }
        } else return 0;
        return (unsigned long)key_buff[0];
    } else if (event.type == ConfigureNotify) {
        XConfigureEvent xce = event.xconfigure;
        return ((unsigned long)xce.height<<16)|((unsigned long)xce.width)
               |0x80000000;
    } else if (event.type == ClientMessage) {
        /* Window Delete event from window manager */
        return 0;
    }

    return 0;
}
