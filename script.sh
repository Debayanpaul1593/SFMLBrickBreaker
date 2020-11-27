#! /bin/bash
g++ -c src/main.cpp src/Bat.cpp
g++ main.o Bat.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./sfml-app