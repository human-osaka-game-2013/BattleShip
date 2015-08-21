/**
*@file	GameScene.cpp
*@author	�T�c
*/

#include "GameScene.h"

/**
*@brief	�Q�[���V�[��������
*@details	���݃����o�N���X�̏������֐��̈����̖�������A�����ŊǗ��N���X�Ȃǂ��Z�b�g���Ă��K�v������B@n

*/
bool GameScene::Init()
{
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player.push_back( new Player( iCount ));	///<	�v���C���[�̏�����
	}
	m_background.Init();	///<	�w�i�I�u�W�F�N�g�̏�����

	m_pStageObject = new( StageObject );		///<	StageObject�I�u�W�F�N�g�𐶐�
	m_pStageObject->Init();
	m_stateManager = new StateManager(m_Player[0], m_Player[1], m_pStageObject, _PLAYER_ID_);	///<	StateManager�I�u�W�F�N�g��������
		
	//	�����͌�Ƀ����o�̃I�u�W�F�N�g�ɂ��Ǘ��N���X���Z�b�g����K�v������̂ŁA
	//	���Ԃɒ���
	m_stateManager->SetDraw( m_pDrawManager );	///<	�`��Ǘ��N���X�̃A�h���X�Z�b�g
	m_stateManager->SetMouse( m_pMouse );		///<	�}�E�X�Ǘ��N���X�̃A�h���X�Z�b�g
	m_stateManager->StateInit();

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

//	�������
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
