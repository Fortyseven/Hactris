#ifndef __PIECES_H__
#define __PIECES_H__

#define PIECE_W	    4
#define PIECE_H	    4
#define MAX_PIECES	7

typedef struct {
    int blocks[PIECE_H][PIECE_W];
    int	width;
    int	height;
} Piece;

extern Piece pieces[];

#endif
