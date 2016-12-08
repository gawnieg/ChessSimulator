chess: main.o Pieces.o Chessboard.o
	g++ -g -std=c++11 -Wall main.o Pieces.o Chessboard.o -o chess

main.o: main.cpp Pieces.h
	g++ -g -std=c++11 -Wall -c main.cpp

Pieces.o: Pieces.cpp Pieces.h
	g++ -g -std=c++11 -Wall -c Pieces.cpp

Chessboard.o: Chessboard.cpp Chessboard.h Pieces.h
	g++ -g -std=c++11 -Wall -c Chessboard.cpp
