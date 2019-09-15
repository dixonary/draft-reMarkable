make clean && \
qmake && \
make -j12 && \
arm-oe-linux-gnueabi-strip bin/draft && \
scp bin/draft root@remarkable:
