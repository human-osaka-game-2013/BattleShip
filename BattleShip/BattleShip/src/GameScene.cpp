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
#ifdef _NOT_USE_COM_
	
#else
	//	�Q�[���������n�܂����̂ŒʐM�̏�����������
	m_Connect.Init();

	m_connectionResult = m_Connect.Connection();
	
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
	m_stateManager->SetDraw( m_pDrawManager );	///< �`��Ǘ��N���X�̃A�h���X�Z�b�g
	m_stateManager->SetMouse( m_pMouse );		///< �}�E�X�Ǘ��N���X�̃A�h���X�Z�b�g
	m_stateManager->SetAudio( m_pAudio );		///< �����Đ��N���X�A�̃h���X�Z�b�g
	m_stateManager->StateInit();
	
	m_fadeInFlag = true;	
	m_fadeOutFlag = false;

	//	�Q�[��BGM�Đ�
#ifdef _DEBUG
	m_pAudio->SoundPlay( Audio::_WIN_BGM_, true );
#else
	m_pAudio->SoundPlay( Audio::_BATTLE_BGM_, true );
#endif
	return true;
}


int GameScene::Control()
{
	//�����ڑ��Ɏ��s���Ă�����Ԃł����܂ŗ��Ă����ꍇ�A�^�C�g���ɖ߂�
	if( !m_connectionResult )
		return 1;

	m_stateManager->UpdateStatInTime( GetTimeInScene() );	///<�o�ߎ��Ԃ̍X�V��Ԃ��X�e�[�g���ɓ`����

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

	if( m_fadeInFlag )
	{
		if( m_screenMask.FadeIn(_FADE_IN_TIME_) )
			m_fadeInFlag = false;
	}
	else if( !GetSceneEndFlag() )
	{
		//	�t�F�[�h�C�����I����āA���퓬���I�����Ă��Ȃ��̂�
		//	�e�X�e�[�g�Ǘ��̏����ֈڂ�
		if( m_stateManager->StateCotrol() == -1)
		{
			//�e�X�e�[�g�̌��ʂɂ��퓬���I�����ꂽ�̂ŁA
			//�t�F�[�h�A�E�g�����Ă��炱�̃V�[�����I��������B
			SetSceneEndFlag( true );
		}
	}
	else if( m_pMouse->MouseStCheck( MOUSE_L, PUSH ) )
	{
		m_fadeOutFlag = true;
	}
	//	�t�F�[�h�A�E�g�����Ă����A��������΃V�[�����I��������
	if( m_fadeOutFlag )
	{
		if( m_screenMask.FadeOut(_FADE_OUT_TIME_) )
		{
			m_fadeInFlag = false;
			return 1;	//�V�[�����I��������
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

	//	�t�F�[�h�p�̃}�X�N�`��
	m_screenMask.GetPosition( &tempX, &tempY);
	m_screenMask.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->VertexDraw( _TEX_GAMEMASK_, tempX, tempY, 
		m_screenMask.GetWidth(),  m_screenMask.GetHeight(),
		0.f, 0.f, 1.f, 1.f,	tempA, tempR, tempG, tempB);
}

//	�ʐM����
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
	//	�S���̏��̑���M���������Ă�����
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
	int enemyID = m_Connect.m_sockType ? 1:2;	//�ʐM�N���X�̎�ނ��瑊���ID�𒲂ׂ�
	bool result = false;

	//	�܂����M���������ĂȂ�������
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
	//	�܂���M���������ĂȂ�������
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
	int enemyID = m_Connect.m_sockType ? 1:2;	//�ʐM�N���X�̎�ނ��瑊���ID�𒲂ׂ�
	ShipObject* tempShip;
	bool result = false;

	for( int iShip = m_sendShipCount; iShip < ShipObject::TYPE_MAX; iShip++ )
	{
		//	�܂����M���������ĂȂ�������
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
		//	�܂���M���������ĂȂ�������
		if( !(m_connectFlag&_BIT_SHIP_R_) )
		{
			if( m_Connect.Receive( (char*)&bufShip[iShip], bufShipSize ))
			{
				tempShip = m_Player[enemyID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
				tempShip->SetShipData( &bufShip[iShip] );
				m_sendShipCount++;	//	����Ɏ󂯎�ꂽ�̂ŁA�J�E���^���C���N�������g

				//	�S�Ă̋���𑗎�M�o���Ă���΁A���M�t���O��true
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