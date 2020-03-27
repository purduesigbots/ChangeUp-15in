#!/bin/bash
#Runs clang-format on all files (sans API.h) in a PROS repo
#Clang-format is needed on PATH
if [ -e "project.pros" ]
then
	echo "Formatting Code..."
	for i in ./include/*.hpp
	do
		echo "Formatting ${i##*/}"
		clang-format -i ./include/${i##*/}
	done
	for i in ./src/*.cpp
	do
		echo "Formatting ${i##*/}"
		clang-format -i ./src/${i##*/}
	done
	echo "Formatting Complete"
else
	echo "Current directory is not a PROS project - will not format it."
fi
