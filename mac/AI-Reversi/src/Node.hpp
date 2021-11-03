//
//  Node.hpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#ifndef Node_hpp
#define Node_hpp

#include "Header.h"
#include "Board.hpp"

class Node {
public:
	// コンストラクタ
	Node();
	Node(Board& arg_board);
	
	// 子ノードの登録
	void addChild(Node* arg_child_node);
	
private:
	// ノードが持つ盤面
	Board board;
	
	// 子ノード
	Array<Node*> children;
};

#endif /* Node_hpp */
