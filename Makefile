##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

all:
		$(MAKE) -C core/
		$(MAKE) -C games/lib_arcade_centipede/
		$(MAKE) -C games/lib_arcade_nibbler/
		$(MAKE) -C graphics/lib_arcade_libcaca/
		$(MAKE) -C graphics/lib_arcade_sfml/

clean_coverage:
		$(MAKE) -C core/ clean_coverage
		$(MAKE) -C games/lib_arcade_centipede/ clean_coverage
		$(MAKE) -C games/lib_arcade_nibbler/ clean_coverage
		$(MAKE) -C graphics/lib_arcade_libcaca/ clean_coverage
		$(MAKE) -C graphics/lib_arcade_sfml/ clean_coverage

clean: clean_coverage
		$(MAKE) -C core/ clean
		$(MAKE) -C games/lib_arcade_centipede/ clean
		$(MAKE) -C games/lib_arcade_nibbler/ clean
		$(MAKE) -C graphics/lib_arcade_libcaca/ clean
		$(MAKE) -C graphics/lib_arcade_sfml/ clean

fclean: clean
		$(MAKE) -C core/ fclean
		$(MAKE) -C games/lib_arcade_centipede/ fclean
		$(MAKE) -C games/lib_arcade_nibbler/ fclean
		$(MAKE) -C graphics/lib_arcade_libcaca/ fclean
		$(MAKE) -C graphics/lib_arcade_sfml/ fclean

re: fclean all

tests_run:
		$(MAKE) -C core/ tests_run
		$(MAKE) -C games/lib_arcade_centipede/ tests_run
		$(MAKE) -C games/lib_arcade_nibbler/ tests_run
		$(MAKE) -C graphics/lib_arcade_libcaca/ tests_run
		$(MAKE) -C graphics/lib_arcade_sfml/ tests_run

debug:
		$(MAKE) -C core/ debug
		$(MAKE) -C games/lib_arcade_centipede/ debug
		$(MAKE) -C games/lib_arcade_nibbler/ debug
		$(MAKE) -C graphics/lib_arcade_libcaca/ debug
		$(MAKE) -C graphics/lib_arcade_sfml/ debug

games:
	$(MAKE) -C games/lib_arcade_centipede/
	$(MAKE) -C games/lib_arcade_nibbler/

graphics:
	$(MAKE) -C graphics/lib_arcade_libcaca/
	$(MAKE) -C graphics/lib_arcade_sfml/

.PHONY : clean fclean re tests_run clean_coverage debug games graphics
