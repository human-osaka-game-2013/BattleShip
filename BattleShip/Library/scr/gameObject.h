/**
*@file	gameObject.h
*@author	�T�c
*/
//	���d�C���N���[�h�h�~
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

/**
*@brief	�Q�[���I�u�W�F�N�g�N���X
*@details	�Q�[�����Ŏg���I�u�W�F�N�g��
*/
class CGameObject
{
public:	
	/**
	*@brief	�I�u�W�F�N�g�̌���
	*/
	enum CHARADIRECTION {
		CH_NONE = -1,
		CH_LEFT,
		CH_UP,
		CH_RIGHT,
		CH_DOWN,
		CH_DIRECTION_MAX,
		
	};

	/**
	*@brief	�I�u�W�F�N�g�̏��
	*/
	enum CHARASTATE {
		STATE_NONE = -1,
		STATE_WAIT,		
		STATE_WALK,
		STATE_JUMP,	
		STATE_DOWN,
		STATE_DAMAGE,	
		STATE_ATTACK,
		CH_STATE_MAX,
	};

private:	//	�����o�ϐ�
	CHARADIRECTION	m_Dir;		///<	����
	CHARASTATE		m_State;	///<	���

	float m_posX;		///<	X���W
	float m_posY;		///<	Y���W
	float m_posZ;		///<	Z���W

	int	m_id;	///<	���ʔԍ��i�I�u�W�F�N�g�ŗL��ID)

	bool m_deadFlag;	///<	�\���ȂǃI�u�W�F�N�g�����ݏo���邩�̔��f�Ɏg��

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	CGameObject();	

	/**
	*@brief	�������
	*/
	virtual void  Free() = 0;

public:	
	/**
	*@brief	�ړ��̉��z�֐�
	*/
	virtual void Control () = 0;

	/**
	*@brief	�`��̉��z�֐�
	*/
	virtual void Draw() = 0;
	
	/**
	*@brief	gameObject�I�u�W�F�N�g�̊�_���͈͓��ɓ����Ă��邩�̓����蔻��
	*@details	
	*@param[in]	_left	������͈͂̍ō��l
	*@param[in]	_top	������͈͂̍ŏ�l
	*@param[in]	_right	������͈͂̍ŉE�l
	*@param[in]	_bottom	������͈͂̍ŉ��l
	*/
	bool HitCheck( float _left, float _top, float _right, float _bottom );

public:	// �A�N�Z�b�T
	/*
	*@brief	�������Z�b�g
	*@param[in]	_dir	�����i�Eor���j
	*/
	void SetDirection ( CHARADIRECTION _dir ){ m_Dir = _dir; }
	/*
	*@brief	��Ԃ��Z�b�g
	*@param[in]	_state	��ԁi�ҋ@�A�U���Ȃǁj
	*/
	void SetState ( CHARASTATE _state ){ m_State = _state; }
	/*
	*@brief	���W�iX,Y,Z�j���Z�b�g
	*@param[in]	_x
	*@param[in]	_y
	*@param[in]	_z
	*/
	void SetPosition ( float _x, float _y, float _z );

	/*
	*@brief	���W�iX�j���Z�b�g
	*@param[in]	_x
	*/
	void SetPositionX ( float _x ){	m_posX = _x;	}
	/*
	*@brief	���W�iY�j���Z�b�g
	*@param[in]	_y
	*/
	void SetPositionY ( float _y ){	m_posY = _y;	}
	/*
	*@brief	���W�iZ�j���Z�b�g
	*@param[in]	_z
	*/
	void SetPositionZ ( float _z ){	m_posZ = _z;	}
	/*
	*@brief	���ʔԍ����Z�b�g
	*@param	_id	ID�iint�^�j
	*/
	void SetID( int _id ){	m_id = _id;	}
	/*
	*@brief	DeadFlag���Z�b�g
	*@param	_dFlag	ID�ibool�^�j
	*/
	void SetDeadFlag( bool _dFlag ){	m_deadFlag = _dFlag;	}
	/*
	*@brief	�����̎擾
	*@return	m_Dir	�����i�Eor���j
	*/
	CHARADIRECTION GetDirection (){	return m_Dir;	}
	/*
	*@brief	��Ԃ̎擾
	*@return	m_State	��ԁi�ҋ@�A�U���Ȃǁj
	*/
	CHARASTATE GetState (){	return m_State;	}
	/*
	*@brief	���W���iX,Y�j�̎擾
	*@param[in]	p_x	���WX
	*@param[in]	p_y	���WY
	*/
	void GetPosition ( float* p_x, float* p_y );
	/*
	*@brief	���W���iX�j�̎擾
	*@return	m_posX	���W���iX�j
	*/
	float GetPositionX (){ return m_posX; }
	/*
	*@brief	���W���iY�j�̎擾
	*@return	m_posY	���W���iY�j
	*/
	float GetPositionY (){ return m_posY; }
	/*
	*@brief	���W���iZ�j�̎擾
	*@return	m_posZ	���W���iZ�j
	*/
	float GetPositionZ (){ return m_posZ; }
	/*
	*@brief	���ʔԍ����擾
	*@return	���ʔԍ��iint�^�j
	*/
	int GetID(){ return m_id; }
	/*
	*@brief	���ʔԍ����擾
	*@return	���ʔԍ��ibool�^�j
	*/
	bool GetDeadFlag(){	return m_deadFlag;	}
};

#endif