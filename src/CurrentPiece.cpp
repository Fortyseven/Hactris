#include "CurrentPiece.h"

#define GAME_SPEED 20

/*************************************************/
CurrentPiece::CurrentPiece(Bucket *buck)
{
    this->bucket = buck;
    this->bakeDelay = NULL;
    reset();
}

/*************************************************/
void CurrentPiece::reset()
{
    this->setType( rand() % MAX_PIECES );
    //this->setType( 4 );
    xpos		= (BUCKET_W / 2) - (curpiece.width / 2);
    ypos		= 0;
    rotation	= 0;
}

/*************************************************/
void CurrentPiece::draw()
{
    int t = 0;

    for(int y = 0; y < curpiece.height; y++) {
        for(int x = 0; x < curpiece.width; x++) {
            t = curpiece.blocks[y][x];

            textprintf_ex(buf, font, x * 8, y*8, -1, 0, "%d", t);

            if (t) {
                int newx = x + xpos;
                int newy = y + ypos;

                if ((newx < 0) || (newx >= BUCKET_W)) {
                    continue;
                }
                if ((newy < 0) || (newy >= BUCKET_H)) {
                    continue;
                }

                int xx = BUCKET_X +  (newx * TILE_SIZE);
                int yy = BUCKET_Y +  (newy * TILE_SIZE);

                draw_sprite(buf, tiles[ t ].image, xx,yy);

            }
            /*
            rect(buf,
            	xx,yy,
            	xx+TILE_SIZE,yy+TILE_SIZE,
            	makecol(255,0,255)
            );
            */
        }
    }

    textprintf_ex(buf, font, 30,30, -1, 0, "(%d, %d)", curpiece.width, curpiece.height);
}

/*
	In these two functions, we have to scan along the piece to see if we hit a block, because the
	pieces are 4x4, but the actual physical blocks usually occupy only 3x3, 3x2, or 4x1, etc.
*/
/*************************************************/
int CurrentPiece::canMoveLeft()
{
    for(int y = 0; y < curpiece.height; y++) {
        for(int x = 0; x < curpiece.width; x++) {
            if (curpiece.blocks[y][x] && bucket->getBlockType(xpos+x-1, y+ypos)) {
                return false;
            }
        }
    }

    return true;
}

/*************************************************/
int CurrentPiece::canMoveRight()
{
    for(int y = 0; y < curpiece.height; y++) {
        for(int x = 0; x < curpiece.width; x++) {
            if (curpiece.blocks[y][x] && bucket->getBlockType(x+xpos+1, y+ypos)) {
                return false;
            }
        }
    }

    return true;

}

/*************************************************/
int CurrentPiece::canMoveDown()
{
    for(int y = curpiece.height-1; y >= 0; y--) {
        for (int x = 0; x < curpiece.width; x++) {
            if ((curpiece.blocks[y][x]) && bucket->getBlockType(xpos+x, ypos+y+1)) {
                return false;
            }
        }
    }

    return true;
}

/*************************************************/
void CurrentPiece::setType(int type)
{
    this->type = type;

    Piece *testpiece = rotatePiece(rotation, this->type);

    // Fake the ok

    memcpy(&curpiece, testpiece, sizeof(Piece));
}

/*************************************************/
void CurrentPiece::bakeMe()
{
    for(int y = 0; y < curpiece.height; y++) {
        for(int x = 0; x < curpiece.width; x++) {
            int p = curpiece.blocks[y][x];
            if (p) {
                int yb = ypos + y;
                int xb = xpos + x;

                if (!bucket->getBlockType(xb, yb)) {
                    bucket->block[ yb ][ xb ].type = p;
                }
            }
        }
    }
    reset();
}

