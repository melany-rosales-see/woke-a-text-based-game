# woke-a-text-based-game
A text based game created in C++20ish


--------------
Compiling using already compiled libraries:

1. Run: g++-13 -std=c++20 main.cpp -o main -L./lib -lGame -lJson
2. Update LD_LIBRARY_PATH to point to libraries
3. Run: ./main

-------------
Manually compiling Json library

1. Run:\
g++-13 -std=c++20 -fPIC -c  Entry.cpp -o Entry.o\
g++-13 -std=c++20 -fPIC -c  Json.cpp -o Json.o\
g++-13 -std=c++20 -shared -o libJson.so Entry.o Json.o

-------------
Manually compiling Json library
1. Run:\
g++-13 -std=c++20 -fPIC -c  Bathroom.cpp -o Bathroom.o\
g++-13 -std=c++20 -fPIC -c  StudioApt.cpp -o StudioApt.o\
g++-13 -std=c++20 -fPIC -c  Vocab.cpp -o Vocab.o\
g++-13 -std=c++20 -fPIC -c  Game.cpp -o Game.o\
g++-13 -std=c++20 -fPIC -c  Haunting.cpp -o Haunting.o\
g++-13 -std=c++20 -fPIC -c  Scene.cpp -o Scene.o\
g++-13 -std=c++20 -fPIC -c  Kitchen.cpp -o Kitchen.o\
g++-13 -std=c++20 -shared -o libGame.so Bathroom.o Game.o StudioApt.o Vocab.o Haunting.o Scene.o Kitchen.o

-------------
