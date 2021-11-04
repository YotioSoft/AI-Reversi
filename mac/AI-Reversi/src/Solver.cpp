//
//  Solver.cpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#include "Solver.hpp"

// コンストラクタ
Solver::Solver(SquareStatus::Type arg_AI_color, Board current_board) {
	// ツリーの生成
	root_node = Node(current_board);
	Node* current_node = &root_node;
	
	// シミュレーション中のターン
	AI_color = arg_AI_color;
	SquareStatus::Type sim_color = AI_color;
	
	// 探索開始
	best_result = minMax(*current_node, sim_color, SOLVE_DEPTH);
}

// 探索
SolveResult Solver::minMax(Node& parent_node, SquareStatus::Type sim_color, int depth) {
	int best_points;
	if (sim_color == AI_color) {
		best_points = INT_MIN;
	}
	else {
		best_points = INT_MAX;
	}
	Array<Point> best_way;
	int obtain_points;
	
	int decision_count = 0;
	
	for (int y=0; y<parent_node.getBoard()->getBoardSquares(); y++) {
		for (int x=0; x<parent_node.getBoard()->getBoardSquares(); x++) {
			obtain_points = 0;
			
			HashTable<Direction::Type, int> obtain_points_table = parent_node.getBoard()->calcObtainPoints(sim_color, Point(x, y));
			int total_obtain_points = parent_node.getBoard()->calcTotalObtainPoints(obtain_points_table);
			
			if (total_obtain_points == 0) {
				continue;
			}
			decision_count ++;
			
			if (sim_color == AI_color) {
				std::cout << "depth: " << depth << "AI obtain at " << x << "," << y << " : " << total_obtain_points <<std::endl;
			}
			else {
				std::cout << "depth: " << depth << "Player obtain at " << x << "," << y << " : " << total_obtain_points <<std::endl;
			}
			
			// 盤面をコピー
			Board child_node_board = *parent_node.getBoard();
			
			// コピーした盤面でコマを置く
			child_node_board.putPiece(obtain_points_table, sim_color, Point(x, y));
			
			// 子ノード生成
			Node child_node(child_node_board);
			
			// 子ノード探索
			if (depth >= 1) {
				SolveResult solve_result = minMax(child_node, parent_node.getBoard()->getEnemyPieceColor(sim_color), depth-1);
				
				if (sim_color == AI_color) {
					obtain_points = total_obtain_points + solve_result.value;
					
					if (best_points <= obtain_points) {
						best_points = obtain_points;
						best_way = {Point(x, y)};
						best_way.append(solve_result.best_way);
					}
				}
				else {
					obtain_points = -total_obtain_points + solve_result.value;
					
					if (best_points >= obtain_points) {
						best_points = obtain_points;
						best_way = {Point(x, y)};
						best_way.append(solve_result.best_way);
					}
				}
				
				// 親ノードに追加
				parent_node.addChild(&child_node);
			}
			else {
				if (sim_color == AI_color) {
					obtain_points = total_obtain_points;
					
					if (best_points <= obtain_points) {
						best_points = obtain_points;
						best_way = {Point(x, y)};
					}
				}
				else {
					obtain_points = -total_obtain_points;
					
					if (best_points >= obtain_points) {
						best_points = obtain_points;
						best_way = {Point(x, y)};
					}
				}
			}
		}
	}
	
	SolveResult result = {
		best_points,
		best_way
	};
	
	return result;
}

// AIの一手を返す
Board Solver::getSolvedBoard() {
	if (best_result.best_way.size() == 0) {
		std::cout << "GAME SET" << std::endl;
		return *root_node.getBoard();
	}
	
	Point best_point = best_result.best_way[0];
	HashTable<Direction::Type, int> obtain_points_table = root_node.getBoard()->calcObtainPoints(AI_color, best_point);
	root_node.getBoard()->putPiece(obtain_points_table, AI_color, best_point);
	
	return *root_node.getBoard();
}
