/**
*@file	GameScene.cpp
*@author	�T�c
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
	m_stateManager.Init();	///<	StateManager�I�u�W�F�N�g��������
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player[iCount].Init( iCount );	///<	�v���C���[�̏�����
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