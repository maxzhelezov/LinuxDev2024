#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([repl-hasher], [0.0.1], [maxzhelezov@gmail.com])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init], [], [AC_MSG_ERROR([librhasher is required])])
#AC_CHECK_LIB([readline], [readline], [AC_DEFINE([READLINE])])

AC_ARG_WITH([readline],
    [AS_HELP_STRING([--with-readline],
    [support fancy command line editing @<:@default=check@:>@])],
    [],
    [with_readline=check])

LIBREADLINE=

AS_IF([test "x$with_readline" != xno],
    [AC_CHECK_LIB([readline], [readline],
    [AC_SUBST([LIBREADLINE], ["-lreadline"])
    AC_DEFINE([HAVE_LIBREADLINE], [1],
                [Define if you have libreadline])
    ],
    [if test "x$with_readline" != xcheck; then
        AC_MSG_FAILURE(
        [--with-readline was given, but test for readline failed])
    fi
])])
    

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

