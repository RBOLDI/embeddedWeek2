#!/bin/bash

#pulling git repository.

echo -e "\n----------Update code!----------\n"

git pull https://github.com/RBOLDI/embeddedWeek2.git

#compile opdracht5

echo -e "\n----------Compile C++ code for opdracht5!----------\n"
cd ../opdrachten/opdracht5
g++ -Wall -o opdracht5 compiler.cpp runtime.cpp parser.cpp  -lbcm2835

#run opdracht5

echo -e "\n----------Run opdracht5!----------\n"
./opdracht5