/*************************************************/
Piece *CurrentPiece::rotatePiece(int rotate, int rot_type)
{
    static Piece newpiece;

    memset(&newpiece, 0, sizeof(Piece));

    int w = pieces[rot_type].width;
    int h = pieces[rot_type].height;

    switch(rotate % 4) {
        case 1:
            for(int y = 0; y < h; y++) {
                for(int x = 0; x < w; x++ ) {
                    newpiece.blocks[x][h-1-y] = pieces[rot_type].blocks[y][x];
                }
            }
            newpiece.width = h;
            newpiece.height = w;
            break;
        case 2:
            for(int y = 0; y < h; y++) {
                for(int x = 0; x < w; x++ ) {
                    newpiece.blocks[h-1-y][w-1-x] = pieces[rot_type].blocks[y][x];
                }
            }
            newpiece.width = w;
            newpiece.height = h;
            break;
        case 3:
            for(int y = 0; y < h; y++) {
                for(int x = 0; x < w; x++ ) {
                    newpiece.blocks[w-1-x][y] = pieces[rot_type].blocks[y][x];
                }
            }
            newpiece.width = h;
            newpiece.height = w;
            break;
        case 0:
        default:
            memcpy(&newpiece, (void *)&pieces[rot_type], sizeof(Piece));
            break;
    }
    return &newpiece;
}

/*************************************************/
int CurrentPiece::canPieceExist(Piece *testpiece)
{
    for(int y = 0; y < testpiece->height; y++) {
        for(int x = 0; x < testpiece->width; x++) {
            if (testpiece->blocks[y][x] && bucket->getBlockType(xpos+x,ypos+y)) {
                return false;
            }
        }
    }
    return true;
}

/*************************************************/
void CurrentPiece::doRotateCCW()
{
    Piece *testpiece = rotatePiece(this->rotation+1, type);

    /*
    	NOTE: Should we also be testing to see if the piece can be
    	      adjusted along the x-axis?
    */

    if (canPieceExist(testpiece)) {
        memcpy(&curpiece, testpiece, sizeof(Piece));
#ifdef USE_IRRKLANG
        sound->play2D("sounds/turn.wav");
#endif
    } else {
        // Try moving the piece up a little bit
        int oldypos = ypos;
        //ypos -= testpiece->height-1;
        ypos--;
        if (canPieceExist(testpiece)) {
            memcpy(&curpiece, testpiece, sizeof(Piece));
#ifdef USE_IRRKLANG
            sound->play2D("sounds/turn.wav");
#endif
        } else {
            ypos = oldypos;
        }
    }

    this->rotation++;

    return;
}

/*************************************************/
void CurrentPiece::doMoveDown(int force = false)
{
    if (canMoveDown()) {
        ypos++;
    } else {
        if (force) {
            bakeMe();
            return;
        }
        if (!bakeDelay) {
            bakeDelay = new Delay(10);
            return;
        } else 	if (bakeDelay->hasPassed()) {
            bakeMe();
            delete bakeDelay;
            bakeDelay = NULL;
        }
    }
}

/*************************************************/
void CurrentPiece::resetBake()
{
    if (this->bakeDelay) {
        this->bakeDelay->reset();
    }
}

/*************************************************/
void CurrentPiece::update()
{
    static unsigned int last_timer = timer;

    static Delay *keydel = new Delay(7);

    //if (ypos > BUCKET_Y) reset();        // Just in case, but probably not needed

    if (key[KEY_UP]) {
        if (keydel->hasPassed()) {
            resetBake();
            doRotateCCW();
        }
    }

    if (key[KEY_LEFT]) {
        if (keydel->hasPassed())
            if (canMoveLeft()) {
                resetBake();
                xpos--;
            }
    } else if (key[KEY_RIGHT]) {
        if (keydel->hasPassed())
            if (canMoveRight()) {
                resetBake();
                xpos++;
            }
    }

    if (key[KEY_DOWN]) {
        if (keydel->hasPassed()) {
            doMoveDown(true);
        }
    }

    if (timer - last_timer > GAME_SPEED) {
        last_timer = timer;
        doMoveDown();
        return;
    }
}
