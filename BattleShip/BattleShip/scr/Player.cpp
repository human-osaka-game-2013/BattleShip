#include "Player.h"
#include "StageObject.h"

void Player::Init( int _userID )
{
	int iCount = 0;
	while( iCount < ShipObject::TYPE_MAX )
	{
		//	�N���X�ʂɊ͎�N���X�𐶐�
		switch( iCount )
		{
		case ShipObject::TYPE_AIRCARRIER:
			m_pShip.push_back( new AircraftCarrier() );
			break;
		case ShipObject::TYPE_BATTLESHIP:
			m_pShip.push_back( new BattleShip() );
			break;
		case ShipObject::TYPE_CRUISER:
			m_pShip.push_back( new Cruiser() );
			break;
		case ShipObject::TYPE_DESTROYER:
			m_pShip.push_back( new Destroyer() );
			break;
		case ShipObject::TYPE_SUBMARINE:
			m_pShip.push_back( new Submarine() );
			break;
		}
		m_pShip[iCount]->Init( _userID );	///<	������
		m_pShip[iCount]->InitVertex( (ShipObject::_SHIP_TYPE_NUM_)iCount );

		iCount++;
	}
}

ShipObject* Player::GetShip( const ShipObject::_SHIP_TYPE_NUM_ _shipType )
{
	if( _shipType < ShipObject::TYPE_MAX && _shipType > ShipObject::TYPE_NONE )
		return m_pShip[_shipType];
	return NULL;	
}

bool Player::DamageControl( const int _column, const int _line, const ShipObject::_SHIP_TYPE_NUM_ _shipType )
{
	if( _shipType >= ShipObject::TYPE_MAX || _shipType <= ShipObject::TYPE_NONE )
		return false;

	int iLocalColumn = _column -(m_pShip[_shipType]->GetArrayColumn() - 2);
	int iLocalLine = _line -(m_pShip[_shipType]->GetArrayLine() - 2);

	if( (m_pShip[_shipType]->m_shipArray[iLocalColumn][iLocalLine]/10)%10 != StageObject::_CONDITION_NOMAL_ )///<�������Ă��Ȃ��}�X����Ȃ����
	{
		return false;
	}
	else	///<	�������Ă��Ȃ��}�X�i_CONDITION_NOMAL_�j�������̂�
	{
		m_pShip[_shipType]->m_shipArray[iLocalColumn][iLocalLine] += 10;	///<	�������̌���_CONDITION_DAMAGE_�Ɉ����グ��
	}

	return true;
}


bool Player::Free()
{
	for( unsigned int iCount = 0; iCount < m_pShip.size(); iCount++ ){
		delete m_pShip[iCount];
	}
	return true;
}