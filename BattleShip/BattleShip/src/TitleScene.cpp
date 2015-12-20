/**
*@file	TitleScene.cpp
*@author	�T�c
*/

#include "TitleScene.h"

bool TitleScene::Init()
{
	m_background.Init();
	m_title.Init( 0.f, 0.f, 1024.f, 256.f );
	m_rudder.Init( WIDTH/2.f, 128.f, 512.f, 512.f );

	m_screenMask.Init();
	m_button.Init( _BUTTON_POS_X_, _BUTTON_POS_Y_,
					_BUTTON_WIDTH_, _BUTTON_HEIGHT_,
					m_pAudio );

	/*
		�M�͌n�̏�����
	*/
	m_rewardButton.Init( _REWARD_BUTTON_X_,
						 _REWARD_BUTTON_Y_,
						 _COM_TYPE_BUTTON_WIDTH_,
						 _COM_TYPE_BUTTON_HEIGTH_,
						 m_pAudio);

	m_reward.GetDrawManagerPtr(m_pDrawManager);
	m_reward.InitReward( m_pAudio );
	/**/

	m_screenMask.SetColor( 255, 255, 255, 255);//�t�F�[�h�C�����������̂ŃA���t�@�l��255��

	m_changeSceneFlag = false;
	
	m_connectSetting.Init( m_pMouse, m_pKey, m_pAudio );

	m_stopFadeFlag = false;
	//	�^�C�g��BGM�Đ�
	m_pAudio->SoundPlay( Audio::_TITLE_BGM_, true );
	return true;
}


int TitleScene::Control()
{
	float tempX = (float)m_pMouse->GetCursorPosX();	///<	�}�E�X���W�̍X�V
	float tempY = (float)m_pMouse->GetCursorPosY();	///<	�}�E�X���W�̍X�V
	int	result = 0;

	//	�V�[�������鎞
	if( m_changeSceneFlag )
	{
		if( m_stopFadeFlag == false)
		{
			m_stopFadeFlag = m_screenMask.FadeOut(_FADE_OUT_TIME_);
		}

		//	�V�[���ύX
		if( m_stopFadeFlag )
		{
			result = 1;
		}
	}
	else
	{
		if( m_screenMask.FadeIn(_FADE_IN_TIME_) )
		{
			char inputState = m_pMouse->GetMouseSt( MOUSE_L );
			char buttonResult = m_button.Contorl( tempX, tempY, inputState );
			
			//	�Q�[���X�^�[�g�{�^����ɃJ�[�\������������
			if( buttonResult == Button::STATE_SELECT )
			{
				m_changeSceneFlag = true;
			}
			m_connectSetting.Control();

			/*
				�M�͊֘A�̏���
			*/
			bool rewardFlag = m_reward.GetDrawFlag();
			if(!rewardFlag)
			{
				buttonResult = m_rewardButton.Contorl( tempX, tempY, inputState );
			
				if( buttonResult == Button::STATE_SELECT )
				{
					m_reward.SetDrawFlag(true);
				}
				m_rewardButton.SetState( Button::STATE_OFF_CURSOR );
			}
			else
			{
				buttonResult = m_reward.ControlReward( tempX, tempY, inputState );
				if( buttonResult == Button::STATE_SELECT )
				{
					m_reward.SetDrawFlag(false);
				}
			}
			/**/
		}
	}
	return result;
}


void TitleScene::Draw()
{
	float tempX, tempY;
	int tempA, tempR, tempG, tempB;

	//	�w�i�`��
	m_background.GetPosition( &tempX, &tempY);
	m_pDrawManager->VertexDraw( _TEX_TITLE_BACK_, tempX, tempY, 
		m_background.GetWidth(),  m_background.GetHeight(),
		0.f, 0.f, 1.f, 1.f);
	
	//	�ǂ̕`��
	m_rudder.GetPosition( &tempX, &tempY);
	m_pDrawManager->CenterDraw( _TEX_TITLE_RUDDER_, tempX, tempY,
		static_cast<float>(GetTimeInScene()),
		m_rudder.GetWidth(),  m_rudder.GetHeight(),
		0.f, 0.f, 1.f, 1.f, 255, 150, 150, 150 );

	//	�^�C�g��
	m_title.GetPosition( &tempX, &tempY);
	m_pDrawManager->VertexDraw( _TEX_TITLE_MAIN_, tempX, tempY, 
		m_title.GetWidth(),  m_title.GetHeight(),
		0.f, 0.f, 1.f, 1.f);
	
	//	�Q�[���X�^�[�g�{�^���`��
	m_button.GetPosition( &tempX, &tempY);
	m_button.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->AnimationDraw( _TEX_BUTTONMAP_,tempX,tempY,
								   m_button.GetWidth(),m_button.GetHeight(),
								   false,false,0,3,
								   D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

	//	�t�F�[�h�p�̃}�X�N�`��
	m_screenMask.GetPosition( &tempX, &tempY);
	m_screenMask.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->VertexDraw( _TEX_TITLEMASK_, tempX, tempY, 
		m_screenMask.GetWidth(),  m_screenMask.GetHeight(),
		0.f, 0.f, 1.f, 1.f,	tempA, tempR, tempG, tempB);
	
	//	�ʐM�ݒ�`��
	m_connectSetting.Draw( m_pDrawManager );	

	//	�M�͕\���{�^���`��
	m_rewardButton.GetPosition( &tempX, &tempY);
	m_rewardButton.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->AnimationDraw( _TEX_BUTTONMAP_,tempX,tempY,
								   m_rewardButton.GetWidth(),
								   m_rewardButton.GetHeight(),
								   false,false,1,0, 
								   D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

	//	�M�͂̕`��
	m_reward.DrawReward();
}
