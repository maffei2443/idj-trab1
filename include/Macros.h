#ifndef MACROS_H
#define MACROS_H

#define INCLUDE_SDL
#include "SDL_include.h"
#include <iostream>

extern int AuxCodeErr;

#ifndef SDL_ABORT_IF_NZERO
    #define SDL_ABORT_IF_NZERO( x ) \
        AuxCodeErr = x; if (AuxCodeErr) myAbort(AuxCodeErr);/*  else //////printf("Ok passed.\n"); */
#endif
#ifndef SDL_ABORT_IF_ZERO
    #define SDL_ABORT_IF_ZERO( x ) \
            SDL_ABORT_IF_NZERO(!(x) )
#endif

void myAbort(int);
#define LOG(x) printf("[Log] "),printf(x);

#endif