#!/bin/bash

BUILD_DIR=build

SRC="$1"
DST="$2"

if [[ $1 == "" ]]; then
    exit;
fi

if [[ $2 == "" ]]; then
    DST="main"
fi

nasm -f elf64 $SRC -o $BUILD_DIR/$DST.o
ld $BUILD_DIR/$DST.o -o $BUILD_DIR/$DST

read -n 1 -p "Keep $DST.o? (y/n) " char

case "$char" in
    [yY]) echo ""; exit;;
    [nN]) rm $BUILD_DIR/$DST.o; echo ""; exit;;
    *)    exit;;
esac
