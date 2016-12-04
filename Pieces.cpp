#include "Pieces.h"
#include <string>
#include <iostream>
#include "Chessboard.h"
#include "errors.h"



using namespace std;

Piece::Piece(bool _colour, string _name, string _position, Chessboard* _chessboardptr ){

	cout<< "Constructing piece"<<endl;
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






Queen::Queen( string _name, bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
	//Queen constuctor
	}
King::King( string _name,bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
		//King constructor
	}
Knight::Knight( string _name,bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
		//Knight constructor
	}



Rook::Rook( string _name, bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
		//Rook constructor

	}

int Rook::makemove(string position, string targetposition){
	cout << "Rook version of makemove is called" << endl;
	cout << "This Rook's colour is " << this->getPieceColour() << endl;
	cout << "This Rooks name " << this-> getPieceName() << endl;

	cout << "position[1] is " << position[1] <<endl;
	cout << "targetposition[1] is " << targetposition[1] <<endl;
	cout << "targetposition[1] - position[1]" << targetposition[1]-position[1] <<endl;
	cout << "position[0] is " << position[0] <<endl;
	cout << "targetposition[0] is " << targetposition[0] <<endl;
	cout << "targetposition[1] - position[1]" << targetposition[0]-position[0] <<endl;



		//gonna subtract from the number part to move down the board
		//vertical movement
		if(((position[1]-targetposition[1] >=1 || targetposition[1]-position[1] >=1)\
		&& position[0] == targetposition[0])\
		&& Check_If_Blocked_Vertical(position, targetposition)==0 ){
			cout << "move requested for rook is ok! and not blocked,can move rook vertically "<<\
			abs(position[1]-targetposition[1]) << "spaces vertically "<<endl;
			return 0;
		}
		//horizontal movement
		if(((position[0] -targetposition[0] >=1 ||targetposition[0]-position[0] >=1)\
		&&position[1]==targetposition[1])&& \
		Check_If_Blocked_Horizontal(position, targetposition)==0){
			cout << "move requested for rook is ok! and not blocked,can move rook horiztonally" <<\
			 abs(targetposition[0]-position[0])<< "spaces horizontally" <<endl;
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
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
Pawn::Pawn(string _name,bool _colour, string _position, Chessboard* chessboardptr):\
	Piece(_colour, _name, _position, chessboardptr)	{
		//Pawn constructor
		firstmove=true;
	}

int Piece::makemove(string position, string targetposition){
return 0; //dummy return this should never be used!
//intentionally blank
}






int Pawn::makemove(string position, string targetposition){
	/*this function takes in the current position and the target position and
	returns true if the move can be made corresponding to the pawn's regulations
	This function will be called from Chessboard::submitMove.
	Will this function also account for pieces in the way???
	returns true if the move can be made.
	returns false if the move is legit.
	*/
	cout << "Pawn version of makemove is called" << endl;
	cout << "First move? " << firstmove <<endl;
	cout << "This pawns colour is " << this->getPieceColour() << endl;
	cout << "This pawns name " << this-> getPieceName() << endl;

	cout << "position[1] is " << position[1] <<endl;
	cout << "targetposition[1] is " << targetposition[1] <<endl;
	cout << "targetposition[1] - position[1]" << targetposition[1]-position[1] <<endl;
	cout << "position[0] is " << position[0] <<endl;
	cout << "targetposition[0] is " << targetposition[0] <<endl;
	cout << "targetposition[1] - position[1]" << targetposition[0]-position[0] <<endl;

//something wrong with colours!!!!

	if(firstmove==true){
		//if the firstmove is true, then can move two spaces forward
		cout << "This is the pawns first move" << endl;
		if(this->getPieceColour() ==0){//the piece to be moved is black
			//gonna subtract from the number part to move down the board
			if((position[1]-targetposition[1] ==2||position[1]-targetposition[1] ==1) \
			&& Check_If_Blocked_Vertical(position, targetposition)==0){
				cout << "move requested is ok! and not blocked,can move pawn forwards "<<\
				position[1]-targetposition[1] << "spaces" <<endl;
				firstmove=false; //set firstmove to false as its firstmove has been completed
				return 0;
			}
		}
		if(this->getPieceColour() ==1){//the piece to be moved is black
			//gonna subtract from the number part to move down the board
			if((targetposition[1]-position[1] ==2||targetposition[1]-position[1] ==1)\
			&& Check_If_Blocked_Vertical(position, targetposition)==0){
				cout << "move requested is ok! can move pawn forwards "<<\
				targetposition[1]-position[1] << " spaces" <<endl;
				firstmove=false; //set firstmove to false as its firstmove has been completed
				return 0;
			}
		}

	}
	else{ //not first move, can only move one square
		//piece to be moved it black and its one square straight
		if(this->getPieceColour() ==0){//the piece to be moved is black
			//gonna subtract from the number part to move down the board
			if(position[1]-targetposition[1] ==1\
				 && Check_If_Blocked_Vertical(position, targetposition)==0){
				cout << "move requested is ok! ,can move pawn forwards "<<\
				position[1]-targetposition[1] << "spaces" <<endl;
				firstmove=false; //set firstmove to false as its firstmove has been completed
				return 0;
			}
		}
		//now diagonal kill move
		if(this->getPieceColour() ==0){//the piece to be moved is black. checking if blocked not
			//required as will be taking a piece if moving diagonnally
			//gonna subtract from the number part to move down the board
			if((position[0]-targetposition[0] ==1 && position[1]-targetposition[1] ==1)){
				cout << "move requested is ok! ,can move pawn diagonally for the kill "<<\
				position[0]-targetposition[0] << "spaces" <<endl;
				firstmove=false; //set firstmove to false as its firstmove has been completed
				return 0;
			}
		}

		//piece to be moved it white and its one square straight
		if(this->getPieceColour() ==1\
			&& Check_If_Blocked_Vertical(position, targetposition)==0){//the piece to be moved is black
			//gonna subtract from the number part to move down the board
			if(targetposition[1]-position[1] ==1){
				cout << "move requested is ok! can move pawn forwards "<<\
				targetposition[1]-position[1] << " spaces" <<endl;
				firstmove=false; //set firstmove to false as its firstmove has been completed
				return 0;
			}
		}
		if(this->getPieceColour() ==0){//the piece to be moved is white and it is a diagonal move
			//gonna subtract from the number part to move down the board
			if((targetposition[0]-position[0] ==1 && targetposition[1]-position[1] ==1)){
				cout << "move requested is ok! ,can move pawn diagonally for the kill "<<\
				targetposition[0]-position[0] << "spaces" <<endl;
				firstmove=false; //set firstmove to false as its firstmove has been completed
				return 0;
			}
		}


	}

	cout <<"move not valid due to pawn requirements for a move!" <<endl;
	return PAWN_INVALID_MOVE;//dummy return
}

int Pawn::Check_If_Blocked_Vertical(const string &position, const string &targetposition){
	//this function will return zero if the piece is not blocked in its path
	//this function will return an error number if the path is blocked
	cout << "checking if blocked vertically on its way" <<endl;
	//straight in front

	if(this->getPieceColour()==true){// function for white pawn
		for(int i=1; i<(targetposition[1]-position[1]+1); i++){
			string temp;
			temp+=position[0];
			temp+=i+position[1];
			//find the piece at each of those locations on the way
			cout << "checking" <<temp << "for obstruction" <<endl;
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
			cout << "checking" <<temp << "for obstruction" <<endl;
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}
		}
	}




	return 0;


}

int Piece::Check_If_Blocked_Vertical(const string &position, const string &targetposition){
	cout << "generic piece class checking if blocked vertically on its way" <<endl;
	/*
	Checks up to but not including destination position for occupation
	*/


	if(position[1] >targetposition[1]){ // moving down the board from the black side to the white side
		for(int i=1; i<(position[1]-targetposition[1]); i++){// 1 starting as dont want to check itself!
			string temp;
			temp+=position[0];
			temp+=position[1]-i;
			//find the piece at each of those locations on the way
			cout << "checking" <<temp << "for obstruction" <<endl;
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
			cout << "checking" <<temp << "for obstruction" <<endl;
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}

		}
	}

	return 0;

}

int Piece::Check_If_Blocked_Horizontal(const string &position, const string &targetposition){

	/*
	this function will return zero if the piece is not blocked in its path
	this function will return an error number if the path is blocked
	Checks up to but not including destination position for occupation
	*/
	cout << "generic piece class checking if blocked vertically on its way" <<endl;
	if(position[0] >targetposition[0]){ // moving down the board from the black side to the white side
		for(int i=1; i<(position[0]-targetposition[0]); i++){// 1 starting as dont want to check itself!
			string temp;
			temp+=position[0]-i;
			temp+=position[1];
			//find the piece at each of those locations on the way
			cout << "checking" <<temp << "for obstruction" <<endl;
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
			cout << "checking" <<temp << "for obstruction" <<endl;
			if(chessboardptr->Check_If_Piece_Active(temp)==1){
				return PIECE_BLOCKED;
			}

		}
	}

	return 0;
}