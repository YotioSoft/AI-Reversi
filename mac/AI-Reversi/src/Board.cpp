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

// 各方向の取得可能なコマ数を算出
HashTable<Direction::Type, int> Board::calcObtainPoints(SquareStatus::Type arg_subject_color, Point arg_start_position) {
	HashTable<Direction::Type, int> ret;
	
	// 各方向に対してひっくり返せるコマ数をカウント
	for (auto d : direction_vec) {
		ret[d.first] = 0;
		if (current_grid[arg_start_position] == arg_subject_color) {
			break;
		}
		
		Point current_position = arg_start_position + d.second;
		
		while (isPositionValid(current_position)) {
			if (current_grid[current_position] != getEnemyPieceColor(arg_subject_color)) {
				break;
			}
			
			ret[d.first] ++;
			current_position += d.second;
		}
		// 同じ色で挟めていなければ0点
		if (current_grid[current_position] != arg_subject_color) {
			ret[d.first] = 0;
		}
	}
	
	return ret;
}

// 取得可能なコマ数の総計
int Board::calcTotalObtainPoints(HashTable<Direction::Type, int> arg_points_table) {
	int total_points = 0;
	
	for (auto t : arg_points_table) {
		total_points += t.second;
	}
	
	return total_points;
}

// コマを置く（注：呼び出し時にマスに置けるか判定済みであることが必須）
void Board::putPiece(HashTable<Direction::Type, int> arg_obtain_points_table, SquareStatus::Type arg_subject_color, Point arg_position) {
	current_grid[arg_position] = arg_subject_color;
	
	// コマをひっくり返す
	for (auto t : arg_obtain_points_table) {
		if (t.second == 0) {
			continue;
		}
		
		Point current_position = arg_position + direction_vec[t.first];
		while (isPositionValid(current_position)) {
			if (current_grid[current_position] != getEnemyPieceColor(arg_subject_color)) {
				break;
			}
			
			turnOver(current_position);
			current_position += direction_vec[t.first];
		}
	}
}

// コマをひっくり返す
void Board::turnOver(Point arg_position) {
	current_grid[arg_position] = getEnemyPieceColor(current_grid[arg_position]);
}

// 座標が有効か
bool Board::isPositionValid(Point arg_position) {
	if (arg_position.x < 0 || arg_position.y < 0) {
		return false;
	}
	else if (arg_position.x >= board_squares || arg_position.y >= board_squares) {
		return false;
	}
	
	return true;
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
			// マウスオーバー時
			if (square_rects[y][x].mouseOver()) {
				HashTable<Direction::Type, int> obtain_points_table = calcObtainPoints(SquareStatus::White, Point(x, y));
				int total_obtain_points = calcTotalObtainPoints(obtain_points_table);
				
				// コマが置ける場合
				if (total_obtain_points > 0) {
					square_rects[y][x].draw(BACKGROUND_COLOR_HILIGHT).drawFrame(1, line_color);
					
					if (square_rects[y][x].leftReleased()) {
						putPiece(obtain_points_table, SquareStatus::White, Point(x, y));
					}
				}
				// コマが置けない場合
				else {
					square_rects[y][x].draw(BACKGROUND_COLOR).drawFrame(1, line_color);
				}
			}
			// それ以外
			else {
				square_rects[y][x].draw(BACKGROUND_COLOR).drawFrame(1, line_color);
			}
			
			// コマの描画
			drawPiece(x, y);
		}
	}
}
