#!/bin/bash
set -ex

#FILE=~/sintel_trailer-1080p.mp4
FILE=~/sintel-1080-cfg02.mkv
#FILE=~/bbb_1080p_c.ts
#FILE=http://qthttp.apple.com.edgesuite.net/1010qwoeiuryfg/0640/06401.ts

BIN=`pwd`/bin/macffplay
if [ -z "$1" ]; then PLAYFILE="${FILE}"; else PLAYFILE="$1"; fi
"${BIN}" -v 48 "${PLAYFILE}"
