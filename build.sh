#!/bin/sh

if [ ! -d "build/" ]
then
    mkdir build
fi

g++ -o build/STS.o main.cpp -O3 `pkg-config --cflags --libs opencv4`

if [ $? -eq 0 ]; then
   echo Successful build!
fi
