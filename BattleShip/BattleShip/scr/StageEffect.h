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
	*@brief	ステートパターン内での初期化
	*/
	bool Init();

	/**
	*@brief	ステートパターン内での描画
	*/
	bool Control();
	
	/**
	*@brief	ステートパターン内での描画
	*/
	void Draw();
	
	/**
	*@brief	ステートパターン内での通信時のサブルーチン処理
	*/
	void ComStandby();

};

#endif