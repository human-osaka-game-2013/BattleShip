/**
*@file	StageObject.h
*@author	�T�c
*/

#ifndef _STAGEOBJECT_H_
#define _STAGEOBJECT_H_

#include "StageDefineList.h"
#include "ShipObject.h"
#include "BoardOfFrame.h"

#define _PLAYER_NUM_ 2

/**
*@brief	�X�e�[�W�I�u�W�F�N�g�N���X
*@details	�Q�[�����̃X�e�[�W���Ǘ�����N���X
*/
class StageObject : public CGameObject
{
public:
	/*
	*@brief	�X�e�[�W�̔z��f�[�^�̎�ނ̗񋓁i�I���Ȃǁj
	*@details	�Ֆʂ̃}�X���I������Ă��邩��A�s���\�͈͂Ȃǂ̎�ނ̗񋓁B
				���G��U���ʒu�̏���������ŊǗ�����B
	*/
	enum _ARRAY_DATA_TYPE_SELECT_
	{
		_SELECT_NOMAL_,	///<�I������Ă��Ȃ�
		_SELECT_TRUE_,	///<�I������Ă���
		_SELECT_FALSE_,	///<�I���o���Ȃ�
		_SEARCH_NOMAL_,	///<���G������͈�
		_SEARCH_ALL_,	///<���G������͈́i�S�Ă̊́j
		_ACTION_NOMAL_,	///<�U������͈�
		_ACTION_ALL_	///<�U������͈́i�S�Ă̊́j
	
	};
	
