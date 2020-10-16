#!/bin/bash

#pulling git repository.

echo -e "\n----------Update code!----------\n"

git pull https://github.com/RBOLDI/embeddedWeek2.git

#compile opdracht3

echo -e "\n----------Compile C++ code for opdracht3!----------\n"
cd ../opdrachten/opdracht3
g++ -Wall -o opdracht3 compiler.cpp parser.cpp runtime.cpp -lbcm2835

#run opdracht3

echo -e "\n----------Run opdracht3!----------\n"
./opdracht3

