/**
*@file	StateManager.cpp
*@author	亀田
*/
#include <windows.h>	//window基礎ファイル
#include "StateManager.h"
#include "lib_head.h"

//--------ステートパターンクラスのヘッダー-------
#include "SetShip.h"
#include "Selection.h"
#include "Result.h"
#include "StageEffect.h"
//-------------------------------------------

#define _FIRST_SETATE_ StateManager::STATE_SET_SHIP	///<	最初のステートパターン

//	コンストラクタ
StateManager::StateManager( Player* const _pPlayer1, Player* const _pPlayer2, StageObject* const	_pStageObject) 
	: m_pPlayer1(_pPlayer1), m_pPlayer2(_pPlayer2), m_pStageObject( _pStageObject)
{
	StateInit();
}

//	ステートの初期化
void StateManager::StateInit()
{
	m_beforeState = STATE_NONE;		///<	初期化なので以前のステートはそもそも無い為、STATE_NONEに。
	m_currentState = _FIRST_SETATE_;///<	ステートの初期化なので最初に読み込むであろうパターンの定数を入れる
	ChangeState(m_currentState);	///<	まだステートポイントには何も入っていないので初期化も兼ねて
}

//	ステートの基本ルーチン処理
void StateManager::StateCotrol()
{
	m_beforeState = m_currentState;	///<	ルーチン的にな処理で前フレーム時のステートを現在のステートに合わせる。

	if( m_pGameState->Control() )	///<	ステートのルーチン処理の結果シーンが変わる必要があれば
	{
		switch( m_currentState )	///<	変更するステートは順番がある程度決まっているので分岐
		{
		case STATE_SET_SHIP:
			ChangeState(STATE_SELECTION);

			break;
		case STATE_SELECTION:
			ChangeState(STATE_RESULT);

			break;
		case STATE_RESULT:
			ChangeState(STATE_SELECTION);

			break;
		case STATE_STAGE_EFFECT:
			//ChangeState(STATE_SELECTION);
			//
			break;
		}
	}


}

//	ステートの基本描画
void StateManager::StateDraw()
{
	m_pGameState->Draw();
}


//	ステートパターンの切り替え
bool StateManager::ChangeState( _STATE_NUM_ _stateType )
{
	if( _stateType > STATE_STAGE_EFFECT&& _stateType < STATE_SET_SHIP )
	{
		MessageBoxA(0,"ステートパターンの変更に失敗しました！\n引数を確認して下さい！(＞＜;)",NULL,MB_OK);
		return false;
	}
	
	switch( _stateType )
	{
	StateDelete();

	case STATE_SET_SHIP:
		m_pGameState = new SetShip();

		break;
	case STATE_SELECTION:
		m_pGameState = new Selection();

		break;
	case STATE_RESULT:
		m_pGameState = new Result();

		break;
	case STATE_STAGE_EFFECT:
		m_pGameState = new StageEffect();

		break;
	}
	m_currentState = _stateType;

	return true;
}

//	ステートオブジェクトの消去
void StateManager::StateDelete()
{
	CLASS_DELETE(m_pGameState);
}

StateManager::~StateManager()
{
	delete m_pGameState;
}