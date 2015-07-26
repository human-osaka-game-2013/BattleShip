/**
*@file	Selection.h
*@author	‹T“c
*/

#ifndef _SELECTION_H_
#define _SELECTION_H_

#include "GameState.h"

class Selection : GameState
{


public:
	void StateControl();
	void StateDraw();
	void ComStandby();
};

#endif