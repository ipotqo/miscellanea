#!/usr/bin/zsh

build_dir=build
main_exe=erasure

mkdir $build_dir
cd $build_dir
cmake ..
make

./$main_exe