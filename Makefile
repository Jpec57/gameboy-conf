LCC=lcc
INCLUDE=includes/
SDIR=src
RDIR=res
SRC=main.c 
NAME=main

all: $(NAME)

$(NAME):
	$(LCC) -o game.gb $(SDIR)/$(SRC)
	open game.gb
clean: 
	rm -rf $(NAME)

re: clean all