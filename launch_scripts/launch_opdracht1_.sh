#!/bin/bash

#pulling git repository.

echo -e "\n----------Update code!----------\n"

git pull https://github.com/RBOLDI/embeddedWeek2.git

#show opdracht1

echo -e "\n----------Show BNF_notation.txt----------\n"

cd ../opdrachten/opdracht1
cat BNF_notation.txt
