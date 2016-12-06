#include "Chessboard.h"
#include <iostream>
#include "Pieces.h"
#include "errors.h"
#include <vector>

using namespace std;

// #define COMMENTS_ON

Chessboard::Chessboard(){
	//chessboard constructor
	//creating pieces

	whiter1 = new Rook("White's Rook", true, "A1", this);
	whiter2 = new Rook("White's Rook", true, "E4", this);
	blackr1 = new Rook("Black's Rook", false, "A8", this);
	blackr2 = new Rook("Black's Rook", false, "H8", this);

	whiteb1 = new Bishop("White's Bishop", true, "A1", this);
	whiteb2 = new Bishop("White's Bishop", true, "F1", this);
	blackb1 = new Bishop("Black's Bishop", false, "C1", this); //was C*
	blackb2 = new Bishop("Black's Bishop", false, "F8", this);

	whitek1 = new Knight("White's Knight", true, "B1", this);
	whitek2 = new Knight("White's Knight", true, "G1", this);
	blackk1 = new Knight("Black's Knight", false, "B8", this);
	blackk2 = new Knight("Black's Knight", false, "G8", this);

	// whiteq = new Queen("White's Queen", true, "E7", this); //D1
	blackq = new Queen("Black's Queen", false, "D8", this);

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
	blackp6 = new Pawn("Black's Pawn stF7", false, "F7", this);
	blackp7 = new Pawn("Black's Pawn stG7", false, "G7", this); //this one
	blackp8 = new Pawn("Black's Pawn stH7", false, "H7", this);

	/*Printing board after construction*/
	PrintBoard();
	//intialise first turn to white
	turn = 1;


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
			#ifdef COMMENTS_ON
			cout << "checking" <<pos << "to see if it is occupied by a piece " <<endl;
			#endif
			if(activeit != activepieces.end() ){
				#ifdef COMMENTS_ON
				cout << "there is a piece occupying this position" <<endl;
				#endif
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
	cout << "here2 " << endl;

	//checking if piece at requested move position exists!
	activeit = activepieces.find(position);
	cout << "here3 " << endl;
	if(activeit != activepieces.end() ){
		piece = activeit->second;
		cout << "Chessboard::submitMove There is a " << (activeit->second)->getPieceName() \
		<< " at this position " << position << endl;
	}
	if(activeit == activepieces.end()){
		#ifdef COMMENTS_ON
		cout << "The piece does not exist!!" << endl;
		#endif
		return NO_PIECE_AT_REQUESTED_MOVE;
	}
	cout << "here1 " << endl;
	//checking if it is the correct pieces turn
	if(Check_If_Correct_Turn((activeit->second)->getPieceColour())==1){
		cout << "The correct colour is being moved" <<endl;
	}
	if(Check_If_Correct_Turn((activeit->second)->getPieceColour())==0){
		cout << "The incorrect colour is being moved" <<endl;
		return INCORRECT_COLOUR_MOVE;
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
		cout << "Chessboard::submit :Target checked to be ok" <<endl;
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
		#ifdef COMMENTS_ON
		cout << "The target piece does not exist!!" << endl;
		#endif
	}


	if(targetexists==true){ // if there is a piece in the target position then call function to delete it
		TakeTargetPiece(position_target); // deleting target piece
	}

	//section to move piece to position_target on board and update activepieces list
	Update_Active_Pieces(position,position_target, piece); //upadte the active list
	//prrinting the board for debugging
	PrintBoard();
	//create list of chessboard positions to be checked
	Create_List_Board_Positions();

	if(turn == 1){ // white so check Is_Check_Black
		bool incheckblack;
		incheckblack=Is_Check_Black();
		cout << "In Check Black? " << incheckblack << endl;
	}
	if(turn==0){
		bool incheckwhite;
		incheckwhite=Is_Check_White();
		cout << "In Check White? " << incheckwhite << endl;
	}


	// errorcode = Check_All_Possible_Moves("C5");

	// cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
	//changing turn colour
	Change_Turn();

	cout << "Error code in submitMove is " << errorcode << endl;
	return errorcode;


}


void Chessboard::Change_Turn(){
	//change turn to other colour 1 if white, 0 if black
	if(turn==false){
		turn=true;
	}
	if(turn==true){
		turn=false;
	}
}




bool Chessboard::Check_If_Correct_Turn(bool colourtocheck){
	//returns 1 if the piece being moved is the right colour to be moved
	if(colourtocheck==turn){
		return 1;
	}
	else{
		return 0;
	}
}



void Chessboard::Create_List_Board_Positions(){
	//	creating list to be checked - this is all possible chessboard squares
	for(char i = '1'; i < '9'; i++){
		for(char j ='A'; j< 'I'; j++){
			string temp;
			temp += j;
			temp +=i;

			//cout << "adding " << temp << " to the vector"<<endl;
			piece_possible_moves.push_back(temp);
		}
	}
}


int Chessboard::Check_All_Possible_Moves(string position){
//
	Piece* piece;

	//checking if piece at requested move position exists!
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		piece = activeit->second;
		#ifdef COMMENTS_ON
		cout << "Chessboard::Check_All_Possible_Moves:" <<endl <<" There is a " <<\
		 (activeit->second)->getPieceName() \
		<< " at this position " << position << endl;
		cout <<endl;
		#endif

	}
	else{
		#ifdef COMMENTS_ON
		cout<< "No piece at position specified " << endl;
		#endif
		return NO_PIECE_AT_REQUESTED_MOVE_CHECK;
	}




	//cout<< "The size of vector element is " << piece_possible_moves.size()<< endl;
	for(unsigned int i =0; i < piece_possible_moves.size(); i++){
		#ifdef COMMENTS_ON
		cout << endl;
		cout << "Checking element "<< i << " which is " << (piece_possible_moves[i]) << " for possible move" <<endl;
		#endif
		int testmoveint =0;
		//if the position to be checked is the position that it cucrently is then skip
		if(piece_possible_moves[i] == position){
			continue;
		}


		//checking if the target is valid, in terms of range and colour in target position
		testmoveint = this->Check_Move_Target_Valid(position, (piece_possible_moves[i]));
		#ifdef COMMENTS_ON
		cout <<"testmoveint after Check_Move_Target_Valid is " << testmoveint <<endl;
		#endif
		if( testmoveint!=0){
			#ifdef COMMENTS_ON
			cout << "Check_All_Possible_Moves Check_Move_Target_Valid says no" << endl;
			#endif
			continue;
		}
		//checking if the piece is allowed to make this move
		testmoveint = piece->makemove(position, (piece_possible_moves[i]));
		//cout << "printing testmoveint after makemove testing " << testmoveint<<endl;
		if( testmoveint!=0){
			#ifdef COMMENTS_ON
			cout << "Check_All_Possible_Moves piece makemove says no" << endl;
			#endif
		}
		// if there is no problem with the move then add it to the possible moves vector
		if(testmoveint==0){
			#ifdef COMMENTS_ON
			cout << "adding "<< piece_possible_moves[i]<<" to actual_possible_moves " <<endl;
			#endif
			piece->actual_possible_moves.push_back(piece_possible_moves[i]);
		}


		// //experimental - checking if the move brings the black king in check
		if(testmoveint==0 && piece_possible_moves[i]==blackk->getPosition()){
			cout<< "adding to the threatening the black king list" <<endl;
			this->positions_threatening_bking.push_back(piece_possible_moves[i]);
		}
		if(testmoveint==0 && piece_possible_moves[i]==whitek->getPosition()){
			cout<< "adding to the threatening the white king list" <<endl;
			this->positions_threatening_wking.push_back(piece_possible_moves[i]);
		}
	}


	//possible moves vector
	// #ifdef COMMENTS_ON
	cout <<"PM for "<<piece->getPieceName() << "\t" << "[";

	for(unsigned int i =0; i < piece->actual_possible_moves.size(); i++){
		cout << piece->actual_possible_moves[i]  << " ";
	}
	cout <<"]" <<endl;
	// #endif


	return MOVE_VALID;


}// end of Check_All_Possible_Moves function




