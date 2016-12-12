#include "Pieces.h"
#include <string>
#include <iostream>
#include "Chessboard.h"
#include "errors.h"

#define COMMENTS_ON

using namespace std;

Piece::Piece(bool _colour, string _name, string _position, Chessboard* _chessboardptr ){

	// cout<< "Constructing piece"<<endl;
	piececolour=_colour; //true if black, white if false
	name=_name; //name of piece
	position = _position; //holds the position of the piece in form A4
	chessboardptr=_chessboardptr;  // pieces constructor
	chessboardptr->setupboardmap(position,this);
	chessboardptr->setupactivepieces(position,this);



}

string Piece::getPieceName(){ //getter function
	return name;
}

string Piece::getPosition(){ //getter function
	return position;
}

bool Piece::getPieceColour(){//getter function
	return piececolour;
}

string Piece::setPosition(string future){
	position = future;
return MOVE_VALID; //dummy return unused function

}





Queen::Queen( string _name, bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
	//Queen constuctor


	}

int Queen::makemove(const string &position, const string &targetposition){
	//check for diagonal
	if((abs(targetposition[0]-position[0]) == abs(targetposition[1]-position[1]))\
	&&Check_If_Blocked_Diag(position,targetposition)==0){
		return MOVE_VALID;
	}
	//vertical movement
	if(((position[1]-targetposition[1] >=1 || targetposition[1]-position[1] >=1)\
	&& position[0] == targetposition[0])\
	&& Check_If_Blocked_Vertical(position, targetposition)==0 ){
		return MOVE_VALID;

	}
	//horizontal movement
	if(((position[0] -targetposition[0] >=1 ||targetposition[0]-position[0] >=1)\
	&&position[1]==targetposition[1])&& \
	Check_If_Blocked_Horizontal(position, targetposition)==0){
		 return MOVE_VALID;
	}




return INVALID_QUEEN_MOVE;

}
King::King( string _name,bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
		//King constructor
	}

int King::makemove(const string &position, const string &targetposition){

	// cout <<endl;
	// cout << "Checking for " << this->getPieceName() << " @ " << this->getPosition()<<endl;
	// cout<< "position[0] is" <<position[0]<<endl;
	// cout<< "position[1] is" <<position[1]<<endl;
	// cout<< "targetposition[0] is" <<targetposition[0]<<endl;
	// cout<< "targetposition[1] is" <<targetposition[1]<<endl;
	// cout << "abs(targetposition[0]-position[0]) is  " << abs(targetposition[0]-position[0])<<endl;
	//check for diagonal
	if(((abs(targetposition[0]-position[0]) == abs(targetposition[1]-position[1]))\
	&&abs(targetposition[1]-position[1])==1)\
	&&Check_If_Blocked_Diag(position,targetposition)==0){
		// cout <<"diagonal move deemed valid" <<endl;
		return MOVE_VALID;
	}
	//vertical movement
	if(((position[1]-targetposition[1] ==1 || targetposition[1]-position[1] ==1)\
	&& position[0] == targetposition[0])\
	&& Check_If_Blocked_Vertical(position, targetposition)==0){
		// cout <<"vertical move deemed valid" <<endl;
		return MOVE_VALID;
	}
	//horizontal movement
	if(((position[0] -targetposition[0]==1 ||targetposition[0]-position[0]==1)\
	&&position[1]==targetposition[1])&& \
	Check_If_Blocked_Horizontal(position, targetposition)==0){
		// cout <<"horizontal move deemed valid" <<endl;
		 return MOVE_VALID;
	}


return INVALID_KING_MOVE;

}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

Knight::Knight( string _name,bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
		//Knight constructor
	}
int Knight::makemove(const string &position, const string &targetposition){
	//check if moves are valid. No blocking checking required for Knight
	//D4 to E6
	if(targetposition[0]-position[0]==1 && targetposition[1]-position[1]==2){
		return MOVE_VALID;
	}
	//D4 to F5
	if(targetposition[0]-position[0]==2 && targetposition[1]-position[1]==1){
		return MOVE_VALID;
	}
	//D4 to C6
	if(position[0]-targetposition[0]==1 && targetposition[1]-position[1]==2){
		return MOVE_VALID;
	}
	//D4 to B5
	if(position[0]-targetposition[0]==2 && targetposition[1]-position[1]==1){
		return MOVE_VALID;
	}
	//D4 to B3
	if(position[0]-targetposition[0]==2 && position[1]-targetposition[1]==1){
		return MOVE_VALID;
	}
	//D4 to C2
	if(position[0]-targetposition[0]==1 && position[1]-targetposition[1]==2){
		return MOVE_VALID;
	}
	//D4 to E2
	if(targetposition[0]-position[0]==1 && position[1]-targetposition[1]==2){
		return MOVE_VALID;
	}
	//D4 to F3
	if(targetposition[0]-position[0]==2 && position[1]-targetposition[1]==1){
		return MOVE_VALID;
	}

	return KNIGHT_INVALID_MOVE;



}




