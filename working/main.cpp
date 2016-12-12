 #include <iostream>

 using namespace std;

 #include "Chessboard.h"
 #include "Pieces.h"

 int main() {
 Chessboard cb;

 cout<<"CHECKING BISHOP"<<endl<<endl;



cout<<"moves should be allowed"<<endl<<endl;



cb.submitMove("D2", "D4");

cb.submitMove("D7", "D5");

cout<<endl;



cb.submitMove("E2", "E4");

cb.submitMove("E7", "E5");

cout<<endl;



cb.submitMove("C1", "D2");

cb.submitMove("F8", "B4");

cout<<endl;



cb.submitMove("F1", "C4");

cb.submitMove("C8", "G4");

cout<<endl;



cout<<"moves shouldn't be allowed:"<<endl<<endl;

cb.submitMove("C4", "B4");

cb.submitMove("C4", "A2");

cb.submitMove("C4", "A7");

cb.submitMove("C4", "H9");

cb.submitMove("C4", "G8");

cb.submitMove("c4", "d3");

cb.submitMove("D2", "E3"); // this is passing!





return 0;


 }
