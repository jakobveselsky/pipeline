#!/bin/bash

cmake .
make
./imageToPCD left.png right.png
