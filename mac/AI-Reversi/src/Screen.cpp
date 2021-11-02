//
//  Screen.cpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#include "Screen.hpp"

void mainScreen(Board& board) {
	while (System::Update()) {
		board.draw();
	}
}

