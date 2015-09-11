/**
*@file	StageEffect.h
*@author	亀田
*/

#ifndef _STAGEEFFECT_H_
#define _STAGEEFFECT_H_

#include "GameState.h"

class StageEffect : public GameState
{


public:
	/**
	*@brief	戦闘エフェクトでの初期化
	*/
	bool Init( ShipObject::_SHIP_TYPE_NUM_ _type );

	/**
	*@brief	戦闘エフェクトでのサブルーチン処理
	*/
	int Control();
	
	/**
	*@brief	戦闘エフェクトでの描画
	*/
	void Draw();
	
	/**
	*@brief	戦闘エフェクトでの通信待機処理
	*/
	void ComStandby();

};

#endif