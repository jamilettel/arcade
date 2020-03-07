##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

NAME	=	arcade

SRC_TEST	=	core/tests/OSRedirector.cpp	\
				core/tests/DLLoader.cpp		\

MAIN	=	core/src/main.cpp

SRC	=\
		core/src/Error.cpp	\
		core/src/Core.cpp	\

OBJ	=	$(SRC:%.cpp=%.o)

OBJ_MAIN	=	$(MAIN:%.cpp=%.o)

OBJ_TEST	=	$(SRC_TEST:%.cpp=%.o)

CXXFLAGS	=	-W -Wall -Wextra -Wshadow	-Icore/include -Iinclude -std=c++17

RM	=	rm -f

CXX	=	g++

LDFLAGS	=	-ldl

TEST_LDFLAGS	=	-lcriterion --coverage

COV_TMP	=	$(SRC:%.cpp=%.gcda) $(SRC:%.cpp=%.gcno) $(SRC_TEST:%.cpp=%.gcda) $(SRC_TEST:%.cpp=%.gcno)

TEST_NAME	=	unit_tests

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
		$(CXX) -o $(NAME) $(OBJ) $(OBJ_MAIN) $(LDFLAGS)
		$(MAKE) -C games/lib_arcade_centipede/
		$(MAKE) -C games/lib_arcade_nibbler/
		$(MAKE) -C graphics/lib_arcade_libcaca/
		$(MAKE) -C graphics/lib_arcade_sfml/

clean_coverage:
		$(RM) $(COV_TMP)

clean: clean_coverage
		$(RM) $(OBJ) $(OBJ_TEST) $(OBJ_MAIN)
		$(MAKE) -C games/lib_arcade_centipede/ clean
		$(MAKE) -C games/lib_arcade_nibbler/ clean
		$(MAKE) -C graphics/lib_arcade_libcaca/ clean
		$(MAKE) -C graphics/lib_arcade_sfml/ clean

fclean: clean
		$(RM) $(NAME) $(TEST_NAME)
		$(MAKE) -C games/lib_arcade_centipede/ fclean
		$(MAKE) -C games/lib_arcade_nibbler/ fclean
		$(MAKE) -C graphics/lib_arcade_libcaca/ fclean
		$(MAKE) -C graphics/lib_arcade_sfml/ fclean

re: fclean all

tests_run: CXXFLAGS+= -fprofile-arcs -ftest-coverage -Icore/tests/include
tests_run: $(OBJ) $(OBJ_TEST)
			$(CXX) -o $(TEST_NAME) $(OBJ) $(OBJ_TEST) $(TEST_LDFLAGS) $(LDFLAGS)
			./$(TEST_NAME)
			gcovr --exclude tests

debug: CXXFLAGS+ = -g
debug: all

games:
	$(MAKE) -C games/lib_arcade_centipede/
	$(MAKE) -C games/lib_arcade_nibbler/

graphics:
	$(MAKE) -C graphics/lib_arcade_libcaca/
	$(MAKE) -C graphics/lib_arcade_sfml/

.PHONY : clean fclean re tests_run clean_coverage debug games graphics
