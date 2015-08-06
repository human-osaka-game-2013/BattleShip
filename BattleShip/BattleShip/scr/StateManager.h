#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "GameState.h"
#include "Player.h"
#include "StageObject.h"

class StateManager
{
public:
	/**
	*@brief	戦闘ステートパターンの列挙
	*/
	enum _STATE_NUM_
	{
		STATE_NONE = -1,
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
	};

private:
	GameState*		m_pGameState;	///<	戦闘ステートパターンオブジェクトのポインタ
	_STATE_NUM_		m_beforeState;	///<	以前のステートパターン
	_STATE_NUM_		m_currentState;	///<	現在のステートパターン
	Player* const 	m_pPlayer[_PLAYER_NUM_];///<	プレイヤー1情報格納ポインタ
	StageObject* const	m_pStageObject;	///<	ステージ情報格納ポインタ

public:
	/**
	*@brief	コンストラクタ
	*/
	StateManager( Player* const _pPlayer1, Player* const _pPlayer2,
		StageObject* const	_pStageObject);

	/**
	*@brief	ステートパターンの切り替え
	*param[in]	_stateType	
	*@return true：ステートパターンの変更完了。*n
			false：変更失敗
	*/
	bool ChangeState( _STATE_NUM_ _stateType );
	
	/**
	*@brief	ステートの初期化
	*/
	void StateInit();
	
	/**
	*@brief	ステートの基本ルーチン処理
	*/
	void StateCotrol();

	/**
	*@brief	ステートの基本描画
	*/
	void StateDraw();

	/**
	*@brief	ステートオブジェクトの消去
	*/
	void StateDelete();
};


#endif