#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <iterator>
#include "Pieces.h"
#include <vector>

class Chessboard{

	private:

		bool turn; // = 1 if whites turn, equal to 0 if blacks turn

	map<string, Piece*> board;
	map<string, Piece*>::iterator it;



	vector<string> piece_possible_moves;
	vector<string> positions_threatening_wking;
	vector<string> positions_threatening_bking;






	Rook *whiter1, *whiter2, *blackr1, *blackr2;
	Bishop *whiteb1, *whiteb2, *blackb1, *blackb2;
	Knight *whitek1, *whitek2, *blackk1, *blackk2;
	Queen *whiteq, *blackq;
	King *whitek, *blackk;
	Pawn *whitep1, *whitep2, *whitep3, *whitep4, *whitep5, *whitep6, *whitep7, *whitep8;
	Pawn *blackp1, *blackp2, *blackp3, *blackp4, *blackp5, *blackp6, *blackp7, *blackp8;
	int Check_Move_Valid(string position, Piece* piece);
	void PrintBoard();
	int Position_within_range(string pos_to_be_checked);
	int Check_Move_Target_Valid(string position, string targetposition); //
	void Update_Active_Pieces(string position, string position_target, Piece* piece);
	void TakeTargetPiece(string position_target);
	int Check_All_Possible_Moves(string position, bool first); // checks all possible moves for a piece in a position, also if it is the first time round a 1 needs to be sent too
	bool Check_If_Correct_Turn(bool colourtocheck);
	void Change_Turn();//called at end of submit move to update turn
	int Check_Same_Colour(string position); //checks if the position passed is the same as turn
	void Create_List_Board_Positions();//creates a generic list of chess board positions eg. A1, A2, A3 etc
	bool Is_Check_White();//returns 1 if is in check false if not.
	bool Is_Check_Black();//returns 1 if is in check false if not.
	int Clear_Possible_Move_Lists(); // empties possible move lists for all pieces
	int Check_Checkmate(bool colour);
	int Check_Stalemate(bool colour);
	int Make_Temp_Move(string targetposition,Piece* piece,bool colour,string tempposition,Piece* temppiece);
	bool Is_Check_2(bool colour);//returns 1 if is in check false if not., uses Check_All_Possible_Moves2


	string Where_is_the_king(bool colour);//might delete??


	void SetupBoard();
	void Clear_Board();

	public:
	Chessboard();
	void setupboardmap(string position, Piece* pieceptr); //function to enter values into board map when they are being constructed
	void setupactivepieces(string position, Piece* pieceptr); //function to set up the active pieces
	void Delete_Piece(string position);
	int submitMove(string position, string position_target); // this is the called function from main.
	int Check_If_Piece_Active(string pos);
	map<string,Piece*> activepieces;
	map<string, Piece*>::iterator activeit;
	void resetBoard();
};





#endif
