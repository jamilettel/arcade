##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

NAME	=	../lib_arcade_sfml.so

SRC_TEST	=	\

MAIN	=	\

SRC	=	src/SfmlGraphical.cpp				\
		src/SfmlError.cpp					\
		src/Scene/MainMenuScene.cpp			\
		src/Scene/GameScene.cpp				\

OBJ	=	$(SRC:%.cpp=%.o)

OBJ_MAIN	=	$(MAIN:%.cpp=%.o)

OBJ_TEST	=	$(SRC_TEST:%.cpp=%.o)

CXXFLAGS	=	-W -Wall -Wextra -Wshadow	-Iinclude -I./../../include -std=c++17 -fPIC

RM	=	@rm -f

CXX	=	g++

LDFLAGS	=	-ldl -lstdc++fs -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -shared	\
			-LMySf -lMySf -Wl,-rpath=./MySf/

TEST_LDFLAGS	=	-lcriterion --coverage

COV_TMP	=	$(SRC:%.cpp=%.gcda) $(SRC:%.cpp=%.gcno) $(SRC_TEST:%.cpp=%.gcda) $(SRC_TEST:%.cpp=%.gcno)

TEST_NAME	=	unit_tests

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
		@make -C MySf --no-print-directory
		$(CXX) -o $(NAME) $(OBJ) $(OBJ_MAIN) $(LDFLAGS)

clean_coverage:
		$(RM) $(COV_TMP)

clean: clean_coverage
		@make -C MySf clean --no-print-directory
		$(RM) $(OBJ) $(OBJ_TEST) $(OBJ_MAIN)

fclean: clean
		@make -C MySf fclean --no-print-directory
		$(RM) $(NAME) $(TEST_NAME)

re: fclean all

tests_run: CXXFLAGS+= -fprofile-arcs -ftest-coverage -Icore/tests/include
tests_run: $(OBJ) $(OBJ_TEST)
			$(CXX) -o $(TEST_NAME) $(OBJ) $(OBJ_TEST) $(TEST_LDFLAGS) $(LDFLAGS)
			./$(TEST_NAME)
			gcovr --exclude tests

debug: CXXFLAGS += -g
debug: all

.PHONY : clean fclean re tests_run clean_coverage debug
