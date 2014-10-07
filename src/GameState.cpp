#include "GameState.h"

/*************************************************/
GameState::GameState()
{
    bucket.reset();
    currentpiece = new CurrentPiece(&bucket);
}

/*************************************************/
void GameState::init()
{
    this->bucketbg = create_bitmap(BUCKET_W * 16, BUCKET_H * 16);
}

/*************************************************/
void GameState::done()
{
    if (bucketbg) {
        destroy_bitmap(this->bucketbg);
    }
}

/*************************************************/
void GameState::draw_bucket()
{
    int pvalue = 0;

    //clear_to_color(bucketbg, makecol(255,0,255));

    for (int y = 0; y < BUCKET_H; y++) {
        for (int x = 0; x < BUCKET_W; x++) {
            if ((pvalue = bucket.block[y][x].type) < MAX_TILETYPE) {
                draw_sprite( this->bucketbg,
                             tiles[pvalue].image,
                             (x * TILE_SIZE),
                             (y * TILE_SIZE));
            }
        }
    }
}

/*************************************************/
void GameState::draw()
{
    //clear_to_color(bucketbg, makecol(255,0,255));

    bucket.update();
    draw_bucket();
    //set_color_blender(128,0,0,128);
    set_add_blender(0,0,255,255);
    //set_alpha_blender();
    //draw_lit_sprite(buf, bucketbg, BUCKET_X, BUCKET_Y, makeacol(255,0,0,128));
    draw_trans_sprite(buf, bucketbg, BUCKET_X, BUCKET_Y);
    //draw_sprite(buf, bucketbg, BUCKET_X, BUCKET_Y);
    currentpiece->update();
    currentpiece->draw();

}
