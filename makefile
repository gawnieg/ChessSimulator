chess: main.o Pieces.o Chessboard.o
	g++ -g -Wall main.o Pieces.o Chessboard.o -o chess
	
main.o: main.cpp Pieces.h
	g++ -g -Wall -c main.cpp
	
Pieces.o: Pieces.cpp Pieces.h
	g++ -g -Wall -c Pieces.cpp

Chessboard.o: Chessboard.cpp Chessboard.h Pieces.h
	g++ -g -Wall -c Chessboard.cpp

