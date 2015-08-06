/**
*@file	GameScene.cpp
*@author	亀田
*/

#include "GameScene.h"

/**
*@todo	GameSceneのコンストラクタで、メンバのコンストラクタの要求が多くて、@n
		placement newというやり方でやろうと思うが上手くいかない。
*/
GameScene::GameScene( int _id, int _playerID, CRenderManager* const _pRenderManager,
	CDrawManager*	const _pDrawManager, CKey* const _pKey, CMouse* const m_pMouse )
	: CScene( _id, _pRenderManager,	_pDrawManager, _pKey, m_pMouse),
	m_Player(),
	m_stateManager(&m_Player[0],&m_Player[1],&m_stageObject),
	m_playerID( _playerID )
{
	
}

bool GameScene::Init()
{
	m_stateManager.StateInit();	///<	StateManagerオブジェクトを初期化
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player[iCount].Init( iCount );	///<	プレイヤーの初期化
	}
	m_stageObject.Init();

}


int GameScene::Control()
{
	m_stateManager.StateCotrol();
}

void GameScene::Draw()
{
	m_stateManager.StateDraw();
}