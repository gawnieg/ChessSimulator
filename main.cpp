 #include <iostream>

 using namespace std;

 #include "Chessboard.h"
 #include "Pieces.h"

 int main() {


Chessboard cb;






     cout << "===========================" << endl;
     cout << "Testing the Chess Engine" << endl;
     cout << "===========================" << endl;
     cout << endl;


     cout << endl;

     cb.submitMove("C2", "C4");


      cout << "===========================" << endl;
      cout << "Second Move" << endl;
      cout << "===========================" << endl;
      cout << endl;

     cb.submitMove("F8", "E7");

     cout << "===========================" << endl;
     cout << "Third Move" << endl;
     cout << "===========================" << endl;
     cout << endl;

 cb.submitMove("C4", "C5");


cout << "End of main" << endl;
     cout << endl;
     return 0;

 //cb.submitMove("B4", "B5");
/*
     cb.submitMove("D4", "H6");
     cout << endl;

     cb.submitMove("D2", "D4");
     cout << endl;

     cb.submitMove("F8", "B4");
     cout << endl;

     cout << "===========================" << endl;
     cout << "Alekhine vs. Vasic (1931)" << endl;
     cout << "===========================" << endl;
     cout << endl;

     cb.resetBoard();
     cout << endl;

     cb.submitMove("E2", "E4");
     cb.submitMove("E7", "E6");
     cout << endl;

     cb.submitMove("D2", "D4");
     cb.submitMove("D7", "D5");
     cout << endl;

     cb.submitMove("B1", "C3");
     cb.submitMove("F8", "B4");
     cout << endl;

     cb.submitMove("F1", "D3");
     cb.submitMove("B4", "C3");
     cout << endl;

     cb.submitMove("B2", "C3");
     cb.submitMove("H7", "H6");
     cout << endl;

     cb.submitMove("C1", "A3");
     cb.submitMove("B8", "D7");
     cout << endl;

     cb.submitMove("D1", "E2");
     cb.submitMove("D5", "E4");
     cout << endl;

     cb.submitMove("D3", "E4");
     cb.submitMove("G8", "F6");
     cout << endl;

     cb.submitMove("E4", "D3");
     cb.submitMove("B7", "B6");
     cout << endl;

     cb.submitMove("E2", "E6");
     cb.submitMove("F7", "E6");
     cout << endl;

     cb.submitMove("D3", "G6");
     cout << endl;
 */


 }
