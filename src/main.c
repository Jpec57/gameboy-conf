#include <gb/gb.h>
#include "res/tilesets/background_window/cherry_wall.c";
#include "res/tilemaps/first_map.c";

void main(void) {
    set_bkg_data(0, 5, CHERRY_WALL);
    set_bkg_tiles(0, 0, 20, 18, FIRST_MAP);
    SHOW_BKG;
}