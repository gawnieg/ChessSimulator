 #include <iostream>

 using namespace std;

 #include "Chessboard.h"
 #include "Pieces.h"

 int main() {


Chessboard cb;


//////////////////FOOLS MATE /////////////////
// cb.submitMove("F2", "F3");//move for stalemate play
// cb.submitMove("E7", "E5");//move for stalemate play
// cb.submitMove("G2", "G4");//move for stalemate play
// cb.submitMove("D8", "H4");//move for stalemate play
// ////??ENDOFFOOLSMATE//////////

// cb.submitMove("G1","G6");


//scholars mate!
// cb.submitMove("E2","E4");
// cb.submitMove("E7","E5");
//
// cb.submitMove("F1","C4");
// cb.submitMove("F8","C5");
//
// cb.submitMove("D1","H5");
// cb.submitMove("G8","F6");
//
// cb.submitMove("H5","F7"); // should be checkmate
//end of scholars mate


/*
     cout << "===========================" << endl;
     cout << "Testing the Chess Engine" << endl;
     cout << "===========================" << endl;
     cout << endl;
//
//
//      cout << endl;
//

//
//
//       cout << "===========================" << endl;
//       cout << "Second Move" << endl;
//       cout << "===========================" << endl;
//       cout << endl;
//
//      cb.submitMove("D7", "D6");
//
//      cout << "===========================" << endl;
//      cout << "Third Move" << endl;
//      cout << "===========================" << endl;
//      cout << endl;
//
//  cb.submitMove("C4", "C5");
//  cb.resetBoard();
//
// cout << "End of main" << endl;
//      cout << endl;
//      return 0;


     //
    //  cb.submitMove("D4", "H6");
    //  cout << endl;
     //
    //  cb.submitMove("D2", "D4");
    //  cout << endl;
     //
    //  cb.submitMove("F8", "B4");
    //  cout << endl;

*/


//////////////////////////////////////////STALEMATE PLAY???????????????????????????


/*
cout << endl;

cb.submitMove("E2", "E3");

cout << endl;

cb.submitMove("A7", "A5");

cout << endl;

cb.submitMove("D1", "H5");

cout << endl;

cb.submitMove("A8", "A6");

cout << endl;

cb.submitMove("H5", "A5");

cout << endl;

cb.submitMove("H7", "H5");

cout << endl;

cb.submitMove("H2", "H4");

cout << endl;

cb.submitMove("A6", "H6");

cout << endl;

cb.submitMove("A5", "C7");

cout << endl;

cb.submitMove("F7", "F6");

cout << endl;

cb.submitMove("C7", "D7");

cout << endl;

cb.submitMove("E8", "F7");

cout << endl;

cb.submitMove("D7", "B7");

cout << endl;

cb.submitMove("D8", "D3");

cout << endl;

cb.submitMove("B7", "B8");

cout << endl;

cb.submitMove("D3", "H7");

cout << endl;

cb.submitMove("B8", "C8");

cout << endl;

cb.submitMove("F7", "G6");

cout << endl;

cb.submitMove("C8", "E6");

cout << endl;

cb.submitMove("D7", "F6");

cout << endl;


*/



////////////////////////////////////END OF STALEMATE PLAy////////////////////////////////////











    cout << "===========================" << endl;
    cout << "Alekhine vs. Vasic (1931)" << endl;
    cout << "===========================" << endl;
    cout << endl;

     cb.resetBoard();
    cout << endl;

    cout << "===========================" << endl;
    cout << " 1 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("E2", "E4"); //ok
    cout << "===========================" << endl;
    cout << " 2 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("E7", "E6"); //ok
    cout << endl;
    cout << "===========================" << endl;
    cout << "3 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("D2", "D4");
    cout << "===========================" << endl;
    cout << "4 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("D7", "D5");
    cout << endl;


    cout << "===========================" << endl;
    cout << "5 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("B1", "C3");
    cout << "===========================" << endl;
    cout << "6 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("F8", "B4");
    cout << endl;
    cout << "===========================" << endl;
    cout << "7 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("F1", "D3");
    cout << "===========================" << endl;
    cout << "8 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("B4", "C3"); // in check after this????   CHECK this
    cout << endl;
    cout << "===========================" << endl;
    cout << "9 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("B2", "C3"); // fault here

    cout << "===========================" << endl;
    cout << " 10 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("H7", "H6");
    cout << endl;

    cout << "===========================" << endl;
    cout << "11 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("C1", "A3");

    cout << "===========================" << endl;
    cout << "12  Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("B8", "D7");

    cout << endl;
    cout << "===========================" << endl;
    cout << "13 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("D1", "E2");//gone ok

    cout << "===========================" << endl;
    cout << " 14 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("D5", "E4");

    cout << endl;
    cout << "===========================" << endl;
    cout << "15 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("D3", "E4");

    cout << "===========================" << endl;
    cout << "16 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("G8", "F6");
    cout << endl;

    cout << "===========================" << endl;
    cout << "17 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("E4", "D3"); //problematic

    cout << "===========================" << endl;
    cout << "18 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("B7", "B6");
    cout << endl;

    cout << "===========================" << endl;
    cout << "19 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("E2", "E6"); // in check I think for this one

    cout << "===========================" << endl;
    cout << "20 Move" << endl;
    cout << "===========================" << endl;
    cb.submitMove("F7", "E6");

    cout << endl;
    cout << "===========================" << endl;
    cout << "21 Move" << endl;
    cout << "===========================" << endl;

    cb.submitMove("D3", "G6");
    cout << endl;




 }
