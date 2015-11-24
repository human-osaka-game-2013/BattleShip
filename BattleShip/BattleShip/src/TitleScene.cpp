/**
*@file	TitleScene.cpp
*@author	�T�c
*/

#include "TitleScene.h"

bool TitleScene::Init()
{
	m_background.Init();
	m_screenMask.Init();
	m_button.Init( _BUTTON_POS_X_, _BUTTON_POS_Y_,
					_BUTTON_WIDTH_, _BUTTON_HEIGHT_ );
	m_screenMask.SetColor( 255, 255, 255, 255);//�t�F�[�h�C�����������̂ŃA���t�@�l��255��

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
		m_changeSceneTime -= 1.f;
		if( m_stopFadeFlag == false)
		{
			m_stopFadeFlag = m_screenMask.FadeOut(_FADE_OUT_TIME_);
		}

		//	�V�[���ύX
		if( m_changeSceneTime <= 0.f || m_stopFadeFlag )
		{
			result = 1;
		}
	}
	else
	{
		if( m_screenMask.FadeIn(_FADE_IN_TIME_) )
		{
			//	�Q�[���X�^�[�g�{�^����ɃJ�[�\������������
			if( m_button.HitBlockCheck( tempX, tempY ) && !m_changeSceneFlag )
			{
				m_button.SetPosition( _BUTTON_POS_X_-1.f, _BUTTON_POS_Y_-1.f, 0.5f );
				m_button.SetColor( 255, 200, 200, 200 );
				m_button.SetWidth( _BUTTON_WIDTH_+2.f );
				m_button.SetHeight( _BUTTON_HEIGHT_+2.f );
				//	�E�N���b�N
				if(m_pMouse->MouseStCheck( MOUSE_L, PUSH ))
				{
					m_button.SetPosition( _BUTTON_POS_X_, _BUTTON_POS_Y_, 0.5f );
					m_button.SetColor( 255, 200, 200, 200 );
					m_button.SetWidth( _BUTTON_WIDTH_ );
					m_button.SetHeight( _BUTTON_HEIGHT_ );
					m_changeSceneFlag = true;
					m_pAudio->SoundPlay( Audio::_CLICK_SE_ );
				}
			}
			else{
				m_button.SetPosition( _BUTTON_POS_X_, _BUTTON_POS_Y_, 0.5f );
				m_button.SetColor( 255, 255, 255, 255 );
				m_button.SetWidth( _BUTTON_WIDTH_ );
				m_button.SetHeight( _BUTTON_HEIGHT_ );
			}
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
	
	//	�Q�[���X�^�[�g�{�^���`��
	m_button.GetPosition( &tempX, &tempY);
	m_button.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->VertexDraw( _TEX_STARTBUTTON_, tempX, tempY, 
		m_button.GetWidth(),  m_button.GetHeight(),
		0.f, 0.f, 1.f, 1.f, tempA, tempR, tempG, tempB);

	//	�t�F�[�h�p�̃}�X�N�`��
	m_screenMask.GetPosition( &tempX, &tempY);
	m_screenMask.GetColor( tempA, tempR, tempG, tempB );
	m_pDrawManager->VertexDraw( _TEX_TITLEMASK_, tempX, tempY, 
		m_screenMask.GetWidth(),  m_screenMask.GetHeight(),
		0.f, 0.f, 1.f, 1.f,	tempA, tempR, tempG, tempB);
	
	
}
