#!/bin/bash
set -ex

if [ $(echo $@|grep -w "clean"|wc -l) != "0" ]; then
    make clean
    exit 0
fi

#sudo apt-get install

make 
sudo make install
