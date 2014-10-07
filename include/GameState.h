#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <allegro.h>
#include <Bucket.h>
#include <Pieces.h>
#include <CurrentPiece.h>
class GameState
{
    public:
        Bucket		    bucket;
        CurrentPiece	*currentpiece;
        BITMAP		    *bucketbg = NULL;

        GameState();
        void init();
        void done();
        void draw_bucket();
        void draw();
};

#endif // GAMESTATE_H
