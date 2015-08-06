/**
*@file	Result.h
*@author	亀田
*/

#ifndef _RESULT_H_
#define _RESULT_H_

#include "GameState.h"

class Result : public GameState
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