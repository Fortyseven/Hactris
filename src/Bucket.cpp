#include "Main.h"

Bucket::Bucket()
{
	reset();
}

void Bucket::reset()
{
	for(int y=0; y < BUCKET_H; y++) {
		for(int x=0; x < BUCKET_W; x++) {
			block[y][x].type = 0; //rand() % 7 + 1;
			block[y][x].filled = 0;
		}
	}
}

int Bucket::getBlockType(int x, int y)
{
	if ((x < 0) || (x >= BUCKET_W)) return -1;
	if ((y < 0) || (y >= BUCKET_H)) return -1;

	return this->block[y][x].type;
}

void Bucket::update()
{
	// Check for a 'hactris'...*cough*

	for(int y = (BUCKET_H-1); y >= 0; y--) {
		int hactris = true;
		for (int x = 0; x < BUCKET_W; x++) {
			// An empty space?  Can't possibly be a...hactris...
			if (!block[y][x].type) {
				hactris = false;
				break;
			}
		}
		if (hactris) {
			moveAndShiftDown(y);
		}

		if (key[KEY_F]) {
			while(key[KEY_F]);
			moveAndShiftDown(BUCKET_H-1);
		}
	}
}

void Bucket::moveAndShiftDown(int line)
{
	memset(block[line], 0, sizeof(TBucketBlock) * BUCKET_W);
	for(int y = line-1; y >= 0; y--) {
		memcpy( block[y+1], block[y], sizeof(TBucketBlock) * BUCKET_W );
	}
#ifdef USE_IRRKLANG
	sound->play2D("sounds/4.wav");
#endif
}
