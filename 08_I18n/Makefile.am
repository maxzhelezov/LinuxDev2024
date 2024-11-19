CFLAGS= -Wall -Wextra -O0 -g
AM_CPPFLAGS = -D'LOCALE_PATH="$(localedir)"'

bin_PROGRAMS=guess
guess_SOURCES=src/guess.c

SUBDIRS = po

gitclean:
	git clean -xdf
