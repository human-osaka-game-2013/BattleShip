#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "ShipObject.h"
#include "AircraftCarrier.h"
#include "BattleShip.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Submarine.h"

class Player
{
private:
	int m_userID;
	std::vector<ShipObject*> m_pShip;

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	Player( int _userID ): m_userID( _userID )
	{
		Init( _userID );
	}
	/**
	*@brief	�������
	*/
	bool Free();

	/**
	*@brief	������
	*/
	void Init( int _userID );

	/**
	*@brief	����擾
	*/
	ShipObject* GetShip( const ShipObject::_SHIP_TYPE_NUM_ _shipType );
	
	/**
	*@brief	���[�U�[ID�擾
	*/
	int GetUserID(){ return m_userID; }

	/**
	*@brief	�v���C���[�̎�����̑��Q����
	*@warning	���̊֐��͌����_��Result�N���X���ŃX�e�[�W������ɍs����W��n���Ă���̂ŁA
				��̎��̂���Ȃ��s����Wor�֌W�̂Ȃ���̎�ޏ���n���Ȃ��l�ɁB
	*@param[in]	_column	�s���W
	*@param[in]	_line	����W
	*@param[in]	_shipType	�ǂ̋�̑��Q���������邩�ɕK�v
	*@return	���Q�����̌���
	*@retval	true	���̃}�X�ɒu���Ă�����������
	*@retval	false	���łɂ��̃}�X���������Ă����ꍇ(�܂��̓G���[�̏ꍇ)
	*/
	bool DamageControl( const int _column, const int _line, const ShipObject::_SHIP_TYPE_NUM_ _shipType );

	/**
	*@brief	��������
	*@param[in]	_shipType	�ǂ̋�̑��Q���������邩�ɕK�v
	*@return	��������̌���
	*@retval	true	���łɍ�������
	*@retval	false	�܂��������Ă��Ȃ�
	*/
	bool CheckDestroy( const ShipObject::_SHIP_TYPE_NUM_ _shipType );

};

#endif 
