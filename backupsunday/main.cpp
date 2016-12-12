 #include <iostream>

 using namespace std;

 #include "Chessboard.h"
 #include "Pieces.h"

 int main() {
 Chessboard cb;



  cout<<"CHECKING PAWN"<<endl<<endl;

  cout<<"moves should be allowed"<<endl<<endl;



  cb.submitMove("D2", "D4");

  cb.submitMove("D7", "D5");

  cout<<endl;



  cb.submitMove("E2", "E4");

  cb.submitMove("E7", "E5");

  cout<<endl;



  cb.submitMove("F2", "F3");

  cb.submitMove("F7", "F6");

  cout<<endl;



  cb.submitMove("H2", "H4");

  cb.submitMove("A7", "A5");

  cout<<endl;



  cb.submitMove("C1", "H6");

  cb.submitMove("F8", "A3");

  cout<<endl;



  cout<<"moves shouldn't be allowed:"<<endl<<endl;

  cb.submitMove("D4", "D5");

  cb.submitMove("D4", "C5");

  cb.submitMove("D4", "E6");

  cb.submitMove("d4", "E5");

  cb.submitMove("84", "E5");

  cb.submitMove("D4", "C4");

  cb.submitMove("D4", "D3");

  cb.submitMove("D4", "D2");

  cb.submitMove("D4", "I4");

  cb.submitMove("A2", "A4");

  cb.submitMove("A2", "A3");

  cb.submitMove("F3", "E4");

  cb.submitMove("H7", "H5");

  cout<<endl;



  cout<<"moves should be allowed, taking pieces:"<<endl<<endl;



  cb.submitMove("D4", "E5");

  cb.submitMove("F6", "E5");

  cout<<endl;



  // cb.resetBoard();






return 0;


 }
