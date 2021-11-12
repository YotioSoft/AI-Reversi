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
	Array<Point> best_way;
} SolveResult;

class Solver {
public:
	// コンストラクタ
	Solver(SquareStatus::Type arg_AI_color, Board current_board);
	
	// 探索
	SolveResult minMax(Node& parent_node, SquareStatus::Type sim_color, int depth);
	
	// AIの一手を返す
	Board getSolvedBoard();
	
	// βカット
	bool alpha_beta_cut(SquareStatus::Type this_turn_color, int depth, int value);
	
	// depth_best_pointsを更新
	void update_depth_best_points(SquareStatus::Type this_turn_color, int depth, int value);
	
private:
	Node root_node;
	
	SquareStatus::Type AI_color;
	
	SolveResult best_result;
	
	Array<int> depth_best_points;
};

#endif /* Solver_hpp */
