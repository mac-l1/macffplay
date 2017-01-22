#!/bin/bash
set -ex

chmod a+x *
sudo apt-get install libsdl2-2.0 libfdk-aac1
sudo rm -f /usr/local/bin/macffplay
sudo cp ./macffplay /usr/local/bin/
