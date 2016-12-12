#include "Chessboard.h"
#include <iostream>
#include "Pieces.h"
#include "errors.h"
#include <vector>
#include <algorithm>

using namespace std;

// #define COMMENTS_ON
// #define COMMENTS_ON_CHECK
// #define PRINTING
// #define POSSIBLE_MOVES_PRINT

Chessboard::Chessboard(){
	//chessboard constructor
	//creating pieces
	SetupBoard();


}

void Chessboard::SetupBoard(){
	whiter1 = new Rook("White's Rook", true, "A1", this);
	whiter2 = new Rook("White's Rook", true, "H1", this);
	blackr1 = new Rook("Black's Rook", false, "A8", this);
	blackr2 = new Rook("Black's Rook", false, "H8", this);

	whiteb1 = new Bishop("White's Bishop", true, "C1", this);
	whiteb2 = new Bishop("White's Bishop", true, "F1", this);
	blackb1 = new Bishop("Black's Bishop", false, "C8", this); //was C*
	blackb2 = new Bishop("Black's Bishop", false, "F8", this);

	whitek1 = new Knight("White's Knight", true, "B1", this);
	whitek2 = new Knight("White's Knight", true, "G1", this);
	blackk1 = new Knight("Black's Knight", false, "B8", this);
	blackk2 = new Knight("Black's Knight", false, "G8", this);

	whiteq = new Queen("White's Queen", true, "D1", this); //D1 checking stalemate G1 then submit move to G6
	blackq = new Queen("Black's Queen", false, "D8", this);

	whitek = new King("White's King", true, "E1", this);//std E1 checking statemate wiki F7
	blackk = new King("Black's King", false, "E8", this);//std E8, stalemate play H8

	whitep1 = new Pawn("White's Pawn", true, "A2", this);
	whitep2 = new Pawn("White's Pawn", true, "B2", this);
	whitep3 = new Pawn("White's Pawn", true, "C2", this);//should be C2
	whitep4 = new Pawn("White's Pawn", true, "D2", this);
	whitep5 = new Pawn("White's Pawn", true, "E2", this);
	whitep6 = new Pawn("White's Pawn", true, "F2", this);
	whitep7 = new Pawn("White's Pawn", true, "G2", this);
	whitep8 = new Pawn("White's Pawn", true, "H2", this);
	// //
	blackp1 = new Pawn("Black's Pawn", false, "A7", this);
	blackp2 = new Pawn("Black's Pawn", false, "B7", this);
	blackp3 = new Pawn("Black's Pawn", false, "C7", this); //this one
	blackp4 = new Pawn("Black's Pawn", false, "D7", this);
	blackp5 = new Pawn("Black's Pawn", false, "E7", this);
	blackp6 = new Pawn("Black's Pawn", false, "F7", this);
	blackp7 = new Pawn("Black's Pawn", false, "G7", this); //this one
	blackp8 = new Pawn("Black's Pawn", false, "H7", this);

	/*Printing board after construction*/
	// PrintBoard();
	//intialise first turn to white
	turn = 1;
	Create_List_Board_Positions();
	cout << "A new chess game has started!" <<endl;
}

void Chessboard::Clear_Board(){

  for (activeit=activepieces.begin(); activeit!=activepieces.end(); ++activeit){
        delete activeit->second;
  }
	activepieces.clear();
	piece_possible_moves.clear();
}


