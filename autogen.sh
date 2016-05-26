#!/bin/sh
libtoolize --force --automake --copy
aclocal
autoheader
autoconf
automake --add-missing --copy

