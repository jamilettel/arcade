##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

all:
		$(MAKE) -C core/ --no-print-directory
		$(MAKE) -C games/lib_arcade_centipede/ --no-print-directory
		$(MAKE) -C games/lib_arcade_nibbler/ --no-print-directory
		$(MAKE) -C graphics/lib_arcade_libcaca/ --no-print-directory
		$(MAKE) -C graphics/lib_arcade_sfml/ --no-print-directory

clean_coverage:
		@$(MAKE) -C core/ clean_coverage --no-print-directory
		@$(MAKE) -C games/lib_arcade_centipede/ clean_coverage --no-print-directory
		@$(MAKE) -C games/lib_arcade_nibbler/ clean_coverage --no-print-directory
		@$(MAKE) -C graphics/lib_arcade_libcaca/ clean_coverage --no-print-directory
		@$(MAKE) -C graphics/lib_arcade_sfml/ clean_coverage --no-print-directory

clean: clean_coverage
		@$(MAKE) -C core/ clean --no-print-directory
		@$(MAKE) -C games/lib_arcade_centipede/ clean --no-print-directory
		@$(MAKE) -C games/lib_arcade_nibbler/ clean --no-print-directory
		@$(MAKE) -C graphics/lib_arcade_libcaca/ clean --no-print-directory
		@$(MAKE) -C graphics/lib_arcade_sfml/ clean --no-print-directory

fclean: clean
		@$(MAKE) -C core/ fclean --no-print-directory
		@$(MAKE) -C games/lib_arcade_centipede/ fclean --no-print-directory
		@$(MAKE) -C games/lib_arcade_nibbler/ fclean --no-print-directory
		@$(MAKE) -C graphics/lib_arcade_libcaca/ fclean --no-print-directory
		@$(MAKE) -C graphics/lib_arcade_sfml/ fclean --no-print-directory

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
