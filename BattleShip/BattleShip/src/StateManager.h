#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "GameState.h"
#include "Player.h"
#include "StageObject.h"
#include "DrawStructList.h"
#include "BoardOfFrame.h"
#include "GameLog.h"

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
	std::string		m_tempStr1;
	std::string		m_tempStr2;
	int				m_beforeShip;	///<�O�t���[���őI���i�Ώہj����Ă�����ێ����Ă����B�ŏ��ɓ����Ă����ꍇ�͏����l�Ƃ���-1�����Ă���B
//	���̃I�u�W�F�N�g�ƒl�̂���肷��\���̂���ϐ�
private:
	
	Player* const 	m_pPlayer1;		///<	�v���C���[1���i�[�|�C���^
	Player* const 	m_pPlayer2;		///<	�v���C���[2���i�[�|�C���^
	const int		m_playerID;		///<	�N�����̃v���C���[ID�BGameScene�����������Ă���B

	bool			m_connectFlag;	///<	�ʐM���s���t���O

	int m_plyaerSelectType;	///< �I�������s���̎��

	int m_resultPlayer;	///<	�v���C���[���ɋN���Ă���퓬����
	int m_resultEnemy;	///<	�G���ɋN���Ă���퓬����
	int m_resultBattle;	///<	���҂̐틵����
	int m_stateTime;	///<	�e�X�e�[�g���ŕb�����J�E���g�����������ɁA�V�[�����Ōv�������b����n���ׂ̃����o

//	�X�e�[�g���ʂ̕`��I�u�W�F�N�g�̏��
private:
	BoardOfFrame	m_StageFrame;	///<	�X�e�[�W�����̃t���[���I�u�W�F�N�g
	BoardOfFrame	m_PlayerFrame[_PLAYER_NUM_];	///<	�v���C���[���̃t���[���I�u�W�F�N�g	
	GameLog			m_gameLog;		///<	�Q�[�����O�I�u�W�F�N�g
	GameLog			m_gameElapsed;	///<	�o�ߎ��ԏo�̓��O
	GameLog			m_gameConnectState;	///<	�ʐM��Ԃ̃��O

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
	*@brief	�f�X�g���N�^
	*/
	~StateManager() {
		CLASS_DELETE(m_pGameState);
	}

	/**
	*@brief	�X�e�[�g�̏�����
	*/
	void StateInit();
	
	/**
	*@brief	�X�e�[�g�̊�{���[�`������
	*/
	int StateCotrol();

	/**
	*@brief	�X�e�[�g�̊�{�`��
	*/
	void StateDraw();

	/**
	*@brief	�X�e�[�g��Ԃ̎擾
	*/
	_STATE_NUM_ GetState(){ return m_currentState; }

	/**
	*@brief	�e�X�e�[�g���̌o�ߎ��Ԃ̎擾
	*@details	CScene�N���X����m_sceneTime�����Ɏ擾
	*/
	int GetStateInTime(){ return m_stateTime; }

	/**
	*@brief	�e�X�e�[�g���̌o�ߎ��Ԃ̍X�V
	*@details	CScene�N���X����m_sceneTime�����ɍX�V
	*/
	void UpdateStatInTime( int _elapsed )
	{
		if( m_stateTime != _elapsed )
		{
			//	�o�ߎ��Ԃ����݂̎��Ԃƈ���Ă���΁A�X�e�[�g�����C���N�������g
			m_pGameState->SetElapsedTimeFromStateInstance( 
				m_pGameState->GetElapsedTimeFromStateInstance()+1);

#ifdef _DEBUG
			std::ostringstream s; 
			m_tempStr1 = "�o�ߎ��ԁF";
			s << (m_pGameState->GetElapsedTimeFromStateInstance()/10) <<"."<< (m_pGameState->GetElapsedTimeFromStateInstance()%10) ;
			m_tempStr2 = s.str();
			m_tempStr1 = m_tempStr1+m_tempStr2;
			//	�o�ߎ��ԃ��O���󂶂ᖳ��������
			if( !m_gameElapsed.m_logStream.empty() )
			{
				//	���g�i�b���\�����O�j������
				LogStream* temp = m_gameElapsed.m_logStream.back();
				delete temp;
				m_gameElapsed.m_logStream.pop_back();
			}
			//	�o�ߌ�̌��ݎ��_�ł̐V�����o�ߎ��Ԃ����O�ɒǉ�����B
			m_gameElapsed.AddStream(m_tempStr1.c_str());
#endif
		}
		m_stateTime=_elapsed;
	}

private:
	/**
	*@brief	�e�X�e�[�g�̃`�F�b�N
	*@details	�e�X�e�[�g��Control���Ă�ŁA���̌��ʂȂǂ���A
				�p�^�[���ύX�̕K�v�����邩�Ǘ��B
	*@return	�X�e�[�g	
	*@retval 1	�X�e�[�g�p�^�[���̕ύX�̕K�v����B*n
	*@retval 0	�ύX�̕K�v����
	*@retval -1	�Q�[���I���̏ꍇ
	*/
	int CheckState();

	/**
	*@brief	�X�e�[�g�p�^�[���̐؂�ւ�
	*param[in]	_stateType	
	*@return true�F�X�e�[�g�p�^�[���̕ύX�����B*n
			false�F�ύX���s
	*/
	bool ChangeState( _STATE_NUM_ _stateType );

	/**
	*@brief	�Ֆʂ̘g�̕\��
	*/
	void DrawStageFrame();

	/**
	*@brief	�Ֆʏ�̋�i�D�j�̕\��
	*/
	void DrawShipObject( const int _playerIndex );

	/**
	*@brief	�Ֆʂ̃}�X�ځi�u���b�N�j�̕\��
	*/
	void DrawStageBlock( const int _playerIndex );

	/**
	*@brief	�Q�[�����O�̕`��
	*/
	void DrawLog();

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