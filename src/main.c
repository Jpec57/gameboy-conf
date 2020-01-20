#include <gb/gb.h>
#include "includes/gameboy_front_tilemap.h"
#include "includes/gameboy_front_tileset.h"
#include "includes/first_map_tilemap.h"
#include "includes/first_map_tileset.h"
#include "includes/big_map_tilemap.h"


void set_background(){
    //Set background in tile data memory
    set_bkg_data(0, CHERRY_WALL_TILESET_COUNT, CHERRY_WALL);
    //set background in background map memory
    set_bkg_tiles(0, 0, FIRST_MAP_TILEMAP_WIDTH, FIRST_MAP_TILEMAP_HEIGHT, FIRST_MAP);
    SHOW_BKG;
}

void set_created_background(){
    set_bkg_data(0, GAMEBOY_FRONT_TILESET_TILE_COUNT, GAMEBOY_FRONT_TILESET);
    set_bkg_tiles(0, 0, 
    GAMEBOY_FRONT_TILEMAP_WIDTH,
    GAMEBOY_FRONT_TILEMAP_HEIGHT,
    GAMEBOY_FRONT_TILEMAP);
    SHOW_BKG;
}

void set_big_background(){
    set_bkg_data(0, CHERRY_WALL_TILESET_COUNT, CHERRY_WALL);
    set_bkg_tiles(0, 0, 
    BIG_MAP_TILEMAP_WIDTH,
    BIG_MAP_TILEMAP_HEIGHT,
    BIG_TILEMAP);
    SHOW_BKG;
}

void set_too_big_background(){
    set_bkg_data(0, CHERRY_WALL_TILESET_COUNT, CHERRY_WALL);
    set_bkg_tiles(0, 0, 
    TOO_BIG_MAP_TILEMAP_WIDTH,
    TOO_BIG_MAP_TILEMAP_HEIGHT,
    TOO_BIG_TILEMAP);
    SHOW_BKG;
}

void main(void) {
    UINT8 keys;
    
    // set_background();
    // set_created_background(); // gameboy
    set_big_background();
    // set_too_big_background();

    while (1) {
        keys = joypad();

        if (keys & J_UP) scroll_bkg(0, -1);
        if (keys & J_DOWN) scroll_bkg(0, 1);
        if (keys & J_LEFT) scroll_bkg(-1, 0);
        if (keys & J_RIGHT) scroll_bkg(1, 0);

        if (keys & J_START) move_bkg(0, 0);
        //wait for screen to refresh to look smoother
        wait_vbl_done();
    }
}
