//
//  Solver.cpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#include "Solver.hpp"

// コンストラクタ
Solver::Solver(SquareStatus::Type AI_color, Board current_board) {
	// ツリーの生成
	root_node = Node(current_board);
	Node* current_node = &root_node;
	
	// シミュレーション中のターン
	SquareStatus::Type sim_color = AI_color;
	
	// 各ターンで置けるとこに置く
	for (int depth=0; depth<SOLVE_DEPTH; depth++) {
		for (int y=0; y<current_board.getBoardSquares(); y++) {
			for (int x=0; x<current_board.getBoardSquares(); x++) {
				HashTable<Direction::Type, int> obtain_points_table = current_board.calcObtainPoints(sim_color, Point(x, y));
				int total_obtain_points = current_board.calcTotalObtainPoints(obtain_points_table);
				
				if (total_obtain_points == 0) {
					continue;
				}
				
				// 盤面をコピー
				Board child_node_board = current_board;
				
				// コピーした盤面でコマを置く
				child_node_board.putPiece(obtain_points_table, sim_color, Point(x, y));
				
				// ノード生成
				Node child_node(child_node_board);
				
				// 親ノードに追加
				current_node->addChild(&child_node);
			}
		}
		
		// ターン切り替え
		sim_color = current_board.getEnemyPieceColor(sim_color);
	}
}
