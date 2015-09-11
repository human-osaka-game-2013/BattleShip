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
	*@brief	戦闘行動選択での初期化
	*/
	bool Init( ShipObject::_SHIP_TYPE_NUM_ _type );

	/**
	*@brief	戦闘行動選択でのサブルーチン処理
	*/
	int Control();
	
	/**
	*@brief	戦闘行動選択での描画
	*/
	void Draw();
	
	/**
	*@brief	戦闘行動選択での通信待機処理
	*/
	void ComStandby();

};

#endif