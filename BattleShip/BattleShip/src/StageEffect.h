/**
*@file	StageEffect.h
*@author	亀田
*/

#ifndef _STAGEEFFECT_H_
#define _STAGEEFFECT_H_

#include "GameState.h"

#define _END_COUNT_OF_EFFECT_	60*10

class StageEffect : public GameState
{
private:
	int m_effectCount;	///<	エフェクトを再生する際のカウンタ
	
public:
	/**
	*@brief	コンストラクタ
	*@param	_type	現在選択している艦の種類
	*/
	StageEffect( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ): GameState( _type, _pGameLog ){
		m_effectCount = 0;
	}

	~StageEffect(){};

	/**
	*@brief	戦闘エフェクトでの初期化
	*/
	bool Init();

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
	bool ComStandby();

};

#endif