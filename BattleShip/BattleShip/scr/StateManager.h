#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "GameState.h"
class StateManagher
{
public:
	/**
	*@brief	戦闘ステートパターンの列挙
	*/
	enum _STATE_NUM_
	{
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
	};

private:
	GameState* m_pGameState;	///<	戦闘ステートパターンオブジェクトのポインタ
	_STATE_NUM_ m_beforeState;	///<	以前のステートパターン
	_STATE_NUM_ m_currentState;	///<	現在のステートパターン
	Player*		m_pPlayer;		///<	プレイヤー情報格納ポインタ
	StageObject*	m_pStageObject;	///<	ステージ情報格納ポインタ

public:
	/**
	*@brief	ステートパターンの切り替え
	*param[in]	_stateType	
	*/
	void ChangeState( _STATE_NUM_ _stateType );
	
	void Init();
	void Cotrol();
	void Draw();

};


#endif