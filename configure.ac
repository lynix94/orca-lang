#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT(orca, 0.5, kiyeul.lee@gmail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/vm/main.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_YACC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h libintl.h limits.h malloc.h netinet/in.h stddef.h stdlib.h string.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_FUNC_OBSTACK
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for libraries
AC_CHECK_LIB([m], [main])
AC_CHECK_LIB([dl], [main])
AC_CHECK_LIB([pthread], [main])
AC_CHECK_LIB([stdc++], [main])
AC_CHECK_LIB([curses], [main])
AC_CHECK_LIB([readline], [main])
AC_CHECK_LIB([boost_regex], [main])
AC_CHECK_LIB([boost_filesystem], [main])
AC_CHECK_LIB([boost_date_time], [main])
AC_CHECK_LIB([boost_system], [main])
AC_CHECK_LIB([gmp], [main])
AC_CHECK_LIB([gtk], [main])
AC_CHECK_LIB([sqlite3], [main])

# Install dir
DIR_DEFS="-DORCA_PREFIXDIR=\\\"\$(prefix)\\\" -DORCA_BINDIR=\\\"\$(bindir)\\\" -DORCA_LIBDIR=\\\"\$(libdir)\\\""

AC_SUBST([DIR_DEFS])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([dup2 gettimeofday memset select socket strdup])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 src/Makefile])
AC_OUTPUT


