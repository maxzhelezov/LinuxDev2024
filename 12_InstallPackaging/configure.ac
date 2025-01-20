#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Programm to guess numbers], [0.0.1], [maxzhelezov@gmail.com], [guess])
AM_INIT_AUTOMAKE([foreign subdir-objects])
DX_INIT_DOXYGEN([guess])
AM_GNU_GETTEXT(external)
AM_GNU_GETTEXT_VERSION(0.21)
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
AC_CONFIG_HEADERS([config.h])
ALL_LINGUAS="ru"
LT_INIT

# Checks for programs.
AC_PROG_CC
IT_PROG_INTLTOOL
PKG_CHECK_MODULES([CHECK],[check])

AC_SUBST(CK_VERBOSITY, verbose)
AC_ARG_VAR(CK_VERBOSITY, [Default: "verbose", can be "silent", "minimal" or "normal")])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in src/Makefile tests/Makefile Doxyfile])
AC_OUTPUT

