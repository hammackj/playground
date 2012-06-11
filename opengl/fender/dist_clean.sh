#!/bin/bash 

files=( 
	"cmake.depends" 
	"cmake.check_depends" 
	"CMakeCache.txt" 
	"cmake.check_cache" 
	"*.cmake" 
	"Makefile" 
	"gmon.out" 
	"CMakeFiles" 
	"cmake_install.cmake" 
	"*~"
)

for i in "${files[@]}"
do
	find . -iname $i -exec rm -rf {} \;
done