int Chessboard::Check_If_Piece_Active(string pos){ //used in pieces!

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
	Piece* piece;

	//checking if piece at requested move position exists!
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		piece = activeit->second;
	}
	if(activeit == activepieces.end()){
		cout << "No piece at position " << position << endl;
		return NO_PIECE_AT_REQUESTED_MOVE;
	}

	/*checking if it is the correct pieces turn.
 	checking if the function returns truue, not colour
	*/
	string incorrectcolour="white's";
	if(turn == true){
		incorrectcolour="black's";
	}
	if(Check_If_Correct_Turn((activeit->second)->getPieceColour())==1){
		//cout << "The correct colour is being moved" <<endl;
	}
	if(Check_If_Correct_Turn((activeit->second)->getPieceColour())==0){
		cout << "It is not "   << incorrectcolour<<" turn to move. "<<endl;
		return INCORRECT_COLOUR_MOVE;
	}


	//error check for position
	errorcode=Check_Move_Valid(position, piece);
	if(errorcode ==POSITION_REQUESTED_OUT_OF_RANGE){
		cout << "Move requested outside of board!"<< endl;
		return POSITION_REQUESTED_OUT_OF_RANGE;
	}
	if(errorcode==NO_PIECE_AT_REQUESTED_MOVE_USER){
		cout << "No piece at position " << position << endl;
		return NO_PIECE_AT_REQUESTED_MOVE_USER;
	}

	//now get info about target position - range check it etc.
	errorcode =  Check_Move_Target_Valid(position, position_target);
	if(errorcode==0){
		//cout << "Chessboard::submit :Target checked to be ok" <<endl;
	}
	if(errorcode !=0){
		return errorcode;
	}

	// now see if move is plausible _PIECE SPECIFIC
	int makemovevar=0; // true if the move is plausible in terms of what piece we are moving.
	makemovevar=piece->makemove(position, position_target);
	if(makemovevar!=0){ //if the move is
		cout << piece->getPieceName() << " cannot move to " << position_target<<endl;
		return makemovevar;
	}

	piece->firstmove =0; // setting the pieces firstmove to zero here. cannot do inside pawn makemove as uses this for possibel move checking

	bool targetexists =false; //true if there is a target piece

	activeit = activepieces.find(position_target);//do we need to reset the iterator to beginning first
	if(activeit != activepieces.end() ){
		targetexists=true;
	}
	if(targetexists==true){ // if there is a piece in the target position then call function to delete it
		Delete_Piece(position_target); // deleting target piece
	}

	//section to move piece to position_target on board and update activepieces list
	Update_Active_Pieces(position,position_target, piece); //upadte the active list


	bool incheckwhite=false;
	bool incheckblack=false;

	incheckblack=Is_Check(true,true);
	// cout << "In Check Black? " << incheckblack << endl;

	incheckwhite=Is_Check(false,true);
	// cout << "In Check White? " << incheckwhite << endl;

	//STALEMATE SECTION
	if(incheckblack==false && turn == 0){
		errorcode= Check_Stalemate(false);

	}
	if(incheckwhite==false && turn == 1){
		errorcode= Check_Stalemate(true);
	}
	if(errorcode==STALEMATE){
		cout << "Stalemate" << endl;
		return STALEMATE;
	}
	//end of stalemate section


	if(incheckblack==true){//then check checkmate black
		errorcode= Check_Checkmate(true);
		//cout << "Check_Checkmate_Black is" << errorcode <<endl;
	}
	if(errorcode == CHECKMATE){
		cout<< piece->getPieceName() << " moves from " << position<< " to "\
		 << position_target<<endl;
		cout << "Checkmate Black! White wins!" <<endl;
		return errorcode;
	}
	if(incheckwhite==true){ //then check checkmate white
		errorcode= Check_Checkmate(false);
		//cout << "Check_Checkmate_White is" << errorcode <<endl;
	}
	if(errorcode == CHECKMATE){
		cout<< piece->getPieceName() << " moves from " << position<< " to "\
		 << position_target<<endl;
		cout << "Checkmate White! Black wins!" <<endl;
		return errorcode;
	}

	/* THE ITEMS IN THE FOLLOWING SECTION SHOULD BE DONE LAST */

	Clear_Possible_Move_Lists();
	Change_Turn(); // changes the turn of the game from white to black and vice versa. SHould be done last.
	if(errorcode==0){
		// cout << "MOVE SUCCESSFULL !!!!!!!!!!!!!!!!!!!!!!!!!" <<endl;
		cout<< piece->getPieceName() << " moves from " << position<< " to " << position_target<<endl;
		cout << endl;
		cout << endl;
	}
	return errorcode;


}//end of submit move

int Chessboard::Make_Temp_Move(string targetposition, Piece* piece, bool colour, string tempposition, Piece* temppiece){

	Piece* temptargetpiece;

	//now make the move
	bool targetexists =false; //true if there is a target piece

	activeit = activepieces.find(targetposition);//do we need to reset the iterator to beginning first
	if(activeit != activepieces.end() ){
		temptargetpiece=(activeit->second);
		targetexists=true;
	}
	if(targetexists==true){ // if there is a piece in the target position then call function to delete it
		Delete_Piece(targetposition); // deleting target piece
	}

	activepieces.insert(pair<string, Piece*>(targetposition, piece));

	Delete_Piece(tempposition);

	//now check that check is still occuring
	int stillcheckblack=0;
	stillcheckblack=Is_Check(colour,0); // true check checkmate black as white is just after moving

	if(stillcheckblack==1){ //still in check so undo move and try next
		Delete_Piece(targetposition);
		//inserting piece in original position
		activepieces.insert(pair<string, Piece*>(tempposition, temppiece));

		if(targetexists==true){
			// reinserting deleted target piece
			activepieces.insert(pair<string, Piece*>(targetposition, temptargetpiece)); //reinstate deleted piece

		}

	return TEMP_MOVE_DIDNT_WORK_OUT;
	}

	if(stillcheckblack==0){//this move can be made to get rid of the check therefore checkmate is not occuring
		//break from loop
		//undo moves and return false to calling submitMove. is not in checkmate
		Delete_Piece(targetposition);
		//inserting piece in original position
		activepieces.insert(pair<string, Piece*>(tempposition, temppiece));
		if(targetexists==true){
			// inserting deleted target piece
			activepieces.insert(pair<string, Piece*>(targetposition, temptargetpiece)); //reinstate deleted piece
		}

		return MOVE_VALID; // no checkmate
	}

return TEMP_MOVE_DIDNT_WORK_OUT;//should not reach

}//end of Temp_Make_Move





