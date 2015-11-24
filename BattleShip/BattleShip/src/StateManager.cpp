/**
*@file	StateManager.cpp
*@author	亀田
*/

#include "StateManager.h"

//--------ステートパターンクラスのヘッダー-------
#include "SetShip.h"
#include "Selection.h"
#include "Result.h"
#include "StageEffect.h"
//-------------------------------------------
#include "DebugNew.h"


#define _FIRST_SETATE_ StateManager::STATE_SET_SHIP	///<	最初のステートパターン
#define _POS_PLAYER1FRAME_	0.f, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)						///<プレイヤー1情報の枠の表示座標
#define _POS_PLAYER2FRAME_	_BLOCK_WIDTH_SIZE_*12, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)	///<プレイヤー2情報の枠の表示座標
#define _SIZE_PLAYERFRAME_	_BLOCK_WIDTH_SIZE_*11, _BLOCK_HEIGHT_SIZE_*5	///<プレイヤー情報の枠サイズ


//#define _DEBUG_SCENE_TEST_

//	コンストラクタ 
StateManager::StateManager( Player* const _pPlayer1, Player* const _pPlayer2, 
							StageObject* const _pStageObject, const int _playerID) 
	: m_pPlayer1(_pPlayer1), m_pPlayer2(_pPlayer2), m_pStageObject( _pStageObject), m_playerID(_playerID)
{
	m_connectFlag = false;
	m_resultPlayer	= static_cast<int>(Result::RESULT_NONE);
	m_resultEnemy	= static_cast<int>(Result::RESULT_NONE);
	m_resultBattle	= static_cast<int>(Result::TYPE_DRAW);
	m_plyaerSelectType	= static_cast<int>(GameState::_SELECT_NONE_);
	m_turnCount = 1;
}

//	ステートの初期化
void StateManager::StateInit()
{
	m_beforeState	= STATE_NONE;		///<	初期化なので以前のステートはそもそも無い為、STATE_NONEに。
	m_currentState	= _FIRST_SETATE_;///<	ステートの初期化なので最初に読み込むであろうパターンの定数を入れる
	m_currentShip	= ShipObject::TYPE_AIRCARRIER;	///<	初期選択駒は空母なので数値を空母にセット。
	
	m_StageFrame.Init( 0.f, -2.f, WIDTH, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_));
	///<画面上部から１１マス分目まで盤面フレームがあるので11/16となる。
	m_PlayerFrame[0].Init( _POS_PLAYER1FRAME_, _SIZE_PLAYERFRAME_ );
	m_PlayerFrame[1].Init( _POS_PLAYER2FRAME_, _SIZE_PLAYERFRAME_ );

	//	ゲームログの初期化
	int plIndex = m_playerID%2;	
	m_gameLog.Init( static_cast<long>( m_PlayerFrame[plIndex].GetPositionX() + static_cast<long>(_LOG_POS_TWEAK_)), 
		static_cast<long>( m_PlayerFrame[plIndex].GetPositionY() + static_cast<long>(_LOG_POS_TWEAK_)) );
	//	ゲーム経過時間ログの初期化
	m_gameElapsed.Init( static_cast<long>( m_PlayerFrame[plIndex].GetPositionX() + static_cast<long>(_LOG_POS_TWEAK_) ),
		static_cast<long>( m_PlayerFrame[plIndex].GetPositionY()) + static_cast<long>(_LOG_HEIGHT_MAX_) );
	//	通信状態ログの初期化
	float tempX = ( m_playerID/_PLAYER_NUM_ ? (_BOARD_OF_SHIPDATA_LINE_P1_) : (_BOARD_OF_SHIPDATA_LINE_P2_+_SHIP_ARRAY_INDEX_) ) * _BLOCK_WIDTH_SIZE_;
	m_gameConnectState.Init( static_cast<long>( tempX ), static_cast<long>( m_PlayerFrame[plIndex].GetPositionY()) + static_cast<long>(_LOG_HEIGHT_MAX_) );

	m_tempStr1 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::START_BATTLE];
	m_gameLog.AddStream( m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
	
	//	ステート変更（＆初期化）
	ChangeState(m_currentState);	///<	まだステートポイントには何も入っていないので初期化も兼ねて

	m_beforeShip = -1;	///<前フレームで選択（対象）されている駒を保持しておく。最初に入ってきた場合は初期値として-1を入れている。	

	for( int iPlayer=0; iPlayer<_PLAYER_NUM_; iPlayer++ )	///<表示位置などを予め初期化しておき、描画時や当たり判定時などにも利用する。
	{
		float tempX, tempY;	
		//	艦種分ループで全ての駒を初期化
		for( int iShip=0; iShip<ShipObject::TYPE_MAX; iShip++ ){

		//	------自駒のステータス（損害情報）の初期化------
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
		}
	}
}

