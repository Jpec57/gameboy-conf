#include <gb/gb.h>
#include "includes/gameboy_front_tilemap.h"
#include "includes/gameboy_front_tileset.h"
#include "includes/first_map_tilemap.h"
#include "includes/first_map_tileset.h"
#include "includes/big_map_tilemap.h"
#include "includes/player_sprites.h"
#include "includes/end_message_tilemap.h"

//Ids of the sprite (two needed as we use a 8*16 sprite)
#define PLAYER_SPRITE_L_ID 0
#define PLAYER_SPRITE_R_ID 1

// Sprite animation maching with compressed_imgs/player_sprites.png
UINT8 PLAYER_SPRITE_ANIM_L[] = {
// TAILLE | MIROIR | ID DES TUILES   | DIRECTION
   4,       0,        0 , 4,  0,  8,   // Bas
   4,       0,       12, 16, 12, 20,   // Haut
   4,       0,       24, 28, 24, 32,   // Droite
   4,       1,       26, 30, 26, 34,   // Gauche
};
UINT8 PLAYER_SPRITE_ANIM_R[] = {
// TAILLE | MIROIR | ID DES TUILES   | DIRECTION
   4,       0,        2,  6,  2, 10,   // Bas
   4,       0,       14, 18, 14, 22,   // Haut
   4,       0,       26, 30, 26, 34,   // Droite
   4,       1,       24, 28, 24, 32,   // Gauche
};

//Separating animation with beginning byte
#define PLAYER_DIRECTION_DOWN  0
#define PLAYER_DIRECTION_UP    6
#define PLAYER_DIRECTION_RIGHT 12
#define PLAYER_DIRECTION_LEFT  18

//Global variables with sprite state
UINT8 player_x;
UINT8 player_y;
UINT8 player_direction;
UINT8 player_animation_frame;
UINT8 is_player_walking;

// Retourne un sprite horizontalement (sur l'axe X).
//
// sprite_id: l'id ("nb") du sprite à modifier.
void flip_sprite_horiz(UINT8 sprite_id) {
    set_sprite_prop(sprite_id, get_sprite_prop(sprite_id) | S_FLIPX);
}

// Supprime le retournement horizontal d'un sprite.
//
// sprite_id: l'id ("nb") du sprite à modifier.
void unflip_sprite_horiz(UINT8 sprite_id) {
    set_sprite_prop(sprite_id, get_sprite_prop(sprite_id) & ~S_FLIPX);
}

// Met à jour les tuiles d'un sprite pour l'animer.
//
// sprite_id: l'id ("nb") du sprite à modifier
// anim:      pointeur vers les données de l'animation
// direction: direction de l'animation (= offset de la sous-animation)
// frame:     la nouvelle frame de l'animation qui doit être affichée
//
// Retourne la prochaine frame de l'animation.
UINT8 update_sprite_animation(UINT8 sprite_id, UINT8 *anim, UINT8 direction, UINT8 frame) {
    UINT8 len = anim[direction];
    UINT8 flip = anim[direction + 1];
    UINT8 tile_id = anim[direction + 2 + frame];

    if (flip) {
        flip_sprite_horiz(sprite_id);
    } else {
        unflip_sprite_horiz(sprite_id);
    }

    set_sprite_tile(sprite_id, tile_id);

    return (frame + 1) % len;
}

void set_background(){
    //Set background in tile data memory
    set_bkg_data(0, CHERRY_WALL_TILESET_COUNT, CHERRY_WALL);
    //Set background in background map memory
    set_bkg_tiles(0, 0, FIRST_MAP_TILEMAP_WIDTH, FIRST_MAP_TILEMAP_HEIGHT, FIRST_MAP);
    SHOW_BKG;
}


void init_user_sprite(){
    set_sprite_data(0, PLAYER_SPRITES_TILE_COUNT, PLAYER_SPRITES);
    //Say to the memory how to load sprites
    SPRITES_8x16;
    SHOW_SPRITES;

    move_sprite(PLAYER_SPRITE_L_ID, player_x, player_y);
    set_sprite_prop(PLAYER_SPRITE_L_ID, S_PALETTE);

    move_sprite(PLAYER_SPRITE_R_ID, player_x + 8, player_y);
    set_sprite_prop(PLAYER_SPRITE_R_ID, S_PALETTE);
}

void init_user_sprite_state(){
    player_x = 80;
    player_y = 72;
    player_direction = PLAYER_DIRECTION_DOWN;
    player_animation_frame = 0;
    is_player_walking = 0;
}

void main(void) {
    UINT8 keys = 0;
    UINT8 frame_skip = 8;  //speed of refresh for smoothing

    set_background();
    init_user_sprite();
    init_user_sprite_state();

    while (1) {
        wait_vbl_done();
        keys = joypad();
        if (keys & J_UP) {
            player_direction = PLAYER_DIRECTION_UP;
            is_player_walking = 1;
        } else if (keys & J_DOWN) {
            player_direction = PLAYER_DIRECTION_DOWN;
            is_player_walking = 1;
        } else if (keys & J_LEFT) {
            player_direction = PLAYER_DIRECTION_LEFT;
            is_player_walking = 1;
        } else if (keys & J_RIGHT) {
            player_direction = PLAYER_DIRECTION_RIGHT;
            is_player_walking = 1;
        } else if (keys & J_START) {
            set_bkg_tiles(5, 6, END_MESSAGE_TILEMAP_WIDTH, END_MESSAGE_TILEMAP_HEIGHT, END_MESSAGE_TILEMAP);
        }
         else {
            is_player_walking = 0;
            frame_skip = 1; //forcing refresh
        }

        //Changing pos
        if (is_player_walking) {
            if (player_direction == PLAYER_DIRECTION_RIGHT) player_x += 1;
            else if (player_direction == PLAYER_DIRECTION_LEFT) player_x -= 1;
            else if (player_direction == PLAYER_DIRECTION_UP) player_y -= 1;
            else if (player_direction == PLAYER_DIRECTION_DOWN) player_y += 1;
            move_sprite(PLAYER_SPRITE_L_ID, player_x, player_y);
            move_sprite(PLAYER_SPRITE_R_ID, player_x + 8, player_y);

            //slowing down for smoothness
            frame_skip -= 1;
            if (!frame_skip) {
                frame_skip = 8;
            } else {
                continue;
            }
        } else {
            player_animation_frame = 0;
        }

        // Update tiles in animation
        update_sprite_animation(
                PLAYER_SPRITE_L_ID,
                PLAYER_SPRITE_ANIM_L,
                player_direction,
                player_animation_frame);

        player_animation_frame = update_sprite_animation(
                PLAYER_SPRITE_R_ID,
                PLAYER_SPRITE_ANIM_R,
                player_direction,
                player_animation_frame);
    }
    
}
