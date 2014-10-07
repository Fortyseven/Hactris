#include "Main.h"
#include "GameState.h"

BITMAP *buf;
TTileType tiles[MAX_TILETYPE] = {NULL};

#ifdef USE_IRRKLANG
ISoundEngine *sound = NULL;
#endif

/*--------------------------------------------------------*/
void init()
{
    int depth, res;

    allegro_init();
    depth = desktop_color_depth();

    if (depth == 0) {
        depth = 16;
    }

    set_color_depth(depth);

    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, VID_WIDTH, VID_HEIGHT, 0, 0);
    if (res != 0) {
        allegro_message(allegro_error);
        exit(-1);
    }

    buf = create_bitmap(VID_WIDTH, VID_HEIGHT);

    install_timer();
    install_keyboard();
    install_mouse();

    timer_init();

#ifdef USE_IRRKLANG
    sound = createIrrKlangDevice();
#endif
}
/*--------------------------------------------------------*/
void deinit()
{
    timer_done();
    clear_keybuf();
}

/*--------------------------------------------------------*/

/*-----------------------*/
int main()
{
    GameState gs;

    init();
    gs.init();

    BITMAP *wallpaper; // = create_bitmap(VID_WIDTH, VID_HEIGHT);

    wallpaper = load_bitmap("images/wallpaper.tga", NULL);
    tiles[0].image = load_bitmap("images/bg.tga", NULL);
    tiles[1].image = load_bitmap("images/block1.tga", NULL);
    tiles[2].image = load_bitmap("images/block2.tga", NULL);
    tiles[3].image = load_bitmap("images/block3.tga", NULL);
    tiles[4].image = load_bitmap("images/block4.tga", NULL);
    tiles[5].image = load_bitmap("images/block5.tga", NULL);
    tiles[6].image = load_bitmap("images/block6.tga", NULL);
    tiles[7].image = load_bitmap("images/block7.tga", NULL);

    //sound->play2D("sounds/music.mp3", false);

    while (!key[KEY_ESC]) {
        blit(wallpaper, buf, 0,0, 0,0, VID_WIDTH, VID_HEIGHT);
        gs.draw();
        blit(buf, screen, 0,0, 0,0, VID_WIDTH, VID_HEIGHT);
    }

    deinit();
    gs.done();
    return 0;
}
END_OF_MAIN();
