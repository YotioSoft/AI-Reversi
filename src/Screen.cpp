//
//  Screen.cpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#include "Screen.hpp"

void mainScreen(Board& board) {
	int turn_change_count = 50;
	
	while (System::Update()) {
		board.draw();
		
		if (board.isAIturn()) {
			turn_change_count --;
			
			if (turn_change_count == 0) {
				Solver solver(board.getAIcolor(), board);
				board = solver.getSolvedBoard();
				board.nextTurn();
			}
		}
		else {
			turn_change_count = 50;
		}
	}
}

