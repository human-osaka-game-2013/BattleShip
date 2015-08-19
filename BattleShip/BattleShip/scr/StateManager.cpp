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
#define _POS_PLAYER1FRAME_	0.f, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)						///<プレイヤー1情報の枠の表示座標
#define _POS_PLAYER2FRAME_	_BLOCK_WIDTH_SIZE_*12, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)	///<プレイヤー2情報の枠の表示座標
#define _SIZE_PLAYERFRAME_	_BLOCK_WIDTH_SIZE_*11, _BLOCK_HEIGHT_SIZE_*5	///<プレイヤー情報の枠サイズ

//	コンストラクタ 
StateManager::StateManager( Player* const _pPlayer1, Player* const _pPlayer2, 
							StageObject* const _pStageObject, const int _playerID) 
	: m_pPlayer1(_pPlayer1), m_pPlayer2(_pPlayer2), m_pStageObject( _pStageObject), m_playerID(_playerID)
{
	StateInit();
}

//	ステートの初期化
void StateManager::StateInit()
{
	m_beforeState = STATE_NONE;		///<	初期化なので以前のステートはそもそも無い為、STATE_NONEに。
	m_currentState = _FIRST_SETATE_;///<	ステートの初期化なので最初に読み込むであろうパターンの定数を入れる
	ChangeState(m_currentState);	///<	まだステートポイントには何も入っていないので初期化も兼ねて
	m_StageFrame.Init( 0.f, -2.f, WIDTH, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_));
	///<画面上部から１１マス分目まで盤面フレームがあるので11/16となる。
	m_PlayerFrame[0].Init( _POS_PLAYER1FRAME_, _SIZE_PLAYERFRAME_ );
	m_PlayerFrame[1].Init( _POS_PLAYER2FRAME_, _SIZE_PLAYERFRAME_ );
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
void StateManager::StateDraw( CDrawManager* _drawManager)
{
	float tempX, tempY;
	
	//	盤面枠表示（左）
	m_StageFrame.GetPosition( &tempX, &tempY );
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		0.f, 0.f, 
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);

	//	盤面枠表示（右）
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*12, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 0.f, 
		1.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);

	//	盤面枠表示（中）
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*_STAGE_WIDTH_MAX_, tempY, 
		_BLOCK_WIDTH_SIZE_, HEIGHT,
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, 0.f,
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 1.f,
		180, 220, 220, 220);

	//	プレイヤー1枠表示
	m_PlayerFrame[0].GetPosition( &tempX, &tempY );
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_PlayerFrame[0].GetWidth(),  m_PlayerFrame[0].GetHeight(),
		0.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
		11/_BLOCK_WIDTH_MAX_, 1.f,
		180, 255, 100, 100);
	//	プレイヤー2枠表示
	m_PlayerFrame[1].GetPosition( &tempX, &tempY );
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_PlayerFrame[1].GetWidth(),  m_PlayerFrame[1].GetHeight(),
		12/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
		1.f, 1.f,
		180, 100, 100, 255);

	//	ステージマス目表示
	for( int ip=0; ip<_PLAYER_NUM_; ip++ ){
		for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ ){
			for( int il=0; il<_STAGE_LINE_MAX_; il++ ){
				
				tempX = ( ic*( _BLOCK_WIDTH_SIZE_ ))+( _BLOCK_WIDTH_SIZE_ );
				tempY = ( il*( _BLOCK_HEIGHT_SIZE_ ))+( _BLOCK_HEIGHT_SIZE_ );
				if( ip == 1 )
					tempX += _BLOCK_WIDTH_SIZE_*11;

				_drawManager->CustomCorolDraw( _TEX_BLOCK_, tempX, tempY, 
					_BLOCK_WIDTH_SIZE_,  _BLOCK_HEIGHT_SIZE_,
					0.f, 0.f, 
					1.f, 1.f,
					100, 200, 200, 200);
			}
		}
	}
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

void StateManager::Free()
{
	delete m_pGameState;

}