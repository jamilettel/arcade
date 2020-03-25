##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

NAME	=	../lib_arcade_sdl.so

SRC	=\
		src/SDLError.cpp	\
		src/Color/Utils.cpp	\
		src/Color/SmoothShifting.cpp	\
		src/Color/AColor.cpp	\
		src/InputZone.cpp	\
		src/Scene/MainMenuScene.cpp	\
		src/MySDL/Text.cpp	\
		src/MySDL/Font.cpp	\
		src/MySDL/Rectangle.cpp	\
		src/MySDL/Window.cpp	\
		src/MySDL/Sprite.cpp	\
		src/List/BasicList.cpp	\
		src/List/ButtonList.cpp	\
		src/List/AList.cpp	\
		src/SDLGraphical.cpp	\
		src/Button/RectButton.cpp	\
		src/Button/AButton.cpp	\
		src/Scene/GameScene.cpp	\
		src/Scene/GameOverScene.cpp	\

OBJ	=	$(SRC:%.cpp=%.o)

CXXFLAGS	=	-W -Wall -Wextra -Wshadow	\
				-Iinclude -I./../../include -std=c++17 -fPIC

RM	=	@rm -f

CXX	=	g++

LDFLAGS	=	-ldl -lstdc++fs -l SDL2 -l SDL2_image -l SDL2_ttf -shared

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
		$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean_coverage:
				$(RM)

clean:
		$(RM) $(OBJ) $(OBJ_TEST) $(OBJ_MAIN)

fclean: clean
		$(RM) $(NAME) $(TEST_NAME)

re: fclean all

tests_run:

debug: CXXFLAGS += -g
debug: all

.PHONY : clean fclean re debug