/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
Rook::Rook( string _name, bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
		//Rook constructor

	}

int Rook::makemove(const string &position, const string &targetposition){
		//gonna subtract from the number part to move down the board
		//vertical movement
		//cout <<"checking if vertical" <<endl;
		if(((position[1]-targetposition[1] >=1 || targetposition[1]-position[1] >=1)\
		&& position[0] == targetposition[0])\
		&& Check_If_Blocked_Vertical(position, targetposition)==0 ){
			return 0;
		}
		//cout <<"not vertical" <<endl;
		//horizontal movement
		//cout <<"checking if horizontal" <<endl;
		if(((position[0] -targetposition[0] >=1 ||targetposition[0]-position[0] >=1)\
		&&position[1]==targetposition[1])&& \
		Check_If_Blocked_Horizontal(position, targetposition)==0){
			 return 0;
		}

		else{
			return INVALID_ROOK_MOVE;
		}

}




/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

Bishop::Bishop(string _name,bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
		//Bishop constructor

	}


int Bishop::makemove(const string &position, const string &targetposition){

	if((abs(targetposition[0]-position[0]) == abs(targetposition[1]-position[1]))\
	&&Check_If_Blocked_Diag(position,targetposition)==0){
		return MOVE_VALID;
	}



return INVALID_BISHOP_MOVE;

}
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
Pawn::Pawn(string _name,bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{

	}


Piece::~Piece(){
	//intentionally blank
}



Piece* Piece::GetPiecePtrGivenPos(string position){
	// this is a helper function that will return a Piece ptr if passed a position
	Piece* piece;
	chessboardptr->activeit = chessboardptr->activepieces.find(position);
	if(chessboardptr->activeit != chessboardptr->activepieces.end() ){
		piece = chessboardptr->activeit->second;
		return piece;
	}
	else{
		return NULL;
	}





}



int Pawn::makemove(const string &position, const string &targetposition){
cout << "first move " << firstmove << endl;
	if(firstmove==true){
		//if the firstmove is true, then can move two spaces forward
		if(this->getPieceColour() ==0){//the piece to be moved is black
			//gonna subtract from the number part to move down the board
			if(((position[1]-targetposition[1] ==2 && position[0] == targetposition[0])\
				||(position[1]-targetposition[1] ==1 && position[0] == targetposition[0])) \
			&& Check_If_Blocked_Vertical(position, targetposition)==0){
				cout << "Here" << endl;
				return MOVE_VALID;

			}
		}

		if(this->getPieceColour() ==0){//the piece to be moved is black _DIAGONAL KILL
			//gonna subtract from the number part to move down the board
			if((position[1]-targetposition[1] ==1 && abs(targetposition[0]-position[0])==1)\
			&& GetPiecePtrGivenPos(targetposition)!=NULL)
			{cout << "Here" << endl;
				return MOVE_VALID;
			}
		}



		if(this->getPieceColour() ==1){//the piece to be moved is white
			//gonna subtract from the number part to move down the board

			if(((targetposition[1]-position[1] ==2 && position[0] == targetposition[0])\
			||(targetposition[1]-position[1] ==1 && position[0] == targetposition[0]))\
			&& Check_If_Blocked_Vertical(position, targetposition)==0){
				cout << "Here" << endl;
				return MOVE_VALID;
			}
		}

		if(this->getPieceColour() ==1){//the piece to be moved is white _DIAGONAL KILL
			//gonna subtract from the number part to move down the board

			if((targetposition[1]-position[1] ==1 && abs(position[0]-targetposition[0])==1)\
			&& GetPiecePtrGivenPos(targetposition)!=NULL)
			{cout << "Here" << endl;
				return MOVE_VALID;
			}
		}


	}
	else{ //not first move, can only move one square
		//piece to be moved it black and its one square straight

		if(this->getPieceColour() ==0){//the piece to be moved is black
			//gonna subtract from the number part to move down the board
			if(position[1]-targetposition[1] ==1\
				&& position[0] == targetposition[0]
				 && Check_If_Blocked_Vertical(position, targetposition)==0){
					 cout << "Here" << endl;
				// this->firstmove=false;  //set firstmove to false as its firstmove has been completed
				return MOVE_VALID;
			}
		}
		//now diagonal kill move
		if(this->getPieceColour() ==0){//the piece to be moved is black. checking if blocked not
			//required as will be taking a piece if moving diagonnally
			//gonna subtract from the number part to move down the board
			if((abs(position[0]-targetposition[0]) ==1 && abs(position[1]-targetposition[1]) ==1 \
				&& GetPiecePtrGivenPos(targetposition)!=NULL)){
					cout << "Here" << endl;
				return MOVE_VALID;
			}
		}

		//piece to be moved it white and its one square straight
		if(this->getPieceColour() ==1\
			&& position[0] == targetposition[0]
			&& Check_If_Blocked_Vertical(position, targetposition)==0){//the piece to be moved is black
			if(targetposition[1]-position[1] ==1){
				cout << "Here" << endl;
				return MOVE_VALID;
			}
		}
		if(this->getPieceColour() ==1){//the piece to be moved is white and it is a diagonal move
			//gonna subtract from the number part to move down the board
			if((targetposition[0]-position[0] ==1 && targetposition[1]-position[1] ==1\
			&& GetPiecePtrGivenPos(targetposition)!=NULL)){
				cout << "Here" << endl;
				return MOVE_VALID;
			}
		}


	}
	return PAWN_INVALID_MOVE;//dummy return
}

int Pawn::Check_If_Blocked_Vertical(const string &position, const string &targetposition){
	//this function will return zero if the piece is not blocked in its path
	//this function will return an error number if the path is blocked
	//straight in front

	if(this->getPieceColour()==true){// function for white pawn
		for(int i=1; i<(targetposition[1]-position[1]+1); i++){
			string temp;
			temp+=position[0];
			temp+=i+position[1];
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}

		}
	}

	if(this->getPieceColour()==false){// function for black pawn
		for(int i=1; i<(position[1]-targetposition[1]+1); i++){// 1 starting as dont want to check itself!
			string temp;
			temp+=position[0];
			temp+=position[1]-i;
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}
		}
	}

	return MOVE_VALID;


}

