/**
*@file	SetShip.h
*@author	亀田
*/

#ifndef _SETSHIP_H_
#define _SETSHIP_H_

#include "GameState.h"

class SetShip : public GameState
{
private:


public:
	/**
	*@brief	ステートパターン内でのサブルーチン処理
	*/
	bool Control();

	/**
	*@brief	ステートパターン内でのサブルーチン処理
	*/
	void Draw();
	
	/**
	*@brief	ステートパターン内でのサブルーチン処理
	*/
	void ComStandby();

};

#endif