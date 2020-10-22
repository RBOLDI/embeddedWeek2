#!/bin/bash

#pulling git repository.

echo -e "\n----------Update code!----------\n"

git pull https://github.com/RBOLDI/embeddedWeek2.git

#compile opdracht6

echo -e "\n----------Compile C++ code for opdracht6!----------\n"
cd ../opdrachten/opdracht6_Afvink
g++ -Wall -o opdracht6 compiler.cpp runtime.cpp parser.cpp  -lbcm2835

#run opdracht6

echo -e "\n----------Run opdracht6!----------\n"
./opdracht6

