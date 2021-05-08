#!/bin/sh
g++ main.cpp `pkg-config --cflags --libs opencv4`
if [ $? -eq 0 ]; then
   echo Successful build!
fi
