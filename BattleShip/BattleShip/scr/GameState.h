/**
*@file	GameState.h
*@author	�T�c
*/

#ifndef	_GAMESTATE_H_
#define _GAMESTATE_H_

class GameState
{
public:
	/**
	*@brief	�Q�[�����ł̃X�e�[�g�p�^�[���̗񋓁B
	*@details	��ɃX�e�[�g�؂�ւ����Ɏg�p
	*/
	enum	_STATE_NUM_
	{
		STATE_NONE,
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
	};

private:
	_STATE_NUM_ m_stateID;	///<	���g�̃X�e�[�g��ID	

public:
	/**
	*@brief	�X�e�[�g�p�^�[�����ł̏�����
	*/
	virtual bool Init() = 0;

	/**
	*@brief	�X�e�[�g�p�^�[�����ł̃T�u���[�`������
	*/
	virtual bool Control() = 0;

	/**
	*@brief	�X�e�[�g�p�^�[�����ł̕`��
	*/
	virtual void Draw() = 0;

	/**
	*@brief	�X�e�[�g�p�^�[�����ł̒ʐM���̃T�u���[�`������
	*/
	virtual void ComStandby() = 0;

	/**
	*@brief	�X�e�[�g��ID�擾
	*/
	_STATE_NUM_ GetState(){ return m_stateID; }

};

#endif