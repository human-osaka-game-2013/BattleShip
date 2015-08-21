/**
*@file	GameState.h
*@author	亀田
*/

#ifndef	_GAMESTATE_H_
#define _GAMESTATE_H_

#include "Player.h"
#include "StageObject.h"
#include "DrawManager.h"
#include "Mouse.h"

class GameState
{
public:
	/**
	*@brief	ゲーム内でのステートパターンの列挙。
	*@details	主にステート切り替え時に使用
	*/
	enum	_STATE_NUM_
	{
		STATE_NONE,
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
	};

protected:
	_STATE_NUM_ m_stateID;	///<	自身のステートのID	
	Player* m_pPlayer[_PLAYER_NUM_];	///<	駒データ格納用
	StageObject* m_pStage;	///<	ステージデータ格納用
	int m_playerID;
	
//	デバイス
protected:
	CDrawManager*	m_pDrawManager;	///<	2D描画管理クラスポインタ(constポインタ)
	CMouse*			m_pMouse;		///<	マウス管理クラスポインタ(constポインタ)

public:
	/**
	*@brief	ステートパターン内での初期化
	*/
	virtual bool Init() = 0;

	/**
	*@brief	ステートパターン内でのサブルーチン処理
	*/
	virtual bool Control() = 0;

	/**
	*@brief	ステートパターン内での描画
	*/
	virtual void Draw() = 0;

	/**
	*@brief	ステートパターン内での通信時のサブルーチン処理
	*/
	virtual void ComStandby() = 0;

	/**
	*@brief	ステートのID取得
	*/
	_STATE_NUM_ GetState(){ return m_stateID; }

	/**
	*@brief	プレイヤークラスポインタをセット
	*@param[in]	_pPlayer	プレイヤーオブジェクトポインタ
	*@param[in]	_playerID	何番のプレイヤーか
	*/
	void SetPlayerPtr( Player* _pPlayer, int _playerID ){ 
		m_pPlayer[_playerID] = _pPlayer;
	}

	/**
	*@brief	ステージクラスポインタをセット
	*@param[in]	_pPlayer	ステージクラスポインタを
	*@param[in]	_playerID	何番のプレイヤーか
	*/
	void SetStagePtr( StageObject* _pStage ){ 
		m_pStage = _pStage;
	}

	/**
	*@brief	描画クラスセット
	*/
	void SetDraw( CDrawManager* const _pDrawManager ){
		m_pDrawManager = _pDrawManager;
	}

	/**
	*@brief	マウスクラスセット
	*/
	void SetMouse( CMouse* const _pMouse ){
		m_pMouse = _pMouse;
	}

	/**
	*@brief	プレイヤーIDセット
	*/
	void SetPlayerID( int _playerID ){ m_playerID = _playerID; }
};

#endif