//
//  Board.cpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#include "Board.hpp"

// コンストラクタ
Board::Board(int arg_board_squares, Point arg_draw_position, SquareStatus::Type arg_player_color) {
	board_squares	= arg_board_squares;
	draw_position	= arg_draw_position;
	
	current_grid	= Grid<SquareStatus::Type>(board_squares, board_squares, SquareStatus::None);
	
	player_square_color	= arg_player_color;
	AI_square_color		= getEnemyPieceColor(player_square_color);
	
	// 画面の大きさとマス数から盤面のサイズと1マスあたりの大きさを決定
	board_size.x	= Scene::Size().x * BOARD_OCCUPATION_W;
	board_size.y	= board_size.x;
	square_size		= board_size.x / board_squares;
	
	// 盤面の初期化（中央4マスにコマを配置）
	current_grid[board_squares/2-1][board_squares/2-1]		= SquareStatus::White;
	current_grid[board_squares/2][board_squares/2]			= SquareStatus::White;
	current_grid[board_squares/2][board_squares/2-1]		= SquareStatus::Black;
	current_grid[board_squares/2-1][board_squares/2]		= SquareStatus::Black;
	
	// 各マスの位置
	square_position	= Grid<Point>(board_squares, board_squares);
	square_rects	= Grid<Rect>(board_squares, board_squares);
	// 盤面用図形
	Rect board_rect(Arg::center(draw_position), board_size);
	for (int y=0; y<board_squares; y++) {
		for (int x=0; x<board_squares; x++) {
			square_position[y][x]	= Point(board_rect.x + square_size * x, board_rect.y + square_size * y);
			square_rects[y][x]		= Rect(square_position[y][x], Size(square_size, square_size));
		}
	}
}

// 逆の色を取得
SquareStatus::Type Board::getEnemyPieceColor(SquareStatus::Type arg_ally_piece_color) {
	return SquareStatus::Type(arg_ally_piece_color * -1);
}

// コマの描画
void Board::drawPiece(int x, int y) {
	if (current_grid[y][x] == SquareStatus::Black) {
		Circle piece(square_position[y][x] + Size(square_size / 2, square_size / 2), square_size / 2 * PIECE_OCCUPATION);
		piece.draw(Palette::Black);
	}
	else if (current_grid[y][x] == SquareStatus::White) {
		Circle piece(square_position[y][x] + Size(square_size / 2, square_size / 2), square_size / 2 * PIECE_OCCUPATION);
		piece.draw(Palette::White);
	}
	
	return;
}

// 描画
void Board::draw() {
	// 盤面用図形
	Rect board_rect(Arg::center(draw_position), board_size);
	
	// 盤面の描画
	for (int y=0; y<board_squares; y++) {
		for (int x=0; x<board_squares; x++) {
			// マスの描画
			if (square_rects[y][x].mouseOver()) {
				square_rects[y][x].draw(BACKGROUND_COLOR_HILIGHT).drawFrame(1, line_color);
			}
			else {
				square_rects[y][x].draw(BACKGROUND_COLOR).drawFrame(1, line_color);
			}
			
			// コマの描画
			drawPiece(x, y);
		}
	}
}
