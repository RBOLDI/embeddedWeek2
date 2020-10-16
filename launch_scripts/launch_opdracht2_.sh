#!/bin/bash

#pulling git repository.

echo -e "\n----------Update code!----------\n"

git pull https://github.com/RBOLDI/embeddedWeek2.git

#compile opdracht2

echo -e "\n----------Compile C++ code for opdracht3!----------\n"
cd ../opdrachten/opdracht2
g++ -Wall -o opdracht2 compiler.cpp parser.cpp

#run opdracht2

echo -e "\n----------Run opdracht3!----------\n"
./opdracht2