//	ステートの基本ルーチン処理
int StateManager::StateCotrol()
{
	m_beforeState = m_currentState;	///<	ルーチン的にな処理で前フレーム時のステートを現在のステートに合わせる。
	int stateResult = this->CheckState();	///<	ステートの変更チェックの処理
	UpdateStatInTime( m_stateTime );	///<	タイムの更新
	
#ifdef _DEBUG_SCENE_TEST_
	stateResult = -1;

#endif
	if( stateResult == 1 )	///<	ステートのルーチン処理の結果シーンが変わる必要があれば
	{
		switch( m_currentState )	///<	変更するステートは順番がある程度決まっているので分岐
		{
		case STATE_SET_SHIP:
			ChangeState(STATE_SELECTION);

			break;
		case STATE_SELECTION:
			ChangeState(STATE_STAGE_EFFECT);

			break;
		case STATE_STAGE_EFFECT:
			ChangeState(STATE_RESULT);
			
			break;
		case STATE_RESULT:
			ChangeState(STATE_SELECTION);

			break;
		}
	}
	else if( stateResult == -1 )
	{
		m_pAudio->SoundAllStop();
		//	戦闘終了に伴う戦況の最終結果をログに表示
		if( m_resultBattle == Result::TYPE_DRAW )
		{
			m_tempStr1 = m_gameLog.GetPhrase( FixedPhrase::RESULT_DRAW_STR );
			m_pAudio->SoundPlay( Audio::_TITLE_BGM_, true );
		}
		else if( m_resultBattle == Result::TYPE_VICTORY )
		{
			m_tempStr1 = m_gameLog.GetPhrase( FixedPhrase::RESULT_VICTORY_STR );
			m_pAudio->SoundPlay( Audio::_WIN_BGM_, true );
		}
		else if( m_resultBattle == Result::TYPE_DEFEAT )
		{
			m_tempStr1 = m_gameLog.GetPhrase( FixedPhrase::RESULT_DEFEAT_STR );
			m_pAudio->SoundPlay( Audio::_LOSE_BGM_, true );
		}
		m_gameLog.AddStream( m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		//	戦闘終了ログを表示
		m_tempStr1 = m_gameLog.GetPhrase( FixedPhrase::RESULT_END );
		m_gameLog.AddStream( m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		m_tempStr1 = "左クリックでタイトルに戻りましょう";
		m_gameLog.AddStream( m_tempStr1.c_str(), _LOG_COLOR_NOMAL_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
	}
	
	return stateResult;
}

int StateManager::CheckState()
{
	
	int checkResult = 0;
	int stageResult = 0;

	//	戦闘続行中なら各ステートの処理を通す
	//	通信を必要とするステートはSetShip、Selectionのみなので、他のステートではこのm_connectFlagには干渉しない事。
	m_pGameState->SetConnectFlag( m_connectFlag );	//	毎フレーム通信のフラグを更新
	stageResult = m_pGameState->Control();	///<　ステートごとの処理に移行
	SetConnectFlag( m_pGameState->GetConnectFlag() );	//	ステート内でのフラグ変更を反映させる
	
	switch( m_currentState )	///<　シーン毎にステートの結果への対処が変わるので分岐
	{
	case STATE_SET_SHIP:
		//	駒配置を促すログを出す
		if( m_beforeShip != m_currentShip && m_currentShip != ShipObject::TYPE_MAX )
		{
			m_tempStr2 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::SET_PHRASE_STR];
			
			m_tempStr1 = m_gameLog.GetMultiplePhrase( 2, static_cast<int>(m_currentShip), static_cast<int>(FixedPhrase::SET_PHRASE_STR) );
			m_gameLog.AddStream( m_tempStr1.c_str() );
		}

		if( m_currentShip >= ShipObject::TYPE_MAX && !m_connectFlag )	///<　全ての駒がセットされた
			checkResult = 1;
		break;

	case STATE_SELECTION:
		if( stageResult == 1 && !m_connectFlag ){	///<　結果が1且つ、通信が完了していた場合
			Selection* pSelection = dynamic_cast<Selection*>(m_pGameState);	///<Selectionの関数にアクセスする必要があるので、ダウンキャストする。
			m_plyaerSelectType = pSelection->GetSelectionType();
		
			checkResult = 1;	///<　選択結果に移る
		}
		break;

	case STATE_STAGE_EFFECT:
		if( stageResult == 1 ){	///<　結果が1(ステージの演出が完了)の場合
			
			checkResult = 1;
		}
		break;

	case STATE_RESULT:
		//勝利or敗北or戦闘終了
		if( stageResult == Result::TYPE_VICTORY || stageResult == Result::TYPE_DEFEAT )
		{
			Result* pResult = dynamic_cast<Result*>(m_pGameState);	///<Resultの関数にアクセスする必要があるので、ダウンキャストする。
			checkResult = -1;	//StateManager側に戦闘結果＝戦闘終了した事を教えてやる。
			pResult->GetResultOfBattle( m_resultBattle );
			m_pStageObject->ResetSelect();	//判定を取ったので選択情報は消す
		}
		//勝敗はまだついていない
		else	
		{
			Result* pResult = dynamic_cast<Result*>(m_pGameState);	///<Resultの関数にアクセスする必要があるので、ダウンキャストする。
			pResult->GetResultPlayerAndEnemy( m_resultPlayer, m_resultEnemy );
			pResult->GetResultOfBattle( m_resultBattle );
			checkResult = 1;
			m_pStageObject->ResetSelect();	//判定を取ったので選択情報は消す
			
			// Selectionステートに移る前に現在のターンが終了したので次の駒を指定
			if( m_currentShip < ShipObject::TYPE_SUBMARINE){

				m_currentShip = static_cast< ShipObject::_SHIP_TYPE_NUM_ >( m_beforeShip+1 );
			}else{
				//	各艦の行動フェーズが一周したのでターン数を増やす
				m_turnCount++;
				m_currentShip = ShipObject::TYPE_AIRCARRIER;
			}
		}

		break;
	
	}

	///< ステート別Controlが終わったので前フレームでの選択駒を更新
	m_beforeShip = static_cast<int>(m_currentShip);
	return checkResult;
}

//	ステートパターンの切り替え
bool StateManager::ChangeState( _STATE_NUM_ _stateType )
{
	if( _stateType > STATE_STAGE_EFFECT&& _stateType < STATE_SET_SHIP )
	{
		MessageBoxA(0,"ステートパターンの変更に失敗しました！\n引数を確認して下さい！(＞＜;)",NULL,MB_OK);
		return false;
	}
	
	//	すでにステートが決まっていた場合（変更する際）は前のインスタンス生成したものを消す必要がある。
	if( m_beforeState != STATE_NONE )
	{
		CLASS_DELETE(m_pGameState); 
	}
	//	各ステート別にステート生成
	switch( _stateType )
	{
	case STATE_SET_SHIP:
		m_tempStr1 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::STATE_SET_SHIP_STR];
		m_gameLog.AddStream(m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		// 現状は最初に配置するのは空母で、CheckState関数内では空母のログ
		m_pGameState = new SetShip( m_currentShip, &m_gameLog );

		break;
	case STATE_SELECTION:
		m_tempStr1 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::STATE_SELECTION_STR];
		m_gameLog.AddStream(m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		m_pGameState = new Selection( m_currentShip, &m_gameLog );

		break;

	case STATE_STAGE_EFFECT:
		m_pGameState = new StageEffect( m_currentShip, &m_gameLog );
		static_cast<StageEffect*>(m_pGameState)->SetSelectionType( m_plyaerSelectType );	///<エフェクトにはどの行動を選択したかの判断がいるので情報を渡してやる。
		break;

	case STATE_RESULT:
		m_tempStr1 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::STATE_RESULT_STR];
		m_gameLog.AddStream(m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		m_pGameState = new Result( m_currentShip, &m_gameLog );

		break;
	}


	m_currentState = _stateType;	///<	現在のステート変数を更新
	
	if( m_currentShip >= ShipObject::TYPE_MAX )	///<	ステート変更のついでに選択駒が範囲を超えているかチェック
		m_currentShip = ShipObject::TYPE_AIRCARRIER;	///<	空母に変更

	//	ステートが変わったので、一連の初期化を行う
	m_pGameState->SetPlayerPtr( m_pPlayer1, 0 );
	m_pGameState->SetPlayerPtr( m_pPlayer2, 1 );
	m_pGameState->SetStagePtr( m_pStageObject );
	m_pGameState->SetDraw( m_pDrawManager );
	m_pGameState->SetMouse( m_pMouse );
	m_pGameState->SetAudio( m_pAudio );
	m_pGameState->SetPlayerID( m_playerID );
	m_pGameState->Init();	///<最後にステート側の初期化も行う（引数はこのクラスが持っている現在の選択駒）

	return true;
}

//	ステートの基本描画
void StateManager::StateDraw()
{	
	DrawStageFrame();

	//	ステート別の描画
	m_pGameState->Draw();

	DrawLog();

	//	通信待ち中
	if( GetConnectFlag() )
	{
		m_pGameState->ComStandby( m_gameConnectState );
	}
}

void StateManager::DrawStageFrame()
{	
	float tempX, tempY;

	if( m_playerID == 1 )
	{
		//	プレイヤー1枠表示
		m_PlayerFrame[0].GetPosition( &tempX, &tempY );
		m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
			m_PlayerFrame[0].GetWidth(),  m_PlayerFrame[0].GetHeight(),
			0.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
			11/_BLOCK_WIDTH_MAX_, 1.f,
			180, 255, 100, 100);	///<	プレイヤー1の枠描画
		
	}
	else
	{
		//	プレイヤー2枠表示
		m_PlayerFrame[1].GetPosition( &tempX, &tempY );
		m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
			m_PlayerFrame[1].GetWidth(),  m_PlayerFrame[1].GetHeight(),
			12/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
			1.f, 1.f,
			180, 100, 100, 255);	///<	プレイヤー2の枠描画
	}

	//	プレイヤー数ループして、駒とマス目を描画する
	for( int ip=0; ip<_PLAYER_NUM_; ip++ )
	{
		DrawShipObject( ip );
		DrawStageBlock( ip );
	}
	
	//	盤面枠表示（左）
	m_StageFrame.GetPosition( &tempX, &tempY );
	m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		0.f, 0.f, 
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);	///<	盤面の左側の描画

	//	盤面枠表示（右）
	m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*12, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 0.f, 
		1.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);	///<	盤面の右側の描画

	//	盤面枠表示（中）
	m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*_STAGE_WIDTH_MAX_, tempY, 
		_BLOCK_WIDTH_SIZE_, HEIGHT,
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, 0.f,
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 1.f,
		100, 220, 220, 220);	///<	盤面の真ん中の描画

	
}

