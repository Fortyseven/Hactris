#ifndef __CURRENTPIECE_H__
#define __CURRENTPIECE_H__

#include "Main.h"

/**********************************************************************
 * CurrentPiece is the piece currently being controlled by the player.
 **********************************************************************/

class Bucket;

/*************************************************/
class CurrentPiece
{
    private:
        Bucket *bucket;
        Delay *bakeDelay;
    public:
        int rotation;
        int type;
        int xpos,ypos;

        Piece curpiece;

        CurrentPiece(Bucket *bucket);

        void reset();
        void draw();
        void update();

        void bakeMe();

        void setType(int type);

        int canMoveLeft();
        int canMoveRight();

        int canMoveDown();
        void doMoveDown(int force);

        void resetBake();

        void doRotateCCW();
        int canPieceExist(Piece *testpiece);
        Piece *rotatePiece(int rotate, int rot_type);
};


#endif
