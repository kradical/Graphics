#!/bin/bash

make
./raytracer.out > test.ppm
xdg-open test.ppm
