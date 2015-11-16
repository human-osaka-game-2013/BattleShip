/**
*@file	Selection.h
*@author	�T�c
*/

#ifndef _SELECTION_H_
#define _SELECTION_H_

#include "GameState.h"

#define _TAB_WIDTH_		128.f
#define _TAB_HEIGHT_	(float)_TAB_WIDTH_/3

class Selection : public GameState
{
private:
	bool m_tabSelectFlag;		///< �^�u��I�����Ă��邩
	bool m_areaSelectFlag;		///< �s���ʂ͈̔͂�I�����Ă��邩
	_SELECT_NUM_ m_plyaerSelectType;	///< �I�������s���̎��
	int m_arrayCheckResult;		///< �s���I�����͈̔̓`�F�b�N�̌���
	
	BoardOfFrame m_actionFrame;	///< �U���g
	BoardOfFrame m_searchFrame;	///< ���G�g
	BoardOfFrame m_moveFrame;	///< �ړ��g

	int(*m_tempArray)[_SHIP_ARRAY_INDEX_];	///<�ǂ̔z��f�[�^�Ƃ̃`�F�b�N���s�����̊i�[�p

public:
	/**
	*@brief	�R���X�g���N�^
	*@param	_type	���ݑI�����Ă���͂̎��
	*/
	Selection( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ): GameState( _type, _pGameLog ){
		m_tabSelectFlag = false;
		m_areaSelectFlag= false;
		m_arrayCheckResult = 0;
		m_plyaerSelectType = _SELECT_NONE_;
	}

	~Selection(){};

	/**
	*@brief	�퓬�s���I���ł̏�����
	*/
	bool Init();

	/**
	*@brief	�퓬�s���I���ł̃T�u���[�`������
	*/
	int Control();
	
	/**
	*@brief	�퓬�s���I���ł̕`��
	*/
	void Draw();
	
	/**
	*@brief	�퓬�s���I���ł̒ʐM�ҋ@����
	*/
	bool ComStandby();

	/**
	*@brief	�I�������s���̎�ނ��擾
	*@details	StateManager�ŃX�e�[�W�̃G�t�F�N�g�ȂǂɃX�e�[�g���ڍs�����ۂɁA
				�I�������s����������Ȃ���΃X�e�[�W��̉��o���o���Ȃ����߁A
				�I��������ނ̏�񂪕K�v�Ɣ��f���܂����B
	*/
	int GetSelectionType(){ return static_cast< int >(m_plyaerSelectType); }

private:

	/**
	*@brief	�^�u�̃N���b�N�̔���
	*/
	bool TabCheck();

	/**
	*@brief	�s���I��ʂ̔z����Z�b�g
	*@details	��Ƀ`�F�b�N����z��f�[�^�̓^�u��I�������ۂɂǂ���g�������܂��Ă��邽�߁A
				�����o�ɉ��ۑ�����ׁA�����ň�x�����z��f�[�^���Z�b�g����B
	*@todo	�����Ⴄ�s����I������ꍇ�ɂ̓t���O�̊Ǘ��̊֌W���炱���̓^�u���đI�����ꂽ�ۂɍēx�ʂ�\��B
	*/
	bool SetTypeArray();

	/**
	*@brief	�s���I�����͈̔̓`�F�b�N
	*@details	���̊֐��ł͑I�������s���ʂɍ��W���w�肷��Ƃ��̕���⏈�����s��
	*/
	int SelectArrayCheck();

	///**
	//*@brief	�X�e�[�W�͈̔̓`�F�b�N
	//*@details	SelectArrayCheck�֐��ɏ����ƍ��ȏ�Ƀl�X�g���[���Ȃ�Ǝv�������߁A�R�`���ɏ����𕪂��鎖�ɂ���B@n
	//			
	//*@param[in]	_id		�`�F�b�N����X�e�[�W�̃v���C���[ID
	//*@param[in]	_column	�`�F�b�N����s
	//*@param[in]	_line	�`�F�b�N�����
	//*@param[in]	_array	�Z�b�g�������z��f�[�^
	//*/
	//int StageCheck( const int& _id, const int& _column, const int& _line, const int(*_array)[_SHIP_ARRAY_INDEX_]);

	/**
	*@brief	�^�u�̏������Z�b�g
	*@details	��Ƀ^�u���̃J���[�l�����Z�b�g
	*/
	void ResetTabFrame();

};

#endif