bool Chessboard::Is_Check_White(){
	//returns true if it is check
	//returns 0 if not check
	int errorcode=0;
	bool incheck=0; //1 if incheck
	//checking where the kings are at
	cout<< "The black king is at" << blackk->getPosition()<< endl;
	cout<< "The white king is at" << whitek->getPosition()<< endl;

		for(unsigned int i =0; i < piece_possible_moves.size(); i++){
			#ifdef COMMENTS_ON
			cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
			cout << "Checking " << piece_possible_moves[i] <<endl;
			#endif
			errorcode = Check_All_Possible_Moves(piece_possible_moves[i]);



		}

	cout << "Printing positions_threatening_wking" << endl;
	for(int i=0; i < positions_threatening_wking.size(); i++){
			cout << positions_threatening_wking[i] <<endl;
	}

	if(positions_threatening_wking.size() >0 ){
		incheck=true;
	}


	cout << "The in check status is " << incheck << endl;

	return incheck;

}

bool Chessboard::Is_Check_Black(){
	//returns true if it is check
	//returns 0 if not check
	int errorcode=0;
	bool incheck=0; //1 if incheck
	//checking where the kings are at
	cout<< "The black king is at" << blackk->getPosition()<< endl;


		for(unsigned int i =0; i < piece_possible_moves.size(); i++){
			#ifdef COMMENTS_ON
			cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
			cout << "Checking " << piece_possible_moves[i] <<endl;
			#endif
			errorcode = Check_All_Possible_Moves(piece_possible_moves[i]);



		}

	//printing positions_threatening_bking
	cout << "Printing positions_threatening_bking" << endl;
	for(int i=0; i < positions_threatening_bking.size(); i++){
			cout << positions_threatening_bking[i] <<endl;
	}


	if(positions_threatening_bking.size() >0){
		incheck=true;
	}


	cout << "The in check status is " << incheck << endl;

	return incheck;

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
	also what piece is in the target
	returns 0 if ok, other number otherwise
	*/

int errorcode=0; //prove otherwise

	bool testcolourtarget;
	bool colourofpeiecetobemoved;
	Piece* targetpiece;
	Piece* currentpiece;
	#ifdef COMMENTS_ON
	cout << "Check_Move_Target_Valid Checking target destination " << targetposition << endl;
	#endif
	//check if the destination is within range of board
	errorcode = Position_within_range(targetposition);
	if(errorcode!=0){
		return  errorcode;
	}
	//now check target is right colour
	activeit = activepieces.find(targetposition);
	if(activeit != activepieces.end() ){
		targetpiece = activeit->second;
		#ifdef COMMENTS_ON
		cout << "There is a " << (activeit->second)->getPieceName() \
		<< " in this position " << endl;
		#endif
		testcolourtarget = targetpiece->getPieceColour();
	}

	if(activeit == activepieces.end()){
		#ifdef COMMENTS_ON
		cout << "There is no target at " <<position <<endl;
		#endif
		return MOVE_VALID; // its ok to move the piece as the destination is empty
	}

	//now check thing to be moved.
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		currentpiece = activeit->second;
		#ifdef COMMENTS_ON
		cout << "There is a " << (activeit->second)->getPieceName() \
		<< " in this position " << endl;
		#endif
		colourofpeiecetobemoved = currentpiece->getPieceColour();

	}
	if(activeit == activepieces.end()){
		#ifdef COMMENTS_ON
		cout << "The currentpiece cannot be found " <<position <<endl;
		#endif
		return SPACE_OCCUPIED_BY_SAME_COLOUR;
	}



	if(colourofpeiecetobemoved==testcolourtarget){
		#ifdef COMMENTS_ON
		cout << "the target colour is the same as the piece being moved" <<endl;
		#endif
		return SPACE_OCCUPIED_BY_SAME_COLOUR;
	}


	else{
		#ifdef COMMENTS_ON
		cout << "The colours do not match so legit" <<endl;
		#endif
		return MOVE_VALID;
	}

}








