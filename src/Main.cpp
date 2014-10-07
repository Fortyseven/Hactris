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
    int depth;

    allegro_init();
    depth = desktop_color_depth();

    if (depth == 0) {
        depth = 16;
    }

    set_color_depth(depth);

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, VID_WIDTH, VID_HEIGHT, 0, 0)) {
        std::string fname(allegro_error);
        error(fname);
        exit(-1);
    }

    buf = create_bitmap(VID_WIDTH, VID_HEIGHT);

    install_timer();
    install_keyboard();
    //install_mouse();

    timer_init();
    srand(time(NULL));

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
void error(std::string message)
{
    allegro_message(message.c_str());
    exit(-1);
}

/*--------------------------------------------------------*/
BITMAP *load_bitmap_check(std::string filepath)
{
    BITMAP *bmp = load_bitmap(filepath.c_str(), NULL);

    if (!bmp) {
        error( "Could not load" + filepath);
    }

    return bmp;
}

/*--------------------------------------------------------*/
int main()
{
    GameState gs;

    init();
    gs.init();

    BITMAP *wallpaper; // = create_bitmap(VID_WIDTH, VID_HEIGHT);

    wallpaper = load_bitmap_check("images/wallpaper.tga");

    tiles[0].image = load_bitmap_check("images/bg.tga");
    tiles[1].image = load_bitmap_check("images/block1.tga");
    tiles[2].image = load_bitmap_check("images/block2.tga");
    tiles[3].image = load_bitmap_check("images/block3.tga");
    tiles[4].image = load_bitmap_check("images/block4.tga");
    tiles[5].image = load_bitmap_check("images/block5.tga");
    tiles[6].image = load_bitmap_check("images/block6.tga");
    tiles[7].image = load_bitmap_check("images/block7.tga");

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
