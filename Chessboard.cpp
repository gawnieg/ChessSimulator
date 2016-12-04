#include "Chessboard.h"
#include <iostream>
#include "Pieces.h"
#include "errors.h"

using namespace std;



Chessboard::Chessboard(){
	//chessboard constructor
	//creating pieces

	whiter1 = new Rook("White's Rook", true, "A1", this);
	whiter2 = new Rook("White's Rook", true, "E4", this);
	blackr1 = new Rook("Black's Rook", false, "A8", this);
	blackr2 = new Rook("Black's Rook", false, "H8", this);

	whiteb1 = new Bishop("White's Bishop", true, "A1", this);
	whiteb2 = new Bishop("White's Bishop", true, "F1", this);
	blackb1 = new Bishop("Black's Bishop", false, "C6", this); //was C*
	blackb2 = new Bishop("Black's Bishop", false, "F8", this);

	whitek1 = new Knight("White's Knight", true, "D4", this);
	whitek2 = new Knight("White's Knight", true, "G1", this);
	blackk1 = new Knight("Black's Knight", false, "B8", this);
	blackk2 = new Knight("Black's Knight", false, "G8", this);

	//whiteq = new Queen("White's Queen", true, "E4", this); //D1
	blackq = new Queen("Black's Queen", false, "D6", this);

	whitek = new King("White's King", true, "E1", this);
	blackk = new King("Black's King", false, "E8", this);

	whitep1 = new Pawn("White's Pawn stA2", true, "A2", this);
	whitep2 = new Pawn("White's PawnstB2", true, "B2", this);
	whitep3 = new Pawn("White's Pawn stC2", true, "C2", this);//should be C2
	whitep4 = new Pawn("White's Pawn stD2", true, "D2", this);
	whitep5 = new Pawn("White's Pawn stE2", true, "E2", this);
	whitep6 = new Pawn("White's Pawn stF2", true, "F2", this);
	whitep7 = new Pawn("White's Pawn stG2", true, "G2", this);
	whitep8 = new Pawn("White's Pawn stH2", true, "H2", this);
	//
	blackp1 = new Pawn("Black's Pawn stA7", false, "A7", this);
	blackp2 = new Pawn("Black's Pawn stB7", false, "B7", this);
	blackp3 = new Pawn("Black's Pawn stC7", false, "C7", this); //this one
	blackp4 = new Pawn("Black's Pawn stD7", false, "D7", this);
	blackp5 = new Pawn("Black's Pawn stE7", false, "E7", this);
	blackp6 = new Pawn("Black's Pawn stF7", false, "F3", this);
	blackp7 = new Pawn("Black's Pawn stG7", false, "G7", this); //this one
	blackp8 = new Pawn("Black's Pawn stH7", false, "H7", this);

	/*Printing board after construction*/
	PrintBoard();



	}

void Chessboard::setupboardmap(string position, Piece* pieceptr){

	board.insert(pair<string, Piece*>(position, pieceptr));

}



void Chessboard::setupactivepieces(string position, Piece* pieceptr){

	activepieces.insert(pair<string, Piece*>(position, pieceptr));

}

void Chessboard::Delete_Piece(string position){

	//find the piece first.
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		activepieces.erase(activeit);
		cout << position << "deleted" << endl;
	}
	else{
		cout << "Error, no piece in position" << position << endl;
	}

}

int Chessboard::Check_If_Piece_Active(string pos){

			activeit = activepieces.find(pos);
			cout << "checking" <<pos << "to see if it is occupied by a piece " <<endl;
			if(activeit != activepieces.end() ){
				cout << "there is a piece occupying this position" <<endl;
				return 1;

			}

	return 0;
}

int Chessboard::submitMove(string position, string position_target){
	/*this function is public and called from main
	will check if the move is valid then with the chessboard and the game rules,
	make the move, then update the activepieces,  */
	int errorcode=0;
	cout << "Chessboard::submitMove The position to be moved is " << position << endl;
	cout << "Chessboard::submitMove The target position is " << position_target<<endl;
	Piece* piece;

	//checking if piece at requested move position exists!
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		piece = activeit->second;
		cout << "Chessboard::submitMove There is a " << (activeit->second)->getPieceName() \
		<< " at this position " << position << endl;
	}
	if(activeit == activepieces.end()){
		cout << "The piece does not exist!!" << endl;
		return NO_PIECE_AT_REQUESTED_MOVE;
	}

	//error check for position
	errorcode=Check_Move_Valid(position, piece);
	cout << " Chessboard::submitMove The error checking status is " << errorcode <<endl;
	if(errorcode !=0){
		return errorcode;
	}


	//now get info about target position - range check it etc.
	cout<<"Chessboard::submit Move now checking target position" << endl;
	errorcode =  Check_Move_Target_Valid(position, position_target);
	cout << " Chessboard::submitMove - check target valid "<< position_target\
	<< " is " << errorcode	 << endl;
	if(errorcode==0){
		cout << "target checked to be ok" <<endl;
	}

	if(errorcode !=0){
		return errorcode;
	}


	// now see if move is plausible _PIECE SPECIFIC
	int makemovevar=0; // true if the move is plausible in terms of what piece we are moving.
	makemovevar=piece->makemove(position, position_target);
	cout << "Chessboard::submitMove makemove called and result is " << makemovevar <<endl;
	if(makemovevar!=0){ //if the move is
		cout << "piece makemove says no" << endl;
		return makemovevar;
	}


	//section to check if another piece is being taken as a result of this
	//check the destination position.
	bool targetexists =false; //true if there is a target piece

	activeit = activepieces.find(position_target);//do we need to reset the iterator to beginning first
	if(activeit != activepieces.end() ){
		cout << "There is a " << (activeit->second)->getPieceName() \
		<< "at this target position " << position_target << endl;
		targetexists=true;
	}
	if(activeit == activepieces.end()){
		cout << "The target piece does not exist!!" << endl;
	}


	if(targetexists==true){ // if there is a piece in the target position then call function to delete it
		TakeTargetPiece(position_target); // deleting target piece
	}

	//section to move piece to position_target on board and update activepieces list
	Update_Active_Pieces(position,position_target, piece); //upadte the active list
	PrintBoard();

