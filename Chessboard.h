#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <iterator>
#include "Pieces.h"

class Chessboard{

	private:
	map<string, Piece*> board;
	map<string, Piece*>::iterator it;

	map<string,Piece*> activepieces;
	map<string, Piece*>::iterator activeit;

	Rook *whiter1, *whiter2, *blackr1, *blackr2;
	Bishop *whiteb1, *whiteb2, *blackb1, *blackb2;
	Knight *whitek1, *whitek2, *blackk1, *blackk2;
	Queen *whiteq, *blackq;
	King *whitek, *blackk;
	Pawn *whitep1, *whitep2, *whitep3, *whitep4, *whitep5, *whitep6, *whitep7, *whitep8;
	Pawn *blackp1, *blackp2, *blackp3, *blackp4, *blackp5, *blackp6, *blackp7, *blackp8;
	int Check_Move_Valid(string position, Piece* piece);
	void PrintBoard();
    int Check_Space_Occupied_By_Own(string pos_to_be_checked,bool RequestedMoveColour);
	int Position_within_range(string pos_to_be_checked);
	int Check_Move_Target_Valid(string position, string targetposition);
	void Update_Active_Pieces(string position, string position_target, Piece* piece);
	void TakeTargetPiece(string position_target);
	public:
	Chessboard();
	void setupboardmap(string position, Piece* pieceptr); //function to enter values into board map when they are being constructed
	void setupactivepieces(string position, Piece* pieceptr); //function to set up the active pieces
	void Delete_Piece(string position);
	int submitMove(string position, string position_target); // this is the called function from main.
	int Check_If_Piece_Active(string pos);


};





#endif
