#include <Header.h>
#include <Screen.hpp>
#include <Board.hpp>

void Main() {
	Window::SetTitle(U"AI Reversi");

	// 背景色
	Scene::SetBackground(BACKGROUND_COLOR);

	// 盤面の宣言
	Board board(8, (int)(Scene::Size().x / 2), (int)(Scene::Size().y / 2), SquareStatus::White);

	// フォントの宣言
	FontAsset::Register(U"Medium", 30, Typeface::Medium);

	// メインスクリーンへ
	mainScreen(board);
}

