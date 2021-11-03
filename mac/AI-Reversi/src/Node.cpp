//
//  Node.cpp
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#include "Node.hpp"

// コンストラクタ
Node::Node() {}
Node::Node(Board& arg_board) {
	board = arg_board;
}

// 子ノードの登録
void Node::addChild(Node* arg_child_node) {
	children << arg_child_node;
}
