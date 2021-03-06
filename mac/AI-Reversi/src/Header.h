//
//  Header.h
//  AI-Reversi
//
//  Created by YotioSoft on 2021/11/03.
//

#pragma once

#ifndef Header_h
#define Header_h

#include <Siv3D.hpp> // OpenSiv3D v0.6.2

#define		BACKGROUND_COLOR			Color(0, 177, 106)
#define		BACKGROUND_COLOR_HILIGHT	Color(35, 203, 167)

class Board;

namespace SquareStatus {
enum Type {
	Black	= -1,
	None	= 0,
	White	= 1
};
}

namespace Direction {
enum Type {
	UpperLeft	= 11,
	Up			= 15,
	UpperRight	= 19,
	Right		= 9,
	LowerRight	= 29,
	Low			= 25,
	LowerLeft	= 21,
	Left		= 1
};
}

#endif /* Header_h */
