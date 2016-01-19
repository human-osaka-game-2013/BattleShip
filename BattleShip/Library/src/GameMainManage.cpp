#include <stdio.h>
#include "SceneManage.h"

//---------------------------------------------------
//	�v���g�^�C�v�錾
//---------------------------------------------------


//	�V�[���N���X�̃��[�`���̐���
void CSceneManager::SceneRoutingManage ()
{
	int _SceneIDTemp = SCENE_NONE;

	if ( GetChangeSceneFlag() == true )
	{
		m_sceneObj -> Init ();
		UpdateChangeFlag ( false );	//	�V�[���ύX���I���A���������ʂ�������
		_SceneIDTemp = GetCurrentScene();
	}
	m_sceneObj->CountTimeInScene();	//	�V�[�������Ԃ̃J�E���g
	int iCntResult = m_sceneObj -> Control ();
	//	�e�V�[����Control�֐�����̕Ԃ�l��1�������ꍇ�ɃV�[���̐؂�ւ����s��
	switch ( iCntResult )
	{
	case 0:

		break;
	case 1:
		if ( GetCurrentScene()+1 < SCENE_MAX  )
		{
			iCurrentScene++;
		}
		else
		{
			iCurrentScene = SCENE_NONE+1;
		}
		m_sceneObj->SetSceneID( iCurrentScene );//	�ύX����V�[��ID������	
		UpdateChangeFlag(true);	//	�ύX�t���O�𗧂Ă�
		break;
	}
}