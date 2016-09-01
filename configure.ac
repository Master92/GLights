#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([GLights], [0.1b], [nils.friedchen@googlemail.com])
AM_INIT_AUTOMAKE([GLights], [0.1b])
AC_CONFIG_SRCDIR([main.cpp])
# AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([libgtkmm-3.0-dev], [main], [], [
	echo "gtkmm is required for this program"
	exit -1])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([bzero socket])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
