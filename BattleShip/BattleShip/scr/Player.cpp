#include "Player.h"

void Player::Init( int _userID )
{
	int iCount = 0;
	while( iCount < ShipObject::TYPE_MAX )
	{
		//	クラス別に艦種クラスを生成
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
		m_pShip[iCount]->Init( _userID );	///<	初期化
		m_pShip[iCount]->InitVertex( (ShipObject::_SHIP_TYPE_NUM_)iCount );

		iCount++;
	}
}

ShipObject* Player::GetShip( ShipObject::_SHIP_TYPE_NUM_ _shipType )
{
	if( _shipType < ShipObject::TYPE_MAX && _shipType > ShipObject::TYPE_NONE )
		return m_pShip[_shipType];
	return NULL;	
}

bool Player::Free()
{
	for( int iCount = 0; iCount < m_pShip.size(); iCount++ ){
		delete m_pShip[iCount];
	}
	return true;
}