int Piece::Check_If_Blocked_Vertical(const string &position, const string &targetposition){

	/*
	Checks up to but not including destination position for occupation
	*/


	if(position[1] >targetposition[1]){ // moving down the board from the black side to the white side
		for(int i=1; i<(position[1]-targetposition[1]); i++){// 1 starting as dont want to check itself!
			string temp;
			temp+=position[0];
			temp+=position[1]-i;
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}
		}
	}

	if(targetposition[1] >position[1]){// moving up the board!
		for(int i=1; i<(targetposition[1]-position[1]); i++){
			string temp;
			temp+=position[0];
			temp+=i+position[1];
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}

		}
	}

	return MOVE_VALID;

}

int Piece::Check_If_Blocked_Horizontal(const string &position, const string &targetposition){

	/*
	this function will return zero if the piece is not blocked in its path
	this function will return an error number if the path is blocked
	Checks up to but not including destination position for occupation
	*/
	if(position[0] >targetposition[0]){ // moving down the board from the black side to the white side
		for(int i=1; i<(position[0]-targetposition[0]); i++){// 1 starting as dont want to check itself!
			string temp;
			temp+=position[0]-i;
			temp+=position[1];
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}
		}
	}

	if(targetposition[0] >position[0]){// moving up the board!
		for(int i=1; i<(targetposition[0]-position[0]); i++){
			string temp;
			temp+=i+position[0];
			temp+=position[1];
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}

		}
	}

	return MOVE_VALID;
}

int Piece::Check_If_Blocked_Diag(const string &position, const string &targetposition){


	/*
	this function will return zero if the piece is not blocked in its path
	this function will return an error number if the path is blocked
	Checks up to but not including destination position for occupation
	*/

	if(targetposition[0] -position[0]>0 && targetposition[1]-position[1]>0){ // moving down the board from the black side to the white side
		#ifdef COMMENTS_ON
		cout << "MOVING Example A1->D4 " <<endl;
		#endif
		for(int i=1; i<(targetposition[1]-position[1]); i++){// 1 starting as dont want to check itself!
			string temp;
			temp+=position[0]+i;
			temp+=position[1]+i;
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}
		}
	}

	if(position[0] -targetposition[0]>0 && position[1]-targetposition[1]>0){// moving up the board!
		#ifdef COMMENTS_ON
		cout << "MOVING Example D4->A1 " <<endl;
		#endif
		for(int i=1; i<(position[0]-targetposition[0]); i++){
			string temp;
			temp+=position[0]-i;
			temp+=position[1]-i;
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}

		}
	}

	if(position[0] -targetposition[0]>0 && targetposition[1]-position[1]>0){// moving up the board!
		#ifdef COMMENTS_ON
		cout << "MOVING Example D1->A4 " <<endl;
		#endif
		for(int i=1; i<(targetposition[1]-position[1]); i++){
			string temp;
			temp+=position[0]-i;
			temp+=position[1]+i;
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}

		}
	}
	if(targetposition[0] -position[0]>0 && position[1]-targetposition[1]>0){// moving up the board!
		#ifdef COMMENTS_ON
		cout << "MOVING Example A4->D1 " <<endl;
		#endif
		for(int i=1; i<(position[1]-targetposition[1]); i++){
			string temp;
			temp+=position[0]+i;
			temp+=position[1]-i;
			//find the piece at each of those locations on the way
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}

		}
	}



return MOVE_VALID;



}
