/**
*@file	TitleScene.h
*@author	�T�c
*/

#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "SceneInterface.h"
#include "Background.h"
#include "ScreenMask.h"
#include "ConnectSetting.h"
#include "Reward.h"

#define _BUTTON_POS_X_  150.0f
#define _BUTTON_POS_Y_	500.0f
#define _BUTTON_WIDTH_	226.0f
#define _BUTTON_HEIGHT_	50.0f
#define _CHANGE_TIME_	3.0f*60.f
#define _REWARD_BUTTON_X_	50.f
#define _REWARD_BUTTON_Y_	650.f

/**
*@brief	�^�C�g���V�[���N���X
*/
class TitleScene : public CScene {
 public:
	/**
	*@brief	�R���X�g���N�^
	*@details	�g��Ȃ��Ǘ��|�C���^������ꍇNULL�|�C���^������
	*@param[in]	_id	�������g�̃V�[��ID
	*@param[in]	_pRenderManager	3D�`��Ǘ��̃|�C���^
	*@param[in]	_pDrawManager	2D�`��Ǘ��̃|�C���^
	*@param[in]	_pKey			�L�[�Ǘ��̃|�C���^
	*@param[in]	m_pMouse		�}�E�X�Ǘ��̃|�C���^
	*/
	TitleScene(int _id,
			   CRenderManager* const _pRenderManager,
			   CDrawManager* const _pDrawManager,
			   CKey* const _pKey,
			   CMouse* const m_pMouse,
			   Audio* const _pAudio )
			   : CScene( _id, _pRenderManager, _pDrawManager, _pKey, m_pMouse, _pAudio) {}

	/**
	*@breif	�f�X�g���N�^
	*/
	~TitleScene() {

	}

	/**
	*@brief	�Q�[�����C���̏������֐�
	*@return	�������̌���
	*@retval true	����
	*@retval false	�������ɉ��炩�̎��s���������ꍇ
	*/
	bool Init();

	/**
	*@brief	�Q�[�����C���̊�{�����̊֐�
	*@return	�V�[���ύX�����锻�f�̒l
	*@retval 0	�V�[���ύX����
	*@retval 1	�V�[���ύX�L��
	*/
	int	 Control();

	/**
	*@brief	2D�`��
	*/
	void Draw();
	void Render(){};

 private:
	Background	m_background;	///<�w�i�I�u�W�F�N�g
	Background	m_title;		///<�^�C�g���I�u�W�F�N�g
	Background	m_rudder;		///<�ǂ̃I�u�W�F�N�g�i�Q�[���̕��͋C���̈�

	ScreenMask	m_screenMask;	///<��ʑJ�ڎ��̃t�F�[�h�p
	Button		m_button;		///<�{�^���I�u�W�F�N�g�i�����_�ł̓Q�[�����X�^�[�g���鎞�Ɏg�p�j
	Button		m_rewardButton;
	ConnectSetting	m_connectSetting;
	Reward		m_reward;
	
	bool		m_changeSceneFlag;
	bool		m_stopFadeFlag;	///<�t�F�[�h��~�i�I���j�t���O

};

#endif