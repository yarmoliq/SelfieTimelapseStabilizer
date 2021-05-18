#!/bin/sh

if [ ! -d "build/obj/" ]
then
    mkdir -p build/obj
fi

g++ -o build/sts src/main.cpp src/**/*.cpp -O3 \
    `pkg-config --cflags --libs opencv4` \
    `pkg-config --cflags --libs exiv2`

if [ $? -eq 0 ]; then
   echo Successful build!
fi
