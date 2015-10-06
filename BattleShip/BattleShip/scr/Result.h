/**
*@file	Result.h
*@author	亀田
*/

#ifndef _RESULT_H_
#define _RESULT_H_

#include "GameState.h"

class Result : public GameState
{
private:
	

public:
	/**
	*@brief	コンストラクタ
	*@param	_type	現在選択している艦の種類
	*/
	Result( ShipObject::_SHIP_TYPE_NUM_& _type ): GameState( _type ){}

	/**
	*@brief	戦闘結果での初期化
	*/
	bool Init();

	/**
	*@brief	戦闘結果でのサブルーチン処理
	*/
	int Control();
	
	/**
	*@brief	戦闘結果での描画
	*/
	void Draw();
	
	/**
	*@brief	戦闘結果での通信待機処理
	*/
	bool ComStandby();

private:
	/**
	*@brief	行動選択による戦闘の結果
	*/
	int ResultOfAction();
};

#endif