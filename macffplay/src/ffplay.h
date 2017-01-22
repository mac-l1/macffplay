#ifndef __MACFFPLAY_H
#define __MACFFPLAY_H

extern "C" {

    int ffplay(int argc, char **argv, int scrWidth, int scrHeight);
    void ffplay_quit(void);
    void ffplay_key(unsigned char key);
    int ffplay_stopped(void);

}

#endif
