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
	
	// 各階層における最良点の初期化
	depth_best_points.resize(SOLVE_DEPTH, 0);
	
	// 探索開始
	makeTree(*current_node, sim_color, SOLVE_DEPTH);
	best_result = minMax(*current_node, SOLVE_DEPTH);
}

// 探索
void Solver::makeTree(Node& parent_node, SquareStatus::Type sim_color, int depth) {
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
			Console << U"(x,y)=(" << x << U"," << y << U")";
			obtain_points = 0;
			
			HashTable<Direction::Type, int> obtain_points_table = parent_node.getBoard()->calcObtainPoints(sim_color, Point(x, y));
			int turn_obtain_points = parent_node.getBoard()->calcTotalObtainPoints(obtain_points_table);
			if (turn_obtain_points == 0) {
				continue;
			}
			decision_count ++;
			/*
			if (sim_color == AI_color) {
				std::cout << "depth: " << depth << "AI obtain at " << x << "," << y << " : " << turn_obtain_points <<std::endl;
			}
			else {
				std::cout << "depth: " << depth << "Player obtain at " << x << "," << y << " : " << turn_obtain_points <<std::endl;
			}*/
			
			// 盤面をコピー
			Board child_node_board = *parent_node.getBoard();
			
			// コピーした盤面でコマを置く
			child_node_board.putPiece(obtain_points_table, sim_color, Point(x, y));
			
			// 子ノード生成
			Node child_node(child_node_board);

			// 子ノード生成
			if (depth >= 1) {
				makeTree(child_node, parent_node.getBoard()->getEnemyPieceColor(sim_color), depth - 1);

				// 親ノードに追加
				parent_node.addChild(&child_node);
			}
		}
	}
	
	// パスした場合
	// 盤面をコピー
	Board child_node_board = *parent_node.getBoard();
	
	// 子ノード生成
	Node child_node(child_node_board);
	
	// 子ノード探索
	if (depth >= 1) {
		makeTree(child_node, parent_node.getBoard()->getEnemyPieceColor(sim_color), depth - 1);

		// 親ノードに追加
		parent_node.addChild(&child_node);
	}
}

// min-max
SolveResult Solver::minMax(Node& node, int depth) {
	return alpha_beta_cut(node, depth, INT_MIN, INT_MAX);
}

// αβ法
SolveResult Solver::alpha_beta_cut(Node& node, int depth, int alpha, int beta) {
	// 終端ノードなら評価値を返す
	if (node.countChildren() == 0 || depth == 0) {
		return { node.getBoard()->getAIPoints() - node.getBoard()->getPlayerPoints(), &node };
	}

	// AIの手のノードなら最大化
	if (node.getBoard()->isAIturn()) {
		Node* best_child = nullptr;
		for (auto child : node.getChildren()) {
			int before_alpha = alpha;
			alpha = std::max(alpha, alpha_beta_cut(*child, depth - 1, alpha, beta).value);
			if (alpha >= beta) {
				break;	// ここでβカット
			}
			if (alpha > before_alpha) {
				best_child = child;
			}
		}
		return { alpha, best_child };
	}
	// プレイヤーのノードなら最小化
	else {
		Node* best_child = nullptr;
		for (auto child : node.getChildren()) {
			int before_beta = beta;
			beta = std::min(beta, alpha_beta_cut(*child, depth - 1, alpha, beta).value);
			if (alpha >= beta) {
				break;	// ここでαカット
			}
			if (beta > before_beta) {
				best_child = child;
			}
		}
		return { beta, best_child };
	}
}

// AIの一手を返す
Board Solver::getSolvedBoard() {
	if (best_result.node == nullptr) {
		std::cout << "PASS" << std::endl;
		return *root_node.getBoard();
	}
	
	Node* best_node = best_result.node;
	Point last_pos = best_result.node->getBoard()->getLastPutPosition();
	if (last_pos.x >= 0 && last_pos.y >= 0) {	// (-1, -1)のときはパス
		HashTable<Direction::Type, int> obtain_points_table = root_node.getBoard()->calcObtainPoints(AI_color, last_pos);
		root_node.getBoard()->putPiece(obtain_points_table, AI_color, last_pos);
	}
	
	return *root_node.getBoard();
}

// depth_best_pointsを更新
void Solver::update_depth_best_points(SquareStatus::Type this_turn_color, int depth, int value) {
	if (value > 100 || value < -100) {
		return;
	}
	
	if (this_turn_color == AI_color) {
		if (depth_best_points[depth-1] < value) {
			std::cout << "AI Update Best-V at Depth: " << depth << " Value: " << value << std::endl;
			depth_best_points[depth-1] = value;
		}
	}
	else {
		if (depth_best_points[depth-1] > value) {
			std::cout << "Pl Update Best-V at Depth: " << depth << " Value: " << value << std::endl;
			depth_best_points[depth-1] = value;
		}
	}
}
