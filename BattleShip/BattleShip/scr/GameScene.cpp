/**
*@file	GameScene.cpp
*@author	�T�c
*/

#include "GameScene.h"

/**
*@todo	GameScene�̃R���X�g���N�^�ŁA�����o�̃R���X�g���N�^�̗v���������āA@n
		placement new�Ƃ��������ł�낤�Ǝv������肭�����Ȃ��B
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
	m_stateManager.StateInit();	///<	StateManager�I�u�W�F�N�g��������
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player[iCount].Init( iCount );	///<	�v���C���[�̏�����
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