void StateManager::DrawShipObject( const int _playerIndex )
{
	//	プレイヤー別の駒情報の表示
	for( int iShip=0; iShip<ShipObject::TYPE_MAX; iShip++ )
	{
		//	ステージ上の駒の表示
		float tempW = _BLOCK_WIDTH_SIZE_;	
		float tempH = _BLOCK_HEIGHT_SIZE_;
		
		/**
		*@todo	現在は自身の駒のみを表示している。
		*/
		if( _playerIndex == m_playerID-1 )	///<今は自分のプレイヤーの駒しか表示しない
		{
			Player* tempPlayer = m_playerID%_PLAYER_NUM_ ? m_pPlayer1:m_pPlayer2;
			ShipObject* tempShip = tempPlayer->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
				
			if( !tempShip->GetDeadFlag() )
			{
				//	盤面上に置かれている自分の駒を描画
				m_pDrawManager->VertexTransform( iShip + _TEX_AIRCARRIER_, tempShip->m_vertex, 
					tempShip->GetPositionX(), tempShip->GetPositionY(), 1.f, 1.f, tempShip->GetDirection()*90.f );
				
				if( _playerIndex== 0 ){	//	プレイヤー1の場合
					//	配置したものからプレイヤー側の所持駒情報も描画
					m_pDrawManager->VertexTransform( iShip + _TEX_AIRCARRIER_, tempShip->m_vertex, 
						(_BOARD_OF_SHIPDATA_LINE_P1_*tempW)+(tempW/2), ((_BOARD_OF_SHIPDATA_COLUMN_+iShip)*tempH) + (tempH/2),
						1.f, 1.f, CGameObject::CH_RIGHT*90.f );

				}else{	//	プレイヤー2の場合

					//	配置したものからプレイヤー側の所持駒情報も描画
					m_pDrawManager->VertexTransform( iShip + _TEX_AIRCARRIER_, tempShip->m_vertex, 
						(_BOARD_OF_SHIPDATA_LINE_P2_*tempW)+(tempW/2), ((_BOARD_OF_SHIPDATA_COLUMN_+iShip)*tempH) + (tempH/2),
						1.f, 1.f, CGameObject::CH_RIGHT*90.f );
				}
				
			}
		}
		
	}
		
}


