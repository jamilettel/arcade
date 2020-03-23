##
## EPITECH PROJECT, 2020
## Arcade
## File description:
## Makefile
##

all:
	$(MAKE) -C core/ --no-print-directory
	$(MAKE) -C games/lib_arcade_solarfox/ --no-print-directory
	$(MAKE) -C games/lib_arcade_nibbler/ --no-print-directory
	$(MAKE) -C lib/lib_arcade_libcaca/ --no-print-directory
	$(MAKE) -C lib/lib_arcade_sfml/ --no-print-directory
	$(MAKE) -C lib/lib_arcade_ncurses/ --no-print-directory

clean_coverage:
	@$(MAKE) -C core/ clean_coverage --no-print-directory
	@$(MAKE) -C games/lib_arcade_solarfox/ clean_coverage --no-print-directory
	@$(MAKE) -C games/lib_arcade_nibbler/ clean_coverage --no-print-directory
	@$(MAKE) -C lib/lib_arcade_libcaca/ clean_coverage --no-print-directory
	@$(MAKE) -C lib/lib_arcade_sfml/ clean_coverage --no-print-directory
	@$(MAKE) -C lib/lib_arcade_ncurses/ clean_coverage --no-print-directory

clean: clean_coverage
	@$(MAKE) -C core/ clean --no-print-directory
	@$(MAKE) -C games/lib_arcade_solarfox/ clean --no-print-directory
	@$(MAKE) -C games/lib_arcade_nibbler/ clean --no-print-directory
	@$(MAKE) -C lib/lib_arcade_libcaca/ clean --no-print-directory
	@$(MAKE) -C lib/lib_arcade_sfml/ clean --no-print-directory
	@$(MAKE) -C lib/lib_arcade_ncurses/ clean --no-print-directory

fclean: clean
	@$(MAKE) -C core/ fclean --no-print-directory
	@$(MAKE) -C games/lib_arcade_solarfox/ fclean --no-print-directory
	@$(MAKE) -C games/lib_arcade_nibbler/ fclean --no-print-directory
	@$(MAKE) -C lib/lib_arcade_libcaca/ fclean --no-print-directory
	@$(MAKE) -C lib/lib_arcade_sfml/ fclean --no-print-directory
	@$(MAKE) -C lib/lib_arcade_ncurses/ fclean --no-print-directory

re: fclean all

tests_run:
	$(MAKE) -C core/ tests_run
	$(MAKE) -C games/lib_arcade_solarfox/ tests_run
	$(MAKE) -C games/lib_arcade_nibbler/ tests_run
	$(MAKE) -C lib/lib_arcade_libcaca/ tests_run
	$(MAKE) -C lib/lib_arcade_sfml/ tests_run
	$(MAKE) -C lib/lib_arcade_ncurses/ tests_run

debug:
	$(MAKE) -C core/ debug
	$(MAKE) -C games/lib_arcade_solarfox/ debug
	$(MAKE) -C games/lib_arcade_nibbler/ debug
	$(MAKE) -C lib/lib_arcade_libcaca/ debug
	$(MAKE) -C lib/lib_arcade_sfml/ debug
	$(MAKE) -C lib/lib_arcade_ncurses/ debug

core:
	$(MAKE) -C core/ --no-print-directory

games:
	$(MAKE) -C games/lib_arcade_solarfox/
	$(MAKE) -C games/lib_arcade_nibbler/

graphicals:
	$(MAKE) -C lib/lib_arcade_libcaca/
	$(MAKE) -C lib/lib_arcade_sfml/
	$(MAKE) -C lib/lib_arcade_ncurses/

.PHONY : clean fclean re tests_run clean_coverage debug games graphicals core
