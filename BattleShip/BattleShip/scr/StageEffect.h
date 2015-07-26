/**
*@file	StageEffect.h
*@author	‹T“c
*/

#ifndef _STAGEEFFECT_H_
#define _STAGEEFFECT_H_

#include "GameState.h"

class StageEffect : GameState
{


public:
	void StateControl();
	void StateDraw();
	void ComStandby();

};

#endif