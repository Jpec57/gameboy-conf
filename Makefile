LCC=lcc
INCLUDE=includes/
SDIR=src
TILEMAP_DIR=res/tilemaps
TILESET_DIR=res/tilesets
TILEMAPS=res/tilemaps/first_map.c \
	res/tilemaps/gameboy_front_tilemap.c \
	res/tilemaps/big_map_tilemap.c \
	res/tilemaps/end_message_tilemap.c
TILESETS=res/tilesets/background_window/cherry_wall.c \
	res/tilesets/sprites/gameboy_front_tileset.c \
	res/tilesets/sprites/player_sprites.c	
RDIR=res
SRC=main.c 
NAME=main

all: $(NAME)

build:
	$(LCC) -o game.gb $(SDIR)/$(SRC) $(TILEMAPS) $(TILESETS) 
open:
	open game.gb

$(NAME): build open

clean: 
	rm -rf $(NAME)

re: clean all