int Chessboard::Check_Stalemate(bool colour){

	Piece* piece;
	Piece* temppiece;
	//Piece* temptargetpiece;
	string tempposition;
	int tempreturn=0;
	//cout << "In stalemate function" <<endl;

	for(unsigned int i =0; i< piece_possible_moves.size(); i++){
		activeit = activepieces.find(piece_possible_moves[i]);
		tempposition=piece_possible_moves[i];
		if(activeit != activepieces.end() ){
			piece = activeit->second;
			temppiece=piece;
			for(unsigned int k =0; k< piece->actual_possible_moves.size(); k++){

				// //check colour of piece
				if(piece->getPieceColour()==colour){
					continue;//if the move is that of the current turn colour then the move will not be considered
				}

				string targetposition =  piece->actual_possible_moves.at(k);
				tempreturn= Make_Temp_Move(targetposition,piece,colour,tempposition,temppiece);
				if(tempreturn==0){ //not stalemate
					return MOVE_VALID; // no stalmate as there is a move that the colour can make that is not check
				}
			}
		}
	}

return STALEMATE;

}


int Chessboard::Check_Checkmate(bool colour){
		//return non zero if checkmate
		Piece* piece;
		Piece* temppiece;
		string tempposition;
		int tempreturn;
		for(unsigned int i =0; i< piece_possible_moves.size(); i++){
			activeit = activepieces.find(piece_possible_moves[i]);
			tempposition=piece_possible_moves[i];
			if(activeit != activepieces.end() ){
				piece = activeit->second;
				temppiece=piece;
				for(unsigned int k =0; k< piece->actual_possible_moves.size(); k++){
					// //check colour of piece
					if(piece->getPieceColour()==colour){
						continue;//if the move is that of the current turn colour then the move will not be considered
					}
					string targetposition = piece->actual_possible_moves.at(k);
					tempreturn= Make_Temp_Move(targetposition,piece,colour,tempposition,temppiece);
					if(tempreturn==0){ //not stalemate
						return MOVE_VALID; // no stalmate as there is a move that the colour can make that is not check
					}
				}
			}
		}

	return CHECKMATE;

}//end of Check_Checkmate_Black








int Chessboard::Clear_Possible_Move_Lists(){

	Piece* piece;
	for(unsigned int i =0; i< piece_possible_moves.size(); i++){
		activeit = activepieces.find(piece_possible_moves[i]);
		if(activeit != activepieces.end() ){
			piece = activeit->second;
			piece->actual_possible_moves.clear(); //clear its possible move list
			}
		}

	return MOVE_VALID;
}


string Chessboard::Where_is_the_king(bool colour){ //this function does not work!!!!!

	if(colour==true){
		//search for the white king
		for(it=activepieces.begin();it != activepieces.end(); it++){
			if((it->second)->getPieceName() == "White's King"){
				return (it->first);
			}
		}
	}
	if(colour==false){
		//search for the black king
		for(it=activepieces.begin();it != activepieces.end(); it++){
			if((it->second)->getPieceName() == "Black's King"){
				return (it->first);
			}
		}
	}
	return MOVE_VALID;//dummy return
}




bool Chessboard::Is_Check(bool colour, bool firstround){
	//returns true if it is check
	//returns 0 if not check

	bool incheck=false; //1 if incheck
	//checking where the kings are at

	if(firstround==0){
		positions_threatening_bking.clear();
		positions_threatening_wking.clear();
	}
	if(firstround==1){
		for(unsigned int i =0; i < piece_possible_moves.size(); i++){
			Check_All_Possible_Moves(piece_possible_moves[i],1);
		}
	}

	for(unsigned int i =0; i < piece_possible_moves.size(); i++){
		Check_All_Possible_Moves(piece_possible_moves[i],0);
	}


	if(positions_threatening_bking.size() >0 && (colour ==true)){ // &&(colour==true)
		incheck=true;
	}
	if(positions_threatening_bking.size() >0 && (colour ==false)){
		incheck=true;
	}

	if(positions_threatening_wking.size() >0 && (colour ==false)){
		incheck=true;
	}


	return incheck;

}

