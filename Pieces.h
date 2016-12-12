#ifndef PIECES_H
#define PIECES_H
#include <string>
#include <cmath>
#include <vector>

class ChessBoard; //forward declare chessboard as will use it in the constructor

using namespace std;

class Piece{
private:


protected:
ChessBoard* chessboardptr;
string position; // example "C4"
bool piececolour; //true if black
string name; //example



Piece* GetPiecePtrGivenPos(string position);
int Check_If_Blocked_Vertical(const string &position, const string &targetposition); //overridden in some classes
int Check_If_Blocked_Horizontal(const string &position, const string &targetposition);//checks if blocked horiztonally
int Check_If_Blocked_Diag(const string &position, const string &targetposition);
public:
Piece(bool _colour, string _name, string _position, ChessBoard* chessboardptr);
string getPieceName();
string getPosition();
bool getPieceColour();
virtual int makemove(const string &position, const string &targetposition)=0;
vector<string> actual_possible_moves;
bool firstmove =1;
virtual ~Piece();




};//end of piece definition


class Queen:public Piece{
	public:
	Queen(string _name,bool _colour, string _position, ChessBoard* chessboardptr);
	 int makemove(const string &position, const string &targetposition);

};
class Rook:public Piece{
	public:
	Rook(string _name,bool _colour, string _position, ChessBoard* chessboardptr);
	 int makemove(const string &position, const string &targetposition);

};
class Bishop:public Piece{
	public:
	Bishop(string _name,bool _colour, string _position, ChessBoard* chessboardptr);
	int makemove(const string &position, const string &targetposition);


};
class King:public Piece{
	public:
	King( string _name,bool _colour, string _position, ChessBoard* chessboardptr);
	 int makemove( const string &position, const string &targetposition);
	//virtual bool makemove(string position, string targetposition);
};
class Pawn:public Piece{
	public:
	Pawn(string _name,bool _colour, string _position, ChessBoard* chessboardptr);
	 int makemove(const string &position, const string &targetposition);


    private:
// bool firstmove; //true if first move, false if not
int Check_If_Blocked_Vertical(const string &position, const string &targetposition); //checks if something is blocking vertically in a straight line

};
class Knight:public Piece{
	public:
	Knight(string _name,bool _colour, string _position, ChessBoard* chessboardptr);
	 int makemove(const string &position, const string &targetposition);
};




#endif
