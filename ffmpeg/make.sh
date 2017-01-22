#!/bin/bash
set -x

VERSION=3.2

MYDIR=$(cd $(dirname $0); pwd)
cd $MYDIR
FFMPEG_PREFIX=${MYDIR}/ffmpeg-install-${VERSION}

if [ $(echo $@|grep -w "clean"|wc -l) != "0" ]; then
    rm -rf ffmpeg-${VERSION} ffmpeg-install-${VERSION}
    exit 0
fi

if [ -d "ffmpeg-install-${VERSION}" ]; then
    echo "ffmpeg already built; done."
    exit 0
fi

if [ ! -d "ffmpeg-${VERSION}" ]; then
    sudo apt-get -y install autoconf automake build-essential libass-dev libfreetype6-dev libsdl1.2-dev libtheora-dev libtool libva-dev libvdpau-dev libvorbis-dev libxcb1-dev libxcb-shm0-dev libxcb-xfixes0-dev pkg-config texinfo zlib1g-dev libx264-dev libfdk-aac-dev libmp3lame-dev libopus-dev curl libvpx-dev

    if [ ! -e "ffmpeg-${VERSION}.tar.xz" ]; then
        curl -O http://ffmpeg.org/releases/ffmpeg-${VERSION}.tar.xz
    fi
    tar xf ffmpeg-${VERSION}.tar.xz
    cd ffmpeg-${VERSION} || exit 2

    CFLAGS="-mfloat-abi=hard -mfpu=neon -ftree-vectorize -mvectorize-with-neon-quad -ffast-math -O3 -pipe -fstack-protector"

    CFLAGS="$CFLAGS" CXXFLAGS="$CXXFLAGS" LDFLAGS="$LDFLAGS" \
    ./configure --prefix=$FFMPEG_PREFIX \
	--extra-version="macffplay-${VERSION}" \
        --pkg-config-flags="--static" \
	--enable-ffplay \
	--disable-ffmpeg \
	--disable-ffprobe \
	--disable-ffserver \
	--disable-doc \
	--enable-gpl \
	--enable-runtime-cpudetect \
	--enable-muxer=all \
	--enable-demuxer=all \
	--enable-encoder=all \
	--enable-decoder=all \
	--enable-protocol=all \
	--disable-devices \
        --enable-libass \
        --enable-libfdk-aac \
        --enable-libfreetype \
        --enable-libmp3lame \
        --enable-libopus \
        --enable-libtheora \
        --enable-libvorbis \
        --enable-libvpx \
        --enable-libx264 \
	--enable-nonfree \
        --disable-shared \
        --enable-static \
	--enable-pthreads \
        ${FLAGS}
fi

cd $MYDIR/ffmpeg-${VERSION} || exit 2
BUILDTHREADS=${BUILDTHREADS:-$(grep -c "^processor" /proc/cpuinfo)}
[ ${BUILDTHREADS} -eq 0 ] && BUILDTHREADS=1
make -j ${BUILDTHREADS} 
if [ $? -eq 0 ]
then
  [ ${SUDO} ] && echo "Root privileges are required to install to ${FFMPEG_PREFIX}"
  ${SUDO} make install && echo "$VERSION" > ../.ffmpeg-installed
else
  echo "ERROR: Building ffmpeg failed"
  exit 1
fi