int Chessboard::Check_All_Possible_Moves(string position, bool firstround){

	Piece* piece;

	//checking if piece at requested move position exists!
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		piece = activeit->second;

	}
	else{
		return NO_PIECE_AT_REQUESTED_MOVE_CHECK;
	}

	for(unsigned int i =0; i < piece_possible_moves.size(); i++){
		int testmoveint =0;
		//if the position to be checked is the position that it cucrently is then skip
		if(piece_possible_moves[i] == position){
			continue;
		}


		//checking if the target is valid, in terms of range and colour in target position
		testmoveint = this->Check_Move_Target_Valid(position, (piece_possible_moves[i]));
		if( testmoveint!=0){
			continue;
		}
		//checking if the piece is allowed to make this move
		testmoveint = piece->makemove(position, (piece_possible_moves[i]));

		// if there is no problem with the move then add it to the possible moves vector
		if(firstround == 1){
			if(testmoveint==0){
				piece->actual_possible_moves.push_back(piece_possible_moves[i]);
			}
		}

		// if the move brings the black king into check then add to list
		if(testmoveint==0 && piece_possible_moves[i]== Where_is_the_king(false)&& \
		(find(positions_threatening_bking.begin(), positions_threatening_bking.end(), position) ==\
		 positions_threatening_bking.end()) &&piece->getPieceColour()==true){
			this->positions_threatening_bking.push_back(position);
		}
		// if the move brings the white king into check then add to list
		if(testmoveint==0 && piece_possible_moves[i]== Where_is_the_king(true)&& \
		(find(positions_threatening_bking.begin(), positions_threatening_bking.end(), position) ==\
		 positions_threatening_bking.end())&&piece->getPieceColour()==false ){
			this->positions_threatening_wking.push_back(position);
		}
	}

	return MOVE_VALID;


}// end of Check_All_Possible_Moves function




void Chessboard::setupactivepieces(string position, Piece* pieceptr){
	activepieces.insert(pair<string, Piece*>(position, pieceptr));
}

void Chessboard::Delete_Piece(string position){
	//find the piece first.
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		activepieces.erase(activeit);
	}
	else{
		cout << "Error, no piece in position" << position << endl;
	}
}


void Chessboard::Change_Turn(){
	//change turn to other colour 1 if white, 0 if black
	if(turn==false){
		turn=true;
		return;
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






void Chessboard::Update_Active_Pieces(string position, string position_target, Piece* piece){
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
	//check if the destination is within range of board
	errorcode = Position_within_range(targetposition);
	if(errorcode!=0){
		return  errorcode;
	}
	//now check target is right colour
	activeit = activepieces.find(targetposition);
	if(activeit != activepieces.end() ){
		targetpiece = activeit->second;
		testcolourtarget = targetpiece->getPieceColour();
	}

	if(activeit == activepieces.end()){
		return MOVE_VALID; // its ok to move the piece as the destination is empty
	}

	//now check thing to be moved.
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
		currentpiece = activeit->second;
		colourofpeiecetobemoved = currentpiece->getPieceColour();

	}
	if(activeit == activepieces.end()){
		return SPACE_OCCUPIED_BY_SAME_COLOUR;
	}
	if(colourofpeiecetobemoved==testcolourtarget){
		return SPACE_OCCUPIED_BY_SAME_COLOUR;
	}
	else{
		return MOVE_VALID;
	}

}








int Chessboard::Check_Move_Valid(string position, Piece* piece){
	/* this function checks if moves submitted from the user in main are
	valid in terms of the board (range) and turn rules */

	int errorcode=0; //prove otherwise
	string testposition=position;
	errorcode = Position_within_range(testposition);
	if(errorcode!=0){
		return  errorcode;
	}
	errorcode = Check_Same_Colour(position); //checks if the space is occupied or not
	if(errorcode==0){ // if the value returned is an "error" then it is ok
		return MOVE_VALID;
	}

	return errorcode;
}

int Chessboard::Check_Same_Colour(string position){
	//checks to see if the position passed is the same colour as turn
	bool colourofpeiecetobemoved;
	activeit = activepieces.find(position);
	if(activeit != activepieces.end() ){
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
		cout << "outside letter range - must be a capital letter between A and H" << endl;
		return POSITION_REQUESTED_OUT_OF_RANGE;
	}

	if(pos_to_be_checked[1] < '1' || pos_to_be_checked[1] > '9' ){
		cout << "outside number range" << endl;
		return POSITION_REQUESTED_OUT_OF_RANGE;
	}

	return MOVE_VALID;

}


/* Function to print current status of board */
void Chessboard::PrintBoard(){
	cout << "The board is as follows : " <<endl;
	for(it=activepieces.begin();it != activepieces.end(); it++){
		cout<<"position "<< it->first <<\
		" piece: " << (it->second)->getPieceName() << " "<<(it->second) << endl;
	}
}

void Chessboard::resetBoard(){
	//to reset chess board.
	//1. delete all pieces
	Clear_Board();
	SetupBoard();
	cout << "Ready for new game" <<endl;

}
