/**
*@file	GameScene.cpp
*@author	亀田
*/

#include "GameScene.h"


bool GameScene::Init()
{
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player.push_back( new Player( iCount ));	///<	プレイヤーの初期化
	}
	m_pStageObject = new( StageObject );		///<	StageObjectオブジェクトを生成
	m_stateManager = new StateManager(m_Player[0], m_Player[1], m_pStageObject, _PLAYER_ID_);	///<	StateManagerオブジェクトを初期化
	m_background.Init();
	
	return true;
}


int GameScene::Control()
{
	float tempX, tempY;
	m_background.GetPosition( &tempX, &tempY);
	m_pDrawManager->VertexDraw( _TEX_BACKGROUND_, tempX, tempY, 
		m_background.GetWidth(),  m_background.GetHeight(),
		0.f, 0.f, 1.f, 1.f);
	m_stateManager->StateCotrol();

	return 0;
}

void GameScene::Draw()
{

	m_stateManager->StateDraw( m_pDrawManager );
}

//	解放処理
bool GameScene::Free()
{
	for( int iCount = 0; iCount < m_Player.size(); iCount++ ){
		m_Player[iCount]->Free();
		delete m_Player[iCount];
	}
	m_pStageObject->Free();
	delete m_pStageObject;
	m_stateManager->Free();
	delete m_stateManager;

	return true;
}
