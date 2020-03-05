##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

NAME	=	lib_arcade_sfml.so

SRC	= src/main.cpp	\

OBJ	=	$(SRC:%.cpp=%.o)

CXXFLAGS	=	-W -Wall -Wextra -Wshadow -Iinclude -fpic

CXX	=	g++

LDFLAGS	=	-shared\

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -rf $(NAME)

re:	fclean all

debug:	CXXFLAGS+=	-g
debug:	all

.PHONY : clean fclean re debug
