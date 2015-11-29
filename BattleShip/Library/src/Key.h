

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
	COMMA,
	
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
	*@brief	�L�[��ԃ`�F�b�N
	*@param[in]	_dik	�L�[�̒萔
	*@param[in]	_st		�L�[�̎��
	*/
	void KeyCheck ( int _dik, int _st );

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

};
#endif