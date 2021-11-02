//
//  Board.hpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#ifndef Board_hpp
#define Board_hpp

#include "Header.h"

#define		BOARD_OCCUPATION_W	2/3		// 画面の大きさに対する盤面の大きさ（横幅が基準）
#define		PIECE_OCCUPATION	2/3		// マスの大きさに対するコマの大きさ

class Board {
public:
	// コンストラクタ
	Board(int arg_board_squares, Point arg_draw_position, SquareStatus::Type arg_player_color);
	
	// コマの色の逆を取得
	SquareStatus::Type getEnemyPieceColor(SquareStatus::Type arg_ally_piece_color);
	
	// コマの描画
	void drawPiece(int x, int y);
	
	// 描画
	void draw();
	
private:
	// 盤面のマス数（縦横一列）
	int board_squares;
	
	// 盤面のサイズ
	Size board_size;
	
	// 描画の中心座標
	Point draw_position;
	
	// 1マスあたりの大きさ
	int square_size;
	
	// 枠線の色
	Color line_color	= Palette::White;
	
	// プレイヤーの色とAIの色
	SquareStatus::Type	player_square_color;
	SquareStatus::Type	AI_square_color;
	
	// マス配列
	Grid<SquareStatus::Type> current_grid;
	
	// マスの位置
	Grid<Point> square_position;
	
	// マス用図形
	Grid<Rect> square_rects;
};

#endif /* Board_hpp */
