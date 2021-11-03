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

#define SOLVE_DEPTH	2

typedef struct SolveResult {
	int value;
	Array<Point> best_way;
} SolveResult;

class Solver {
public:
	// コンストラクタ
	Solver(SquareStatus::Type arg_AI_color, Board current_board);
	
	// 探索
	SolveResult solve(Node& parent_node, SquareStatus::Type sim_color, int depth);
	
	// AIの一手を返す
	Board getSolvedBoard();
	
private:
	Node root_node;
	
	SquareStatus::Type AI_color;
	
	SolveResult best_result;
};

#endif /* Solver_hpp */