	/*
	*@brief	�X�e�[�W�̔z��f�[�^�̎�ނ̗񋓁i���Q�󋵁j
	*@details	�Ֆʂ̃}�X�̋���邩�ǂ����́A�X�e�[�W�ł�2���ڂ�0�̎��_�ŋ�͑��݂��Ȃ��͂��ł��B
	*/
	enum _ARRAY_DATA_TYPE_CONDITION_
	{
		_CONDITION_NONE_,	///<�����
		_CONDITION_NOMAL_,	///<�����
		_CONDITION_DAMAGE_	///<��������Ă���
	};


public:
	int				m_stageArray[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<�X�e�[�W��̏��
	BoardOfFrame	m_stageBlock[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<�X�e�[�W�u���b�N�̍��W

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	StageObject() : CGameObject(){
			
	}

	bool Init();

	void Control(){};

	void Draw(){};

	/**
	*@brief	�X�e�[�W�u���b�N�̃`�F�b�N(��Ƃ̔���)
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_ship	�w�肵���u���b�N���S�ɔ�r�����̃|�C���^
	*@param[in] _arrayType	�`�F�b�N����z��̃^�C�v�iShipObject::_SHIP_ARRAY_TYPE_����j
	*@param[in]	_shipNum	�������g�̋�ɐڐG���Ă����ꍇ
	*@return	0�F�X�e�[�W��̎w��͈͂ƃu���b�N�̎��̂��ڐG���Ă��Ȃ��ꍇ�B@n
				1�F�X�e�[�W�O�Ƀu���b�N�̎��̂��������ꍇ�B@n
				2�F�w�肵���u���b�N�͈̔͂ɂ��łɃX�e�[�W��ŉ��������݂��Ă����ꍇ�B@n
				-1�F��L�ȊO�̎������������ꍇ�B
	*/
	int CheckStageBlock( int _player, const int _column, const int _line, ShipObject* _ship,  
							ShipObject::_SHIP_ARRAY_TYPE_ _arrayType, const int _shipNum );
	
	/**
	*@brief	����X�e�[�W��͈̔͂Ɖ�ʏ�̍��WXY�Ƃ̔���
	*@details	��ɉ�ʏ�̍��W���w���Ă���u���b�N�̒��g�𒲂ׂ�B@n
	*@todo		����͈ړ��\�͈͂��w���Ă���ꍇ�𒲂ׂ邽�߂̊֐��Ƃ��č��܂����B
	*@param[out] _column	�w���Ă�����W�̍s�̒l
	*@param[out] _line		�w���Ă�����W�̗�̒l	
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_x		��ʏ�̒��ׂ������WX
	*@param[in]	_y		��ʏ�̒��ׂ������WY
	*@param[in]	_ship	�͈͂̒��S�ƂȂ��I�u�W�F�N�g�̃|�C���^
	*@param[in] _arrayType	�`�F�b�N����z��̃^�C�v�iShipObject::_SHIP_ARRAY_TYPE_����j
	*@return	0�F�I������Ă��Ȃ��u���b�N���w���Ă���ꍇ�B@n
				1�F�I���\�u���b�N���w���Ă���ꍇ�B@n
				2�F�I��s�\�u���b�N���w���Ă���ꍇ�B@n
				-1�F��L�ȊO�̎������������ꍇ�i�܂��͂��������u���b�N�ɐڐG���Ă��Ȃ��ꍇ�j�B
	*/
	int CheckRangeOnStage( int& _column, int& _line, 
							int _player, const float _x, const float _y, ShipObject* _ship, ShipObject::_SHIP_ARRAY_TYPE_ _arrayType );

	/**
	*@brief		�X�e�[�W�u���b�N�Ǝw��͈͂̃Z�b�g
	*@details	��S�ɔz��͈͂��d�˂��킹�āA���̎w��͈͂ƃX�e�[�W�Ƃ̔���ɉ�����
				�͈͏����X�e�[�W�ɃZ�b�g����B@n
	*@todo		���̊֐��͈ړ��͈͂̃`�F�b�N���s���ׂɍ�������́B�o���邱�ƂȂ炷�łɂ���֐��ő�p�������B
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_ship	�z��͈͂̒��S�Ƃ���ׂ̋�̃|�C���^
	*@param[in] _tempArray	�z��͈�
	*@param[in]	_shipNum	�������g�̋�ɐڐG���Ă����ꍇ��������Ȃ��悤�ɂ���
	*@return	true�F�͈̓Z�b�g������
				false�F�͈̓Z�b�g�����s�����ꍇ�B
	*/
	bool SetStageToRange( int _player, ShipObject* _ship, 
		const int(*_array)[_SHIP_ARRAY_INDEX_], const int _shipNum );

	/**
	*@brief	�X�e�[�W�u���b�N�֋�����Z�b�g
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_ship	�w�肵���u���b�N���S�ɃZ�b�g�����̃|�C���^
	*@return	false�F���炩�̌����ŃZ�b�g�����s�B@n
				true�F�����ɏ����Z�b�g�����B
	*/
	bool SetShip( int _player, const int _column, const int _line, ShipObject* _ship );

	/**
	*@brief	�X�e�[�W�u���b�N�֎w��͈͏����Z�b�g�i1�}�X�̂݁j
	*@details	1�}�X�̂݃X�e�[�W�u���b�N��3���ڂɏ��i_ARRAY_DATA_TYPE_SELECT_�j���Z�b�g����
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_setType	�͈͏������̒l�ŃZ�b�g���邩
	*@return	false�F���炩�̌����ŃZ�b�g�����s�B@n
				true�F�����ɏ����Z�b�g�����B
	*/
	bool SetRange( int _player, const int _column, const int _line, const _ARRAY_DATA_TYPE_SELECT_ _setType );

	/**
	*@brief	�X�e�[�W�u���b�N�֎w��͈͏����Z�b�g
	*@details	_array�͈̔͂Ńf�[�^��_selectNum�̓��e�ɉ����ăX�e�[�W�ɃZ�b�g�B
				���݂͍��Gor�U���̏����Z�b�g�����p
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_array	�w�肵���u���b�N���S�ɃZ�b�g����z����
	*@param[in]	_selectNum	�͈͏������̒l�ŃZ�b�g���邩
	*@return	false�F���炩�̌����ŃZ�b�g�����s�B@n
				true�F�����ɏ����Z�b�g�����B
	*/
	bool SetRange( int _player, const int _column, const int _line, 
					const int(*_array)[_SHIP_ARRAY_INDEX_], const int _selectNum );

	/**
	*@brief	�X�e�[�W�u���b�N�֎w��͈͏����Z�b�g
	*@details	_array�͈̔͂Ńf�[�^��_setType��3���ڂɃX�e�[�W�ɃZ�b�g
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_array	�w�肵���u���b�N���S�ɃZ�b�g����z����
	*@param[in]	_setType	�͈͏������̒l�ŃZ�b�g���邩
	*@return	false�F���炩�̌����ŃZ�b�g�����s�B@n
				true�F�����ɏ����Z�b�g�����B
	*/
	bool SetRange( int _player, const int _column, const int _line, const int(*_array)[_SHIP_ARRAY_INDEX_], 
					const _ARRAY_DATA_TYPE_SELECT_ _setType );


	/**
	*@brief	�X�e�[�W�u���b�N�֋�����Ĕz�u
	*@param[in]	_player	�v���C���[��ID
	*@param[in]	_column	�s
	*@param[in]	_line	��
	*@param[in]	_ship	�w�肵���u���b�N���S�ɃZ�b�g�����̃|�C���^
	*@param[in]	_shipNum	�������g�̋�ɐڐG���Ă����ꍇ��������Ȃ��悤�ɂ���
	*@return	false�F���炩�̌����ŃZ�b�g�����s�B@n
				true�F�����ɏ����Z�b�g�����B
	*/
	bool RelocationShip( int _player, const int _column, const int _line, ShipObject* _ship, const int _shipNum );

	/**
	*@brief	�X�e�[�W�u���b�N�̑I����Ԃ�����
	*/
	void ResetSelect();

	/**
	*@brief	�������
	*/
	void  Free();
};

#endif