void StateManager::DrawStageBlock( const int _playerIndex )
{
	float tempX, tempY;

	//	行
	for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ )
	{	
		//	列
		for( int il=0; il<_STAGE_LINE_MAX_; il++ )
		{
			m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetPosition( &tempX, &tempY );
			
			int tempA = 0, tempR = 200, tempG = 200, tempB = 200;
			int tempArrayData = m_pStageObject->m_stageArray[_playerIndex][ic][il];
		
			//	選択マスor損傷マスは見えるようにする
			if( StageObject::SelectOfData(tempArrayData) != StageObject::_SELECT_NOMAL_ ||
				StageObject::ConditionOfData(tempArrayData) == StageObject::_CONDITION_DAMAGE_)
			{
					
				//	範囲指定桁チェック
				switch( StageObject::SelectOfData(tempArrayData) )
				{
				case StageObject::_SELECT_TRUE_:	///<選択されているマス
					tempA = 100;
					break;
				case StageObject::_SELECT_FALSE_:	///<駒が置けないor選択範囲が何かに接触しているマス
					tempA = 100, tempR = 255, tempG = 0, tempB = 0;
					break;
				case StageObject::_SEARCH_NOMAL_:
				case StageObject::_SEARCH_ALL_:
					tempA = 100, tempR = 0, tempG = 255, tempB = 0;
					break;
				case StageObject::_ACTION_NOMAL_:
				case StageObject::_ACTION_ALL_:
					tempA = 100, tempR = 0, tempG = 0, tempB = 255;
					break;
				}
	
				//	損傷状態桁チェック
				switch( StageObject::ConditionOfData(tempArrayData) )
				{
				case StageObject::_CONDITION_NONE_:
				case StageObject::_CONDITION_NOMAL_:
					break;
				case StageObject::_CONDITION_DAMAGE_:
					tempA = 200, tempR = 100, tempG = 50, tempB = 50;
					break;
	
				}
				
			m_pDrawManager->VertexDraw( _TEX_BLOCK_, tempX, tempY, 
				m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetWidth(), 
				m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetHeight(),
				0.f, 0.f, 
				1.f, 1.f,
				tempA, tempR, tempG, tempB);	///<	マスの描画
			}
			m_pDrawManager->VertexDraw( _TEX_BLOCKFRAME_, tempX, tempY, 
				m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetWidth(), 
				m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetHeight(),
				0.f, 0.f, 
				1.f, 1.f,
				100, 200, 200, 200);	///<	マスの描画
		}
	}
}

