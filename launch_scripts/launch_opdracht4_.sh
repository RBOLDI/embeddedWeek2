#!/bin/bash

#pulling git repository.

echo -e "\n----------Update code!----------\n"

git pull https://github.com/RBOLDI/embeddedWeek2.git

#compile opdracht4

echo -e "\n----------Compile C++ code for opdracht4!----------\n"
cd ../opdrachten/opdracht4
g++ -Wall -o opdracht ncurses.cpp -lncurses

#run opdracht4

echo -e "\n----------Run opdracht4!----------\n"
./opdracht4

