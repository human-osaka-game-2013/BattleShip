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
	m_gameEndFlag = false;

#ifdef _NOT_USE_COM_
	
#else
	//	ゲーム部分が始まったので通信の初期化をする
	m_Connect.Init();

	m_Connect.Connection();

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
	m_stateManager->SetDraw( m_pDrawManager );	///<	描画管理クラスのアドレスセット
	m_stateManager->SetMouse( m_pMouse );		///<	マウス管理クラスのアドレスセット
	m_stateManager->StateInit();
	
	return true;
}


int GameScene::Control()
{
	static bool fadeInFlag = true;	//ゲーム開始時はフェードインさせる

	
	if(m_stateManager->StateCotrol() == -1)
	{
		return 1;
	}
	
	if( fadeInFlag )
	{
		if( m_screenMask.FadeIn(_FADE_IN_TIME_) )
			fadeInFlag = false;
	}
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
	return 0;
}

void GameScene::Draw()
{
	float tempX, tempY;
	int tempA, tempR, tempG, tempB;

	m_background.GetPosition( &tempX, &tempY);
	m_pDrawManager->VertexDraw( _TEX_BACKGROUND_, tempX, tempY, 
		m_background.GetWidth(),  m_background.GetHeight(),
		0.f, 0.f, 1.f, 1.f);
	m_stateManager->StateDraw( m_pDrawManager );

	//	フェード用のマスク描画
	m_screenMask.GetPosition( &tempX, &tempY);
	m_screenMask.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->VertexDraw( _TEX_TITLEMASK_, tempX, tempY, 
		m_screenMask.GetWidth(),  m_screenMask.GetHeight(),
		0.f, 0.f, 1.f, 1.f,	tempA, tempR, tempG, tempB);
}


//	通信処理
bool GameScene::CommunicationProcessing()
{
	int bufStageSize = sizeof(ConnectStage);
	int bufShipSize = sizeof(ConnectShip);
	ConnectStage bufStage;
	ConnectShip bufShip[ShipObject::TYPE_MAX];
	int enemyID = m_Connect.m_sockType ? 1:2;	//通信クラスの種類から相手のIDを調べる


	switch( m_stateManager->GetState() )
	{
	case StateManager::STATE_SET_SHIP:
	case StateManager::STATE_SELECTION:
	
		if( !m_Connect.m_sockType )	//	サーバー側なら先に受信を行う
		{
			if( m_Connect.Receive( (char*)&bufStage, bufStageSize ) )
			{
				m_pStageObject->MargeStage( &bufStage, m_playerID, enemyID, (int)m_stateManager->GetState() );
				memmove_s( bufStage.m_stageArray, sizeof(int [_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_]),
							m_pStageObject->m_stageArray, sizeof(int [_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_]));
				if( m_Connect.Send( (char*)&bufStage, bufStageSize ))
				{

				}
			}
			else
			{
				return false;
			}
			for( int iShip = 0; iShip < ShipObject::TYPE_MAX; iShip++ )
			{
				if( m_Connect.Receive( (char*)&bufShip[iShip], bufShipSize ))
				{
					ShipObject* tempShip = m_Player[enemyID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
					tempShip->SetShipData( &bufShip[iShip] );

					tempShip = m_Player[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
					tempShip->SetConnectShipData( &bufShip[iShip] );
					
					if( m_Connect.Send( (char*)&bufShip[iShip], bufShipSize ))
					{

					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			
		}
		else	//	クライアント側なら先に送信を行う
		{
			memmove_s( bufStage.m_stageArray, sizeof(int [_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_]),
				m_pStageObject->m_stageArray, sizeof(int [_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_]));

			if( m_Connect.Send( (char*)&bufStage, bufStageSize ))
			{
				if( m_Connect.Receive( (char*)&bufStage, bufStageSize ) )
				{
					m_pStageObject->MargeStage( &bufStage, m_playerID, enemyID, (int)m_stateManager->GetState() );
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
			for( int iShip = 0; iShip < ShipObject::TYPE_MAX; iShip++ )
			{
				ShipObject* tempShip = m_Player[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
				tempShip->SetConnectShipData( &bufShip[iShip] );
				if( m_Connect.Send( (char*)&bufShip[iShip], bufShipSize ))
				{
					if( m_Connect.Receive( (char*)&bufShip[iShip], bufShipSize ))
					{
						tempShip = m_Player[enemyID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
						tempShip->SetShipData( &bufShip[iShip] );
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}

		}
		break;
	
	case StateManager::STATE_RESULT:
	case StateManager::STATE_STAGE_EFFECT:
		

		break;
	}
	return true;
}
