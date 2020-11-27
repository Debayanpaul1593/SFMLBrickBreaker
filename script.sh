#! /bin/bash
g++ -c src/main.cpp src/Bat.cpp src/Ball.cpp
g++ main.o Bat.o Ball.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./sfml-app