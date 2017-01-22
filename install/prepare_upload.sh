#!/bin/bash
set -ex

VERSION=v0.1
rm -rf $VERSION
mkdir -p $VERSION
cp * $VERSION||true
rm $VERSION/prepare_upload.sh
