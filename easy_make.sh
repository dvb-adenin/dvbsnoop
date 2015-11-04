#! /bin/sh
make distclean
libtoolize --force
aclocal
#autoheader
automake --force-missing --add-missing
autoconf
./configure
make
