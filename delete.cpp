int Chessboard::Check_All_Possible_Moves(string position){

	Piece* piece;
	#ifdef COMMENTS_ON
	cout << "Entering Check_All_Possible_Moves for " << position<<endl;
	#endif
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
		if(testmoveint==0 && piece_possible_moves[i]== Where_is_the_king(false)&& \
		(find(positions_threatening_bking.begin(), positions_threatening_bking.end(), position) ==\
		 positions_threatening_bking.end()) &&piece->getPieceColour()==true){
			cout<< "adding to the threatening the black king list" <<endl;
			this->positions_threatening_bking.push_back(position);
		}
		if(testmoveint==0 && piece_possible_moves[i]== Where_is_the_king(true)&& \
		(find(positions_threatening_bking.begin(), positions_threatening_bking.end(), position) ==\
		 positions_threatening_bking.end())&&piece->getPieceColour()==false ){
			this->positions_threatening_wking.push_back(position);
		}
	}


	//possible moves vector
	#ifdef POSSIBLE_MOVES_PRINT
	cout <<"PM for "<<piece->getPieceName() << "\t" << "[";

	for(unsigned int i =0; i < piece->actual_possible_moves.size(); i++){
		cout << piece->actual_possible_moves[i]  << " ";
	}
	cout <<"]" <<endl;
	#endif
	return MOVE_VALID;


}// end of Check_All_Possible_Moves function
