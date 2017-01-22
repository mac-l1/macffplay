#!/bin/bash

if [ $(echo $@|grep -w "clean"|wc -l) != "0" ]; then
    rm -rf Mindroid.cpp
else
if ! [ -e Mindroid.cpp ]; then
  git clone https://github.com/esrlabs/Mindroid.cpp.git
  cd Mindroid.cpp
  git checkout 0e0371fc764168660018a8e8643a4640fbad5ae7
  sed 's/-D__ARMv6_CPU_ARCH__ -fPIC -O2/-fPIC -O2 -Wa,-mimplicit-it=thumb/g' Makefile.RPi > Makefile.ARM
  make -f Makefile.ARM
  sudo cp libmindroid.so /usr/local/lib
fi
fi

