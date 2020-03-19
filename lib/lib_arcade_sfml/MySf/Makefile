##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

NAME	=	libMySf.a

SRC	=\
		src/Error.cpp	\
		src/Color/Utils.cpp	\
		src/Color/SmoothShifting.cpp	\
		src/Color/AColor.cpp	\
		src/InputZone.cpp	\
		src/List/BasicList.cpp	\
		src/List/ButtonList.cpp	\
		src/List/AList.cpp	\
		src/Button/BasicButton.cpp	\
		src/Button/RectButton.cpp	\
		src/Button/BasicButtonOutline.cpp	\
		src/Button/AButton.cpp	\

OBJ	=	$(SRC:%.cpp=%.o)

CXXFLAGS	=	-W -Wall -Wextra -Wshadow	\
				-Iinclude -std=c++17 -fPIC	\

RM	=	@rm -f

CXX	=	g++

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
		ar rc $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

debug: CXXFLAGS += -g
debug: all

.PHONY : clean fclean re debug
