# build file to generate the distribution binary tarball

make clean
./configure --prefix=/tmp/comptty-build
make install-strip
tar czf comptty-$1.bin.tgz -C /tmp/comptty-build/bin comptty

make clean

./configure \
  $PKGCFG \
  $CROSSCFG \
  --with-ptw32=/opt/mxe/usr/i686-pc-mingw32 \
  PTW32_LIBS="-lpthread -lpcreposix -lpcre" \
  FLTK_CONFIG=$PREFIX/bin/i686-pc-mingw32-fltk-config

make

$PREFIX/bin/i686-pc-mingw32-strip src/comptty.exe
make nsisinst
mv src/*setup*exe .

make clean

# build the distribution tarball
./configure
make distcheck
make clean
