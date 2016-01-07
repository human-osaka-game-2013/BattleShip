/**
*@file	GameScene.cpp
*@author	亀田
*/
#include "GameScene.h"

#include "DebugNew.h"

/**
*@brief	ゲームシーン初期化
*@details	現在メンバクラスの初期化関数の引数の問題もあり、ここで管理クラスなどをセットしてやる必要がある。@n
*/
bool GameScene::Init()
{
#ifdef _NOT_USE_COM_
	
#else
	//	ゲーム部分が始まったので通信の初期化をする
	m_Connect.Init();

	m_connectionResult = m_Connect.Connection();
	
#endif
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player.push_back( new Player( iCount ));	///<	プレイヤーの初期化
	}

	m_background.Init();	///<	背景オブジェクトの初期化
	m_screenMask.Init();	///<	フェード用オブジェクト初期化
	m_screenMask.SetColor( 255, 255, 255, 255);//フェードインさせたいのでアルファ値は255で

	m_pStageObject = new( StageObject );		///<	StageObjectオブジェクトを生成
	m_pStageObject->Init();

	m_playerID = m_Connect.m_sockType ? 2:1;	///<　サーバー側なら1クライアント側なら2
	m_stateManager = new StateManager(m_Player[0], m_Player[1], m_pStageObject, m_playerID);	///<	StateManagerオブジェクトを初期化
		
	//	ここは後にメンバのオブジェクトにも管理クラスをセットする必要があるので、
	//	順番に注意
	m_stateManager->SetDraw( m_pDrawManager );	///< 描画管理クラスのアドレスセット
	m_stateManager->SetMouse( m_pMouse );		///< マウス管理クラスのアドレスセット
	m_stateManager->SetAudio( m_pAudio );		///< 音声再生クラスアのドレスセット
	m_stateManager->StateInit();
	
	m_fadeInFlag = true;	
	m_fadeOutFlag = false;

	//	ゲームBGM再生
#ifdef _DEBUG
	m_pAudio->SoundPlay( Audio::_WIN_BGM_, true );
#else
	m_pAudio->SoundPlay( Audio::_BATTLE_BGM_, true );
#endif
	return true;
}


int GameScene::Control()
{
	//もし接続に失敗していた状態でここまで来ていた場合、タイトルに戻す
	if( !m_connectionResult )
		return 1;

	m_stateManager->UpdateStatInTime( GetTimeInScene() );	///<経過時間の更新状態をステート側に伝える

	if( m_stateManager->GetConnectFlag() )
	{
#ifdef _NOT_USE_COM_
		if(1)//通信が完了した場合
		{
			m_stateManager->SetConnectFlag( false );
		}

#else
		if( CommunicationProcessing() )	//通信が完了した場合
		{
			m_stateManager->SetConnectFlag( false );
		}		

#endif
	}

	if( m_fadeInFlag )
	{
		if( m_screenMask.FadeIn(_FADE_IN_TIME_) )
			m_fadeInFlag = false;
	}
	else if( !GetSceneEndFlag() )
	{
		//	フェードインし終わって、かつ戦闘が終了していないので
		//	各ステート管理の処理へ移る
		if( m_stateManager->StateCotrol() == -1)
		{
			//各ステートの結果により戦闘が終了されたので、
			//フェードアウトさせてからこのシーンを終了させる。
			SetSceneEndFlag( true );
		}
	}
	else if( m_pMouse->MouseStCheck( MOUSE_L, PUSH ) )
	{
		m_fadeOutFlag = true;
	}
	//	フェードアウトさせていき、完了すればシーンを終了させる
	if( m_fadeOutFlag )
	{
		if( m_screenMask.FadeOut(_FADE_OUT_TIME_) )
		{
			m_fadeInFlag = false;
			return 1;	//シーンを終了させる
		}
	}

	return 0;
}

void GameScene::Draw()
{
	
	BackGroundDraw();
	
	m_stateManager->StateDraw();

	ScreenMaskDrawa();
}


void GameScene::BackGroundDraw()
{
	float tempX, tempY;
	
	m_background.GetPosition( &tempX, &tempY);
	m_pDrawManager->AnimationDraw( _TEX_BACKGROUND_, tempX, tempY, 
		m_background.GetWidth(),  m_background.GetHeight(),
		static_cast<unsigned int>(GetTimeInScene()*3) );
}


