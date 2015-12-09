

#ifndef	_KEY_H_
#define _KEY_H_

#include "Input.h"
#include "device.h"

/**
*@brief	�g�p����L�[�̎��
*@details	KeyCheck�Ƌ��Ɏg���L�[��������΃R�R�Ɏ�ނ�ǉ����Ă���
*/ 
enum eKEYKIND
{
	/*
		���l�̓��͂Ȃǁi�����̕��т͕ς��Ȃ��ŉ������B�j
	*/
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	PERIOD,

	/*
		���̑�
	*/	
	ENTER,

	KEYMAX
};

/**
*@brief	�L�[�̏�ԊǗ��N���X
*/
class CKey
{
private:
	int m_key[KEYMAX];		///< �L�[�̏�Ԃ���ޕʂɊi�[����ϐ�
	bool m_preKey[KEYMAX];	///< �L�[�̎�ޕʂɉ�����Ă��邩�̃t���O
	IDirectInputDevice8* const	m_pKeyDevice;	///<	�L�[�f�o�C�X�I�u�W�F�N�g�̃|�C���^

public:
	/**
	*@brief	�R���X�g���N�^
	*@param[in]
	*/
	CKey( IDirectInputDevice8* const _pKeyDevice);

public:
	
	/**
	*@brief	�����̃L�[�̏�Ԃ��܂Ƃ߂ă`�F�b�N
	*@details	KeyCheck�֐����܂Ƃ߂ČĂяo��
	*/
	void AllKeyCheck ();
	
	/**
	*@brief	�L�[��ԃ`�F�b�N
	*@param[in]	_st		�L�[�̎��
	*@param[in]	_keySt	�L�[�̏��
	*/
	bool StCheck(int _st, int _keySt);

	/**
	*@brief	�L�[��ԂƑS�ăL�[�̃`�F�b�N
	*@details	�����̃L�[��ԂɂȂ��Ă���L�[��z��f�[�^����T���A
				��ԍŏ��ɍ��v�����L�[��ID��Ԃ��B�Y�����Ȃ������ꍇ��-1��Ԃ�
	*/
	int CheckStateToAllKey( int _keySt );
private:
	/**
	*@brief	�L�[��ԃ`�F�b�N
	*@param[in]	_dik	�L�[�̒萔
	*@param[in]	_st		�L�[�̎��
	*/
	void KeyCheck ( int _dik, int _st );

};
#endif