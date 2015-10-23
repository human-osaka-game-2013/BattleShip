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
	enum _ACTION_RESULT_
	{
		RESULT_NONE,
		RESULT_SEARCH,
		RESULT_ATTACK,
	};

private:
	char m_resultPlayer;
	char m_resultEnemy;

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
	*@details	戦闘結果は、各駒１つの行動選択の結果なので、判定としては下記の３種類になる。
	*@param[in]	_playerIndex	プレイヤーの配列での指数
	*@return 戦闘結果
	*@retval 0	特に無し
	*@retval 1	相手の攻撃が当たった
	*@retval 2	相手に索敵された
	*/
	int ResultOfAction( int _playerIndex );
};

#endif