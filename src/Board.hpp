//
//  Board.hpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#pragma once

#ifndef Board_hpp
#define Board_hpp

#include "Header.h"

#define		BOARD_OCCUPATION_W	3/5		// 画面の大きさに対する盤面の大きさ（横幅が基準）
#define		PIECE_OCCUPATION	2/3		// マスの大きさに対するコマの大きさ

class Board {
public:
	// コンストラクタ
	Board();
	Board(int arg_board_squares, int arg_draw_position_x, int arg_draw_position_y, SquareStatus::Type arg_player_color);
	
	// コマの色の逆を取得
	SquareStatus::Type getEnemyPieceColor(SquareStatus::Type arg_ally_piece_color);
	
	// 各方向の取得可能なコマ数を算出
	HashTable<Direction::Type, int> calcObtainPoints(SquareStatus::Type arg_subject_color, Point arg_start_position);
	
	// 取得可能なコマ数の総計
	int calcTotalObtainPoints(HashTable<Direction::Type, int> arg_points_table);
	
	// コマを置く（注：呼び出し時にマスに置けるか判定済みであることが必須）
	void putPiece(HashTable<Direction::Type, int> arg_obtain_points_table, SquareStatus::Type arg_subject_color, Point arg_position);
	
	// コマをひっくり返す
	void turnOver(Point arg_position);
	
	// 次のターンへ
	void nextTurn();
	
	// 座標が有効か
	bool isPositionValid(Point arg_position);
	
	// AIのターンか
	bool isAIturn();
	
	// AIの色
	SquareStatus::Type getAIcolor();
	
	// 盤面のサイズを取得
	int getBoardSquares();
	
	// 点数を取得
	int getPlayerPoints();
	int getAIPoints();
	
	// コマの色の取得
	Color getPieceColor(SquareStatus::Type arg_color);
	
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
	
	Circle player_points_icon;
	Circle AI_points_icon;
	
	// 各プレイヤーの点数
	int player_points;
	int AI_points;
	
	// 現在のターン
	SquareStatus::Type	current_turn_color;
	int turn_number;
	
	// マス配列
	Grid<SquareStatus::Type> current_grid;
	
	// マスの位置
	Grid<Point> square_position;
	
	// マス用図形
	Grid<Rect> square_rects;
	
	// 各方向のベクトル
	HashTable<Direction::Type, Point> direction_vec = {
		{Direction::UpperLeft,	Point{-1, -1}},
		{Direction::Up,			Point{ 0, -1}},
		{Direction::UpperRight,	Point{ 1, -1}},
		{Direction::Right,		Point{ 1,  0}},
		{Direction::LowerRight,	Point{ 1,  1}},
		{Direction::Low,		Point{ 0,  1}},
		{Direction::LowerLeft,	Point{-1,  1}},
		{Direction::Left,		Point{-1,  0}}
	};
};

#endif /* Board_hpp */
