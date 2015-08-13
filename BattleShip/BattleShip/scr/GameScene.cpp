/**
*@file	GameScene.cpp
*@author	�T�c
*/

#include "GameScene.h"


bool GameScene::Init()
{
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player.push_back( new Player( iCount ));	///<	�v���C���[�̏�����
	}
	m_pStageObject = new( StageObject );		///<	StageObject�I�u�W�F�N�g�𐶐�
	m_stateManager = new StateManager(m_Player[0], m_Player[1], m_pStageObject);	///<	StateManager�I�u�W�F�N�g��������
	return true;
}


int GameScene::Control()
{
	m_stateManager->StateCotrol();

	return 0;
}

void GameScene::Draw()
{
	m_stateManager->StateDraw();
}

GameScene::~GameScene()
{
	for( int iCount = 0; iCount < m_Player.size(); iCount++ )
		delete m_Player[iCount];

	delete m_pStageObject;
	delete m_stateManager;
}