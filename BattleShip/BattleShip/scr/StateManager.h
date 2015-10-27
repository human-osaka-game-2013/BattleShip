#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "GameState.h"
#include "Player.h"
#include "StageObject.h"
#include "DrawStructList.h"
#include "BoardOfFrame.h"


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

	
//	�ʏ�̃����o�ϐ�
private:
	GameState*		m_pGameState;	///<	�퓬�X�e�[�g�p�^�[���I�u�W�F�N�g�̃|�C���^
	_STATE_NUM_		m_beforeState;	///<	�ȑO�̃X�e�[�g�p�^�[��
	_STATE_NUM_		m_currentState;	///<	���݂̃X�e�[�g�p�^�[��
	StageObject* const	m_pStageObject;	///<	�X�e�[�W���i�[�|�C���^
	ShipObject::_SHIP_TYPE_NUM_	m_currentShip;	///<	���ݑI��Ώۂ̋�BGameState�Ƌ��L���邽�ߎ�舵���ɒ��ӁI
	
//	���̃I�u�W�F�N�g�ƒl�̂���肷��\���̂���ϐ�
private:
	
	Player* const 	m_pPlayer1;		///<	�v���C���[1���i�[�|�C���^
	Player* const 	m_pPlayer2;		///<	�v���C���[2���i�[�|�C���^
	const int		m_playerID;		///<	�N�����̃v���C���[ID�BGameScene�����������Ă���B

	bool			m_connectFlag;	///<	�ʐM���s���t���O

	int m_selectType;	///< �I�������s���̎��

	int m_resultPlayer;	///<	�v���C���[���ɋN���Ă���퓬����
	int m_resultEnemy;	///<	�G���ɋN���Ă���퓬����
	int m_resultBattle;	///<	���҂̐틵����

//	�X�e�[�g���ʂ̕`��I�u�W�F�N�g�̏��
private:
	BoardOfFrame	m_StageFrame;	///<	�X�e�[�W�����̃t���[���I�u�W�F�N�g
	BoardOfFrame	m_PlayerFrame[_PLAYER_NUM_];	///<	�v���C���[���̃t���[���I�u�W�F�N�g	
//	BoardOfFrame	m_ShipFrame[_PLAYER_NUM_][ShipObject::TYPE_MAX];

//	�f�o�C�X
private:
	CDrawManager*	m_pDrawManager;	///<	2D�`��Ǘ��N���X�|�C���^(const�|�C���^)
	CMouse*			m_pMouse;		///<	�}�E�X�Ǘ��N���X�|�C���^(const�|�C���^)

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	StateManager( Player* const _pPlayer1, Player* const _pPlayer2,
		StageObject* const	_pStageObject, const int _playerID );

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

	/**
	*@brief	�������
	*/
	void Free();

	/**
	*@brief	�X�e�[�g��Ԃ̎擾
	*/
	_STATE_NUM_ GetState(){ return m_currentState; }

private:
	/**
	*@brief	�X�e�[�g�p�^�[���̐؂�ւ�
	*@details	�e�X�e�[�g��Control���Ă�ŁA���̌��ʂȂǂ���A
				�p�^�[���ύX�̕K�v�����邩�Ǘ��B
	*@return true�F�X�e�[�g�p�^�[���̕ύX�̕K�v����B*n
			false�F�ύX�̕K�v����
	*/
	bool CheckState();

	/**
	*@brief	�X�e�[�g�p�^�[���̐؂�ւ�
	*param[in]	_stateType	
	*@return true�F�X�e�[�g�p�^�[���̕ύX�����B*n
			false�F�ύX���s
	*/
	bool ChangeState( _STATE_NUM_ _stateType );

public:
	/**
	*@brief	�`��N���X�Z�b�g
	*/
	void SetDraw( CDrawManager* const _pDrawManager ){
		m_pDrawManager = _pDrawManager;
	}

	/**
	*@brief	�}�E�X�N���X�Z�b�g
	*/
	void SetMouse( CMouse* const _pMouse ){
		m_pMouse = _pMouse;
	}
	
	/**
	*@brief	�ʐM���s���t���O���擾
	*/
	const bool GetConnectFlag(){ return m_connectFlag; }

	/**
	*@breif	�ʐM���s���t���O���X�V
	*/
	void SetConnectFlag( const bool _flag ){ m_connectFlag = _flag; }

};


#endif