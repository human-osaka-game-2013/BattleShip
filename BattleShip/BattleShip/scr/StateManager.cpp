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
	
	for( int iPlayer=0; iPlayer<_PLAYER_NUM_; iPlayer++ )	///<表示位置などを予め初期化しておき、描画時や当たり判定時などにも利用する。
	{
		float tempX, tempY;	
		for( int iShip=0; iShip<ShipObject::TYPE_MAX; iShip++ ){
			float tempW = _BLOCK_WIDTH_SIZE_, tempH = _BLOCK_HEIGHT_SIZE_;	///<駒別に可変性があるので縦横幅の仮保存をして少し効率を上げる。
			tempX = tempW;
			tempY = (_STAGE_HEIGHT_MAX_*tempH)+(iShip*tempH);	///<Y座標はまずプレイヤー情報枠の基準点から
			
			//	駒の向きの初期化
			ShipObject* tempShip;
			
			if( iPlayer == 0 ){
				tempX += tempW*5;	///<プレイヤー1は1マス目から5マス分ずらすので
				tempShip = m_pPlayer1->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
			}else{
				tempX += tempW*11;	///<プレイヤー2は1マス目から11マス分ずらすので
				tempShip = m_pPlayer2->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
			}
			switch( iShip )	///<	艦種別分岐
			{
			case ShipObject::TYPE_AIRCARRIER:	
				m_ShipFrame[iPlayer][iShip].Init( tempX, tempY, tempW*5, tempH );
				break;
			case ShipObject::TYPE_BATTLESHIP:
				m_ShipFrame[iPlayer][iShip].Init( tempX, tempY, tempW*4, tempH );
				break;
			case ShipObject::TYPE_CRUISER:
				m_ShipFrame[iPlayer][iShip].Init( tempX, tempY, tempW*3, tempH );
				break;
			case ShipObject::TYPE_DESTROYER:
			case ShipObject::TYPE_SUBMARINE:
				m_ShipFrame[iPlayer][iShip].Init( tempX, tempY, tempW*2, tempH );
				break;

			}
			m_ShipFrame[iPlayer][iShip].SetDirection( tempShip->GetDirection() );///<	m_pShipの向き情報をコチラにも適用
		}
	}
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
		180, 220, 220, 220);	///<	盤面の左側の描画

	//	盤面枠表示（右）
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*12, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 0.f, 
		1.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);	///<	盤面の右側の描画

	//	盤面枠表示（中）
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*_STAGE_WIDTH_MAX_, tempY, 
		_BLOCK_WIDTH_SIZE_, HEIGHT,
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, 0.f,
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 1.f,
		180, 220, 220, 220);	///<	盤面の真ん中の描画

	//	プレイヤー1枠表示
	m_PlayerFrame[0].GetPosition( &tempX, &tempY );
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_PlayerFrame[0].GetWidth(),  m_PlayerFrame[0].GetHeight(),
		0.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
		11/_BLOCK_WIDTH_MAX_, 1.f,
		180, 255, 100, 100);	///<	プレイヤー1の枠描画
	//	プレイヤー2枠表示
	m_PlayerFrame[1].GetPosition( &tempX, &tempY );
	_drawManager->CustomCorolDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_PlayerFrame[1].GetWidth(),  m_PlayerFrame[1].GetHeight(),
		12/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
		1.f, 1.f,
		180, 100, 100, 255);	///<	プレイヤー2の枠描画

	//	ステージマス目表示
	//	プレイヤー数
	for( int ip=0; ip<_PLAYER_NUM_; ip++ ){
		//	行
		for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ ){	
			//	列
			for( int il=0; il<_STAGE_LINE_MAX_; il++ ){
				m_pStageObject->m_stageBlock[ip][ic][il].GetPosition( &tempX, &tempY );
				
				int tempA = 0, tempR = 200, tempG = 200, tempB = 200;

				if( m_pStageObject->m_stageArray[ip][ic][il] != 0 )	///<駒があった場所は塗りつぶす（Test）
				{
					tempA = 100;

				_drawManager->CustomCorolDraw( _TEX_BLOCK_, tempX, tempY, 
					m_pStageObject->m_stageBlock[ip][ic][il].GetWidth(), 
					m_pStageObject->m_stageBlock[ip][ic][il].GetHeight(),
					0.f, 0.f, 
					1.f, 1.f,
					tempA, tempR, tempG, tempB);	///<	マスの描画
				}
				_drawManager->CustomCorolDraw( _TEX_BLOCKFRAME_, tempX, tempY, 
					m_pStageObject->m_stageBlock[ip][ic][il].GetWidth(), 
					m_pStageObject->m_stageBlock[ip][ic][il].GetHeight(),
					0.f, 0.f, 
					1.f, 1.f,
					100, 200, 200, 200);	///<	マスの描画
			}
		}
		//	プレイヤー別の駒情報の表示
		for( int iShip=0; iShip<ShipObject::TYPE_MAX; iShip++ ){
			m_ShipFrame[ip][iShip].GetPosition( &tempX, &tempY );
			float tempW = m_ShipFrame[ip][iShip].GetWidth();
			float tempH = m_ShipFrame[ip][iShip].GetHeight();
			
			switch( iShip )	///<	艦種別分岐
			{
			case ShipObject::TYPE_AIRCARRIER:	
				_drawManager->CustomCorolDraw( _TEX_AIRCARRIER_, tempX, tempY, 
					tempW,  tempH,
					0.f, 0.f, 
					1.f, 1.f,
					255, 255, 255, 255);	///<空母駒の描画
				break;
			case ShipObject::TYPE_BATTLESHIP:
				_drawManager->CustomCorolDraw( _TEX_BATTLESHIP_, tempX, tempY, 
					tempW,  tempH,
					0.f, 0.f, 
					1.f, 1.f,
					255, 255, 255, 255);	///<戦艦駒の描画
				break;
			case ShipObject::TYPE_CRUISER:
				_drawManager->CustomCorolDraw( _TEX_CRUISER_, tempX, tempY, 
					tempW,  tempH,
					0.f, 0.f, 
					1.f, 1.f,
					255, 255, 255, 255);	///<巡洋艦駒の描画
				break;
			case ShipObject::TYPE_DESTROYER:
				_drawManager->CustomCorolDraw( _TEX_DESTROYER_, tempX, tempY, 
					tempW,  tempH,
					0.f, 0.f, 
					1.f, 1.f,
					255, 255, 255, 255);	///<駆逐艦駒の描画
				break;
			case ShipObject::TYPE_SUBMARINE:
				_drawManager->CustomCorolDraw( _TEX_SUBMARINE_, tempX, tempY, 
					tempW,  tempH,
					0.f, 0.f, 
					1.f, 1.f,
					255, 255, 255, 255);	///<潜水艦駒の描画
				break;

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

	//	ステートが変わったので、一連の初期化を行う
	m_pGameState->SetPlayerPtr( m_pPlayer1, 0 );
	m_pGameState->SetPlayerPtr( m_pPlayer2, 1 );
	m_pGameState->SetStagePtr( m_pStageObject );
	m_pGameState->SetDraw( m_pDrawManager );
	m_pGameState->SetMouse( m_pMouse );
	m_pGameState->SetPlayerID( m_playerID );
	m_pGameState->Init();	///<最後に

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