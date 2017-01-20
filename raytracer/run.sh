#!/bin/bash

make
./raytracer.out > test.ppm
open test.ppm
