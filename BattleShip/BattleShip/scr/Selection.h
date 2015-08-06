/**
*@file	Selection.h
*@author	亀田
*/

#ifndef _SELECTION_H_
#define _SELECTION_H_

#include "GameState.h"

class Selection : public GameState
{


public:
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