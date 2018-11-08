##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Basic Makefile
##

SRC	= 	main.cpp \
		Noise.cpp

SRC_ON_GIT = 

OBJ	= $(SRC:.cpp=.o)

NAME	= bomberman

CXXFLAGS  = -W -Wall -Werror -Wextra -lIrrlicht -lGL -lSDL

CURRENT_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

GIT_DIR = $(subst _the_sources,,$(CURRENT_DIR))

all:	$(NAME)

save_git:
	cp $(SRC_ON_GIT) $(GIT_DIR)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) -lIrrlicht -lGL -lSDL
clean:
	rm -f $(OBJ)
fclean:		clean
	rm -f $(NAME)
re:	fclean all
author:
	echo $(USER) > author
