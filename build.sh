#!/bin/bash
set -e
TOOLCHAIN=rm-toolchain
source $TOOLCHAIN/environment-setup-cortexa9hf-neon-oe-linux-gnueabi
qmake
make
set -x
deploy=result
mkdir -p $deploy/usr/bin $deploy/usr/share/draft/ deploy/etc/ $deploy/lib/systemd/system/
mv draft $deploy/usr/bin
mv {qml,js} $deploy/usr/share/draft/
mv extra-files/draft $deploy/etc/
mv extra-files/draft.service $deploy/lib/systemd/system/draft.service
