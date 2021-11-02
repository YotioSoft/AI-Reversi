/*
			AI-Reversi
		(C) 2021 YotioSoft
 */

#include "Header.h"
#include "Screen.hpp"
#include "Board.hpp"

void Main() {
	Window::SetTitle(U"AI Reversi");
	
	// 背景色
	Scene::SetBackground(BACKGROUND_COLOR);

	// 盤面の宣言
	Board board(8, (Scene::Size()/2), SquareStatus::White);
	
	// メインスクリーンへ
	mainScreen(board);
}
