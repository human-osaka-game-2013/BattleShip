/**
*@file	ShipObject.h
*@author	�T�c
*/

#ifndef _SHIPOBJECT_H_
#define _SHIPOBJECT_H_

#include "gameObject.h"
#include "read_file.h"
#include "BoardOfFrame.h"
#include "StageDefineList.h"
#include "DrawManager.h"

#define _SHIP_ARRAY_INDEX_	5	///<	��̔z��w��
#define _SHIP_INIT_DIR_	CGameObject::CH_UP

/**
*@brief	��̊��N���X
*/
class ShipObject:public CGameObject, public ReadFile
{
public:
	/**
	*@brief	��͎̊�ޗ�
	*/
	enum _SHIP_TYPE_NUM_
	{
		TYPE_NONE=-1,
		TYPE_AIRCARRIER,
		TYPE_BATTLESHIP,
		TYPE_CRUISER,
		TYPE_DESTROYER,
		TYPE_SUBMARINE,
		TYPE_MAX,
	};

	/**
	*@brief	��̔z����
	*/
	enum _SHIP_ARRAY_TYPE_
	{
		ARRAY_TYPE_SHIP,
		ARRAY_TYPE_ACTION,
		ARRAY_TYPE_SEARCH,
		ARRAY_TYPE_MOVE,
		ARRAY_TYPE_MAX,
	};

	/**
	*@brief	��̃e�[�u�������
	*/
	enum _SHIP_TABLE_NUM_
	{
		TABLE_SHIP,
		TABLE_ACTION = _SHIP_ARRAY_INDEX_,
		TABLE_SEARCH = TABLE_ACTION+_SHIP_ARRAY_INDEX_,
		TABLE_MOVE = TABLE_SEARCH+_SHIP_ARRAY_INDEX_,
		TABLE_MAX = TABLE_MOVE+_SHIP_ARRAY_INDEX_
	};

private:
	int m_userID;
	int m_posColumn;
	int m_posLine;

public:
	int m_shipArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̎��̔z��
	CUSTOMVERTEX	m_vertex[4];	///<	��̋�`�������̃��[�J�����W

	int m_actionArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̍U���͈͔z��
	int m_searchArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̍��G�͈͔z��
	int m_moveArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	��̈ړ��͈͔z��
	
public:
	/**
	*@brief	�R���X�g���N�^
	*@details	��z��̏�������CGameObject�̃R���X�g���N�^���Ăяo��
	*/
	ShipObject::ShipObject() : CGameObject(){
		for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++ ){
			for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++ )	{
				m_shipArray[iColumn][iLine]=0;
				m_actionArray[iColumn][iLine]=0;
				m_searchArray[iColumn][iLine]=0;
				m_moveArray[iColumn][iLine]=0;

			}
		}
		SetDirection( _SHIP_INIT_DIR_ );
	}

	/**
	*@brief	������
	*/
	virtual void Init( int _userID ) = 0;

	void Control(){};

	void Draw(){};

	/**
	*@brief	�ǂݎ�����f�[�^���e�[�u���ɃZ�b�g
	*@details	��f�[�^��
	*/
	void SetTable( char* _p, int _iColumn, int _iLine);

	/**
	*@brief	���]����
	*@param[in]	_array	��]������z��
	*@param[in] _rotType	��]����������Btrue�F�E��], false�F����]�B
	*/
	bool RotationShip( int _arrayType, bool _rotType );

	/**
	*@brief	���_���̏�����
	*@details	��̕`���ShipObject���̔z�u���𗊂�ɂ��邽�߁A
				�ʏ�̕`��i���S�_or�����̋�`�����`��j�ł͏o���Ȃ��̂�
				��Ƃɋ�`�̃��[�J�����W������Ă��K�v������B
	*/
	void InitVertex( _SHIP_TYPE_NUM_ _shipType );

	/**
	*@brief	�������
	*/
	void  Free();

public:
	/**
	*@brief	��̎�����ID�擾
	*/
	int GetUserID(){ return m_userID; }	

	/**
	*@brief	�X�e�[�W��ł̋�̒��S�ʒu�̃Z�b�g
	*/
	void SetArrayPos( int _column, int _line ){ 
		m_posColumn = _column;
		m_posLine	= _line;
	}

	/**
	*@brief	�X�e�[�W��ł̋�̒��S�ʒu�̃Z�b�g
	*/
	void GetArrayPos( int& _column, int& _line ){ 
		_column	= m_posColumn;
		_line	= m_posLine;
	}

};


#endif