void GameScene::ScreenMaskDrawa()
{
	float tempX, tempY;
	int tempA, tempR, tempG, tempB;

	//	フェード用のマスク描画
	m_screenMask.GetPosition( &tempX, &tempY);
	m_screenMask.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->VertexDraw( _TEX_GAMEMASK_, tempX, tempY, 
		m_screenMask.GetWidth(),  m_screenMask.GetHeight(),
		0.f, 0.f, 1.f, 1.f,	tempA, tempR, tempG, tempB);
}

//	通信処理
bool GameScene::CommunicationProcessing()
{
	bool result = false;

	switch( m_stateManager->GetState() )
	{
	case StateManager::STATE_SET_SHIP:
	case StateManager::STATE_SELECTION:
		if( !(m_connectFlag&_BIT_STAGE_R_) )
		{
			result = ComStageData();
		}
		else if( !(m_connectFlag&_BIT_SHIP_R_) )
		{
			result = ComShipsData();
		}
		break;
	}
	//	全部の情報の送受信が完了していたら
	if( m_sendShipCount==ShipObject::TYPE_MAX && (m_connectFlag==_BIT_ALL_SR_) )
	{
		m_connectFlag = m_connectFlag^_BIT_ALL_SR_;
		m_sendShipCount = 0;
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

bool GameScene::ComStageData()
{
	int bufStageSize = sizeof(ConnectStage);
	ConnectStage bufStage;
	int enemyID = m_Connect.m_sockType ? 1:2;	//通信クラスの種類から相手のIDを調べる
	bool result = false;

	//	まだ送信を完了してなかったら
	if( !(m_connectFlag&_BIT_STAGE_S_) )
	{
		memmove_s( bufStage.m_stageArray, sizeof(int [_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_]),
		m_pStageObject->m_stageArray, sizeof(int [_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_]));

		if( m_Connect.Send( (char*)&bufStage, bufStageSize ))
		{
			m_connectFlag += _BIT_STAGE_S_;
		}
		else
		{
			result = false;
		}
	}
	//	まだ受信を完了してなかったら
	if( !(m_connectFlag&_BIT_STAGE_R_) )
	{
		if( m_Connect.Receive( (char*)&bufStage, bufStageSize ) )
		{
			m_pStageObject->MargeStage( &bufStage, m_playerID, enemyID, (int)m_stateManager->GetState() );
			m_connectFlag += _BIT_STAGE_R_;
			result = true;
		}
		else
		{
			result = false;
		}
	}
	else
	{
		result = true;
	}
	return result;
}

bool GameScene::ComShipsData()
{
	int bufShipSize = sizeof(ConnectShip);
	ConnectShip bufShip[ShipObject::TYPE_MAX];
	int enemyID = m_Connect.m_sockType ? 1:2;	//通信クラスの種類から相手のIDを調べる
	ShipObject* tempShip;
	bool result = false;

	for( int iShip = m_sendShipCount; iShip < ShipObject::TYPE_MAX; iShip++ )
	{
		//	まだ送信を完了してなかったら
		if( !(m_connectFlag&_BIT_SHIP_S_) )
		{
			ShipObject* tempShip = m_Player[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
			tempShip->SetConnectShipData( &bufShip[iShip] );

			if( m_Connect.Send( (char*)&bufShip[iShip], bufShipSize ))
			{
				m_connectFlag += _BIT_SHIP_S_;
			}
			else
			{
				result = false;
			}
		}
		//	まだ受信を完了してなかったら
		if( !(m_connectFlag&_BIT_SHIP_R_) )
		{
			if( m_Connect.Receive( (char*)&bufShip[iShip], bufShipSize ))
			{
				tempShip = m_Player[enemyID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
				tempShip->SetShipData( &bufShip[iShip] );
				m_sendShipCount++;	//	正常に受け取れたので、カウンタをインクリメント

				//	全ての駒情報を送受信出来ていれば、送信フラグをtrue
				m_connectFlag = m_sendShipCount==ShipObject::TYPE_MAX ? _BIT_ALL_SR_ : m_connectFlag>>1;
				result = true;
			}
			else
			{
				result = false;
			}
		}
		if( result == false )
			break;
	}
	return result;
}