#!/bin/bash
set -x # verbose

export ARCH=arm
SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
cd $SCRIPT_DIR

sudo apt-get install -y --force-yes build-essential xutils-dev git autoconf libtool pkg-config curl

cd ffmpeg
./make.sh $@
cd $SCRIPT_DIR

cd mindroid
./make.sh $@
cd $SCRIPT_DIR

cd macffplay
./make.sh $@
cd $SCRIPT_DIR

cd install
#./installmacplayer.sh
cd $SCRIPT_DIR

exit
