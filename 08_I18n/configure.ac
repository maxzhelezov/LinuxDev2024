#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([guess], [0.0.1], [maxzhelezov@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_GNU_GETTEXT(external)
AM_GNU_GETTEXT_VERSION(0.21)
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])
ALL_LINGUAS="ru"

# Checks for programs.
AC_PROG_CC
IT_PROG_INTLTOOL


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in])
AC_OUTPUT