return errorcode;


}



















void Chessboard::TakeTargetPiece(string position_target){

	cout<< "deleting piece at " << position_target <<endl;
	Delete_Piece(position_target);
	cout <<"deleted" <<endl;

}



void Chessboard::Update_Active_Pieces(string position, string position_target, Piece* piece){
	cout << "updating activelist" << endl;
	Delete_Piece(position); //delete old entry
	activepieces.insert(pair<string, Piece*>(position_target, piece));

}


int Chessboard::Check_Move_Target_Valid(string position, string targetposition){
	/* this function checks if the target is a valid target in terms of position and
	also what piece is in the target */

int errorcode=0; //prove otherwise

	//string testposition = "A2";
	// bool testcolour =true;
	string testposition=targetposition;
	bool testcolour;
	Piece* piece;
	cout << "Check_Move_Target_Valid Checking target destination " << position << endl;
	//check if the destination is within range of board
	errorcode = Position_within_range(testposition);
	if(errorcode!=0){
		return  errorcode;
	}

	activeit = activepieces.find(targetposition);
	if(activeit != activepieces.end() ){
		piece = activeit->second;
		cout << "There is a " << (activeit->second)->getPieceName() \
		<< "at this position " << endl;
		testcolour = piece->getPieceColour();
		errorcode = Check_Space_Occupied_By_Own(position,testcolour); //checks if the space is occupied or not
		if(errorcode!=0){
			cout << "Space occuped by own" <<endl;
			return errorcode;
		}
	}

	else{
		cout << "There is no piece in the target destination" <<endl;
	}



return errorcode;


}








int Chessboard::Check_Move_Valid(string position, Piece* piece){
	/* this function checks if moves submitted from the user in main are
	valid in terms of the board (range) and turn rules */

int errorcode=0; //prove otherwise

	//string testposition = "A2";
	// bool testcolour =true;
	string testposition=position;
	bool testcolour = piece->getPieceColour();

	errorcode = Position_within_range(testposition);
	if(errorcode!=0){
		cout << "Position out of range" <<endl;
		return  errorcode;
	}

	errorcode = Check_Space_Occupied_By_Own(testposition,testcolour); //checks if the space is occupied or not
	if(errorcode==1){ // if the value returned is an "error" then it is ok
		cout << "Space occuped by own so ok" <<endl;
		return MOVE_VALID;
	}




return errorcode;

}

int Chessboard::Check_Space_Occupied_By_Own(string pos_to_be_checked, bool RequestedMoveColour){ // function to check if the space passed is occupied

	//checking if the requested space is occupied by one of the same colour

	for(it=board.begin(); it != board.end();it++){
		if(it->first == pos_to_be_checked && (it->second)->getPieceColour() == RequestedMoveColour){
			cout << "the pos_to_be_checked is " << pos_to_be_checked <<endl;
			cout << "the colour of the piece is " << (it->second)->getPieceColour() << endl;
			return SPACE_OCCUPIED_BY_SAME_COLOUR; //completely unoccuped
		}
	}




return MOVE_VALID;


}

int Chessboard::Position_within_range(string pos_to_be_checked){ // function to check if the space passed is occupied

	//check if that position is even valid?! liek M7 etc.
	if(pos_to_be_checked[0] < 'A' || pos_to_be_checked[0] >'H' ){
		cout << "outside letter range" << endl;
		return POSITION_REQUESTED_OUT_OF_RANGE;
	}

	if(pos_to_be_checked[1] < '1' || pos_to_be_checked[1] > '9' ){
		cout << "outside number range" << endl;
		return POSITION_REQUESTED_OUT_OF_RANGE;
	}

return MOVE_VALID;

}


/* Function to print current status of board */
void Chessboard::PrintBoard(){ //do we need to pass "this"
	cout << "The board is as follows : " <<endl;


	for(it=activepieces.begin();it != activepieces.end(); it++){
		cout<<"position "<< it->first <<\
		" piece: " << (it->second)->getPieceName() << endl;

	}

}
