//
//  Solver.hpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#ifndef Solver_hpp
#define Solver_hpp

#include "Header.h"
#include "Node.hpp"
#include "Board.hpp"

#define SOLVE_DEPTH	2

class Solver {
public:
	// コンストラクタ
	Solver(SquareStatus::Type AI_color, Board current_board);
	
	// 探索
	Point solve();
	
private:
	Node root_node;
};

#endif /* Solver_hpp */
