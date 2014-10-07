#ifndef __BUCKET_H__
#define __BUCKET_H__

/**********************************************************************
 * "Bucket" represents the playing field where the pieces go to die.
 **********************************************************************/


#define BUCKET_W    10
#define BUCKET_H	24

#define BUCKET_X	(VID_WIDTH/2) - ((BUCKET_W * TILE_SIZE) / 2)
#define BUCKET_Y	(TILE_SIZE * 2)


typedef struct {
    int filled;
    int type;
} TBucketBlock;

class Bucket
{
    public:
        TBucketBlock block[BUCKET_H][BUCKET_W];

        Bucket();
        void reset();
        int getBlockType(int x, int y);
        void update();

    private:
        void moveAndShiftDown(int line);
};
#endif
