#ifndef __MAIN_H__
#define __MAIN_H__


#include <allegro.h>
#include <string>

#ifdef USE_IRRKLANG
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
using namespace irrklang;
extern ISoundEngine *sound;
#endif

#include "Timer.h"

#define VID_WIDTH	640
#define VID_HEIGHT	480

#define TILE_SIZE	16

#define MAX_TILETYPE	8

#include "Pieces.h"
#include "CurrentPiece.h"
#include "Bucket.h"

typedef struct {
    BITMAP *image;
} TTileType;


extern BITMAP	 *buf;
extern TTileType tiles[];

extern void error(std::string message);

#endif
