##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

NAME	=	arcade

SRC_TEST	=	tests/OSRedirector.cpp	\
				tests/DLLoader.cpp		\

MAIN	=	core/src/main.cpp

SRC	=\
		core/src/Error.cpp	\

OBJ	=	$(SRC:%.cpp=%.o)

OBJ_MAIN	=	$(MAIN:%.cpp=%.o)

OBJ_TEST	=	$(SRC_TEST:%.cpp=%.o)

CXXFLAGS	=	-W -Wall -Wextra -Wshadow	-Icore/include

RM	=	rm -f

CXX	=	g++

LDFLAGS	=	-ldl

TEST_LDFLAGS	=	-lcriterion --coverage

COV_TMP	=	$(SRC:%.cpp=%.gcda) $(SRC:%.cpp=%.gcno) $(SRC_TEST:%.cpp=%.gcda) $(SRC_TEST:%.cpp=%.gcno)

TEST_NAME	=	unit_tests

all:	$(NAME)

$(NAME):	$(OBJ) $(OBJ_MAIN)
			$(CXX) -o $(NAME) $(OBJ) $(OBJ_MAIN) $(LDFLAGS)

clean_coverage	:
					$(RM) $(COV_TMP)

clean	:	clean_coverage
			$(RM) $(OBJ) $(OBJ_TEST) $(OBJ_MAIN)

fclean	:	clean
			$(RM) $(NAME) $(TEST_NAME)

re	:	fclean all

tests_run	:	CXXFLAGS+= -fprofile-arcs -ftest-coverage -Itests/include
tests_run	: 	$(OBJ) $(OBJ_TEST)
				$(CXX) -o $(TEST_NAME) $(OBJ) $(OBJ_TEST) $(TEST_LDFLAGS) $(LDFLAGS)
				./$(TEST_NAME)
				gcovr --exclude tests

debug:	CXXFLAGS+=	-g
debug:	all

.PHONY : clean fclean re tests_run clean_coverage debug
