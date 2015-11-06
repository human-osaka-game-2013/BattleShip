/**
*@file	GameScene.cpp
*@author	�T�c
*/
#include "GameScene.h"

#include "DebugNew.h"

/**
*@brief	�Q�[���V�[��������
*@details	���݃����o�N���X�̏������֐��̈����̖�������A�����ŊǗ��N���X�Ȃǂ��Z�b�g���Ă��K�v������B@n
*/
bool GameScene::Init()
{
	m_gameEndFlag = false;

#ifdef _NOT_USE_COM_
	
#else
	//	�Q�[���������n�܂����̂ŒʐM�̏�����������
	m_Connect.Init();

	m_Connect.Connection();

#endif
	for( int iCount=0; iCount<_PLAYER_NUM_; iCount++ ) {
		m_Player.push_back( new Player( iCount ));	///<	�v���C���[�̏�����
	}

	m_background.Init();	///<	�w�i�I�u�W�F�N�g�̏�����
	m_screenMask.Init();	///<	�t�F�[�h�p�I�u�W�F�N�g������
	m_screenMask.SetColor( 255, 255, 255, 255);//�t�F�[�h�C�����������̂ŃA���t�@�l��255��

	m_pStageObject = new( StageObject );		///<	StageObject�I�u�W�F�N�g�𐶐�
	m_pStageObject->Init();

	m_playerID = m_Connect.m_sockType ? 2:1;	///<�@�T�[�o�[���Ȃ�1�N���C�A���g���Ȃ�2
	m_stateManager = new StateManager(m_Player[0], m_Player[1], m_pStageObject, m_playerID);	///<	StateManager�I�u�W�F�N�g��������
		
	//	�����͌�Ƀ����o�̃I�u�W�F�N�g�ɂ��Ǘ��N���X���Z�b�g����K�v������̂ŁA
	//	���Ԃɒ���
	m_stateManager->SetDraw( m_pDrawManager );	///<	�`��Ǘ��N���X�̃A�h���X�Z�b�g
	m_stateManager->SetMouse( m_pMouse );		///<	�}�E�X�Ǘ��N���X�̃A�h���X�Z�b�g
	m_stateManager->StateInit();
	
	return true;
}


int GameScene::Control()
{
	static bool fadeInFlag = true;	//�Q�[���J�n���̓t�F�[�h�C��������

	
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
		if(1)//�ʐM�����������ꍇ
		{
			m_stateManager->SetConnectFlag( false );
		}

#else
		if( CommunicationProcessing() )	//�ʐM�����������ꍇ
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

	//	�t�F�[�h�p�̃}�X�N�`��
	m_screenMask.GetPosition( &tempX, &tempY);
	m_screenMask.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->VertexDraw( _TEX_TITLEMASK_, tempX, tempY, 
		m_screenMask.GetWidth(),  m_screenMask.GetHeight(),
		0.f, 0.f, 1.f, 1.f,	tempA, tempR, tempG, tempB);
}


//	�ʐM����
bool GameScene::CommunicationProcessing()
{
	int bufStageSize = sizeof(ConnectStage);
	int bufShipSize = sizeof(ConnectShip);
	ConnectStage bufStage;
	ConnectShip bufShip[ShipObject::TYPE_MAX];
	int enemyID = m_Connect.m_sockType ? 1:2;	//�ʐM�N���X�̎�ނ��瑊���ID�𒲂ׂ�


	switch( m_stateManager->GetState() )
	{
	case StateManager::STATE_SET_SHIP:
	case StateManager::STATE_SELECTION:
	
		if( !m_Connect.m_sockType )	//	�T�[�o�[���Ȃ��Ɏ�M���s��
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
		else	//	�N���C�A���g���Ȃ��ɑ��M���s��
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
