//
//  Solver.hpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#pragma once

#ifndef Solver_hpp
#define Solver_hpp

#include "Header.h"
#include "Node.hpp"
#include "Board.hpp"

#define SOLVE_DEPTH	6

typedef struct SolveResult {
	int value;
	Node* node;
} SolveResult;

class Solver {
public:
	// コンストラクタ
	Solver(SquareStatus::Type arg_AI_color, Board current_board);
	
	// 探索
	void makeTree(Node& parent_node, SquareStatus::Type sim_color, int depth);

	// min-max
	SolveResult minMax(Node& node, int depth);
	
	// βカット
	SolveResult alpha_beta_cut(Node& node, int depth, int alpha, int beta);

	// AIの一手を返す
	Board getSolvedBoard();
	
	// depth_best_pointsを更新
	void update_depth_best_points(SquareStatus::Type this_turn_color, int depth, int value);
	
private:
	Node root_node;
	
	SquareStatus::Type AI_color;
	
	SolveResult best_result;
	
	Array<int> depth_best_points;
};

#endif /* Solver_hpp */
