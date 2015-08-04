/**
*@file	GameScene.cpp
*@author	亀田
*/

#include "GameScene.h"

GameScene::GameScene( int _id, int _playerID, CRenderManager* const _pRenderManager,
	CDrawManager*	const _pDrawManager, CKey* const _pKey, CMouse* const m_pMouse )
	: CScene( _id, _pRenderManager,	_pDrawManager, _pKey, m_pMouse), m_playerID( _playerID )
{
	Init();
}

bool GameScene::Init()
{
	m_stateManager.Init();	///<	StateManagerオブジェクトを初期化
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player[iCount].Init( iCount );	///<	プレイヤーの初期化
	}
	m_stageObject.Init();

}


int GameScene::Control()
{
	m_stateManager.Cotrol();
}

void GameScene::Draw()
{
	m_stateManager.Draw();
}