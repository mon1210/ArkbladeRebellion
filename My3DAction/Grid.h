/*
*
*
*
*/
#pragma once
#include "Constants.h"
#include "DxLib.h"


class Grid
{
public:
	Grid();
	~Grid();
	virtual void Draw();
protected:
	VECTOR startHorizontal;
	VECTOR endHorizontal;
	VECTOR startVertical;
	VECTOR endVertical;
};
