LCC=lcc
INCLUDE=includes/
SDIR=src
RDIR=res
SRC=main.c 
NAME=main

all: $(NAME)

build:
	$(LCC) -I $(INCLUDE) -o game.gb $(SDIR)/$(SRC)
open:
	open game.gb

$(NAME): build open

clean: 
	rm -rf $(NAME)

re: clean all