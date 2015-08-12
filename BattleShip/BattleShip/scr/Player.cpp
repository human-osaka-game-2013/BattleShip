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
	}
}