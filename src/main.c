#include <gb/gb.h>
#include "res/tilesets/background_window/cherry_wall.c"
#include "res/tilemaps/first_map.c"
#include "includes/gameboy_front_tilemap.h"
#include "includes/gameboy_front_tileset.h"


void set_background(){
    //Set background in tile data memory
    set_bkg_data(0, 5, CHERRY_WALL);
    //set background in background map memory
    set_bkg_tiles(0, 0, 20, 18, FIRST_MAP);
}

void set_sprite(){
    set_bkg_data(0, GAMEBOY_FRONT_TILESET_TILE_COUNT, GAMEBOY_FRONT_TILESET);
    set_bkg_tiles(0, 0, 
    GAMEBOY_FRONT_TILEMAP_WIDTH,
    GAMEBOY_FRONT_TILEMAP_HEIGHT,
    GAMEBOY_FRONT_TILEMAP);
}

void main(void) {
    set_background();
    set_sprite();
    SHOW_BKG;
}
