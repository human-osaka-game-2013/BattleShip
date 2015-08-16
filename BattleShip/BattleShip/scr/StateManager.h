#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "Window.h"
#include "GameState.h"
#include "Player.h"
#include "StageObject.h"
#include "DrawManager.h"

#define _BLOCK_WIDTH_MAX_	23	///<�Ֆʂ̉����̍ő�u���b�N��
#define _BLOCK_HEIGHT_MAX_	(float)16	///<�Ֆʂ̏c���̍ő�u���b�N��
#define _STAGE_HEIGHT_MAX_	(float)11	///<�X�e�[�W�����̏c���̍ő�u���b�N��

class StateManager
{
public:
	/**
	*@brief	�퓬�X�e�[�g�p�^�[���̗�
	*/
	enum _STATE_NUM_
	{
		STATE_NONE = -1,
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
	};

public:
	/**
	*@brief	�Ֆʂ̃t���[���I�u�W�F�N�g�N���X�i�`��p�j
	*@details	�X�e�[�W��UI�v�f�Ȃǂ�ʂ̃N���X�Ƃ��Ď�������B@n
				�X�e�[�W��v���C���[���͕K�v�ɉ����ă����o������炤�B
	*/
	class BoardOfFrame : public CGameObject
	{
	private:
		float fWidth ,fHeight;

	public:
		/**
		*@brief	������
		*/
		void Init( float _fx, float _fy, float _fWidth, float _fHeight )
		{
			SetPosition(_fx, _fy, 0.5f);
			fHeight = _fHeight;
			fWidth = _fWidth;
		}
		void Control(){};
		void Draw(){};
		void Free(){};
		float GetWidth(){ return fWidth; }
		float GetHeight(){ return fHeight; }
	};

private:
	GameState*		m_pGameState;	///<	�퓬�X�e�[�g�p�^�[���I�u�W�F�N�g�̃|�C���^
	_STATE_NUM_		m_beforeState;	///<	�ȑO�̃X�e�[�g�p�^�[��
	_STATE_NUM_		m_currentState;	///<	���݂̃X�e�[�g�p�^�[��
	Player* const 	m_pPlayer1;		///<	�v���C���[1���i�[�|�C���^
	Player* const 	m_pPlayer2;		///<	�v���C���[2���i�[�|�C���^
	StageObject* const	m_pStageObject;	///<	�X�e�[�W���i�[�|�C���^
	BoardOfFrame	m_StageFrame;	///<	�X�e�[�W�����̃t���[���I�u�W�F�N�g
	BoardOfFrame*	m_pPlayerFrame;	///<	

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	StateManager( Player* const _pPlayer1, Player* const _pPlayer2,
		StageObject* const	_pStageObject);
	/**
	*@brief	�������
	*/
	void Free();

	/**
	*@brief	�X�e�[�g�p�^�[���̐؂�ւ�
	*param[in]	_stateType	
	*@return true�F�X�e�[�g�p�^�[���̕ύX�����B*n
			false�F�ύX���s
	*/
	bool ChangeState( _STATE_NUM_ _stateType );
	
	/**
	*@brief	�X�e�[�g�̏�����
	*/
	void StateInit();
	
	/**
	*@brief	�X�e�[�g�̊�{���[�`������
	*/
	void StateCotrol();

	/**
	*@brief	�X�e�[�g�̊�{�`��
	*/
	void StateDraw( CDrawManager* _drawManager);

	/**
	*@brief	�X�e�[�g�I�u�W�F�N�g�̏���
	*/
	void StateDelete();
};


#endif