int Chessboard::Check_Move_Valid(string position, Piece* piece){
	/* this function checks if moves submitted from the user in main are
	valid in terms of the board (range) and turn rules */

int errorcode=0; //prove otherwise

	//string testposition = "A2";
	// bool testcolour =true;
	string testposition=position;
	//bool testcolour = piece->getPieceColour();

	errorcode = Position_within_range(testposition);
	if(errorcode!=0){
		cout << "Position out of range" <<endl;
		return  errorcode;
	}

	errorcode = Check_Same_Colour(position); //checks if the space is occupied or not
	if(errorcode==0){ // if the value returned is an "error" then it is ok
		cout << "Position " << position<< "occuped by correct turn colour so ok" <<endl;
		return MOVE_VALID;
	}

return errorcode;

}

int Chessboard::Check_Same_Colour(string position){
	//checks to see if the position passed is the same colour as turn
	bool colourofpeiecetobemoved;
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		#ifdef COMMENTS_ON
		cout << "There is a " << (activeit->second)->getPieceName() \
		<< " in this position " << endl;
		#endif
		colourofpeiecetobemoved = (activeit->second)->getPieceColour();
	}
	if(colourofpeiecetobemoved!= turn){
		return 1;
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
		" piece: " << (it->second)->getPieceName() << " "<<(it->second) << endl;

	}

}
