/**
*@file	SetShip.h
*@author	‹T“c
*/

#ifndef _SETSHIP_H_
#define _SETSHIP_H_

#include "GameState.h"

class SetShip : GameState
{


public:
	void StateControl();
	void StateDraw();
	void ComStandby();

};

#endif