void StateManager::DrawLog()
{
	DirectXFont* const pDxFont =  &m_pDrawManager->m_dxFont;
	int logValue = 0;
	float tempX, tempY;

	//ログの枠表示
	if( m_playerID == 1 )
	{
		//	ゲームログ表示
		m_PlayerFrame[1].GetPosition( &tempX, &tempY );
		m_pDrawManager->VertexDraw( _TEX_GAMELOG_, tempX, tempY, 
			m_PlayerFrame[1].GetWidth(),  m_PlayerFrame[1].GetHeight(),
			0.f, 0.f, 1.f, 1.f,
			200, 255, 255, 255 );	///<	プレイヤー2の枠描画
	}
	else
	{
		//	ゲームログ表示
		m_PlayerFrame[0].GetPosition( &tempX, &tempY );
		m_pDrawManager->VertexDraw( _TEX_GAMELOG_, tempX, tempY, 
			m_PlayerFrame[0].GetWidth(),  m_PlayerFrame[0].GetHeight(),
			0.f, 0.f, 1.f, 1.f,
			200, 255, 255, 255 );	///<	プレイヤー1の枠描画
	}
	
	//	戦闘系ログ
	if( !m_gameLog.m_logStream.empty() )
	{
		logValue = m_gameLog.m_logStream.size();
		long tempX = 0, tempY = 0;
		unsigned int tempW = 0, tempH = 0;
		std::string* pStr;
		LPCSTR lpTempStr;
		std::list<LogStream*>::const_iterator itEnd = m_gameLog.m_logStream.end();
		for( std::list<LogStream*>::iterator it = m_gameLog.m_logStream.begin();
			it != itEnd; ++it)
		{
			(*it)->GetPosition( tempX, tempY );
			(*it)->GetSize( tempW, tempH );
			pStr = (*it)->GetStringPtr();
			lpTempStr = const_cast<char *>(pStr->c_str());
			if(pDxFont->DrawA( tempX, tempY, static_cast<unsigned long>(_LOG_FONT_WIDTH_), 
							tempH, lpTempStr, (*it)->GetColor(), (*it)->GetFormat() ))
			{

			}
		}
	}
	//	経過時間ログ
	if( !m_gameElapsed.m_logStream.empty() )
	{
		logValue = m_gameElapsed.m_logStream.size();
		long tempX = 0, tempY = 0;
		unsigned int tempW = 0, tempH = 0;
		std::string* pStr;
		LPCSTR lpTempStr;
		std::list<LogStream*>::const_iterator itEnd = m_gameElapsed.m_logStream.end();
		for( std::list<LogStream*>::iterator it = m_gameElapsed.m_logStream.begin();
			it != itEnd; ++it)
		{
			(*it)->GetPosition( tempX, tempY );
			(*it)->GetSize( tempW, tempH );
			pStr = (*it)->GetStringPtr();
			lpTempStr = const_cast<char *>(pStr->c_str());
			if(pDxFont->DrawA( tempX, tempY, tempW, tempH, lpTempStr, (*it)->GetColor(), (*it)->GetFormat() ))
			{

			}
		}
	}
	//	通信待ち中
	if( GetConnectFlag() )
	{
		//	通信中ログ
		if( !m_gameConnectState.m_logStream.empty() )
		{
			logValue = m_gameConnectState.m_logStream.size();
			long tempX = 0, tempY = 0;
			unsigned int tempW = 0, tempH = 0;
			std::string* pStr;
			LPCSTR lpTempStr;
			std::list<LogStream*>::const_iterator itEnd = m_gameConnectState.m_logStream.end();
			for( std::list<LogStream*>::iterator it = m_gameConnectState.m_logStream.begin();
				it != itEnd; ++it)
			{
				(*it)->GetPosition( tempX, tempY );
				(*it)->GetSize( tempW, tempH );
				pStr = (*it)->GetStringPtr();
				lpTempStr = const_cast<char *>(pStr->c_str());
				if(pDxFont->DrawA( tempX, tempY, tempW, tempH, lpTempStr, (*it)->GetColor(), (*it)->GetFormat() ))
				{

				}
			}
		}
	}
	
}
