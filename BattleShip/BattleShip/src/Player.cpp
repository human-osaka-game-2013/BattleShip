#include "Player.h"
#include "StageObject.h"

#include "DebugNew.h"

void Player::Init( int _userID )
{
	int iCount = 0;
	while( iCount < ShipObject::TYPE_MAX )
	{
		//	クラス別に艦種クラスを生成
		switch( iCount )
		{
		case ShipObject::TYPE_AIRCARRIER:
			m_pShip.push_back( new AircraftCarrier( _userID ) );
			break;
		case ShipObject::TYPE_BATTLESHIP:
			m_pShip.push_back( new BattleShip( _userID ) );
			break;
		case ShipObject::TYPE_CRUISER:
			m_pShip.push_back( new Cruiser( _userID ) );
			break;
		case ShipObject::TYPE_DESTROYER:
			m_pShip.push_back( new Destroyer( _userID ) );
			break;
		case ShipObject::TYPE_SUBMARINE:
			m_pShip.push_back( new Submarine( _userID ) );
			break;
		}
		m_pShip[iCount]->Init();	///<	初期化
		m_pShip[iCount]->InitVertex( (ShipObject::_SHIP_TYPE_NUM_)iCount );

		iCount++;
	}
}

ShipObject* Player::GetShip( const ShipObject::_SHIP_TYPE_NUM_ _shipType )
{
	if ( _shipType < ShipObject::TYPE_MAX && _shipType > ShipObject::TYPE_NONE )
		return m_pShip[_shipType];
	return NULL;	
}

bool Player::DamageControl( const int _column, const int _line, const ShipObject::_SHIP_TYPE_NUM_ _shipType )
{
	if ( _shipType >= ShipObject::TYPE_MAX || _shipType <= ShipObject::TYPE_NONE )
		return false;

	int iLocalColumn = _column -(m_pShip[_shipType]->GetArrayColumn() - 2);
	int iLocalLine = _line -(m_pShip[_shipType]->GetArrayLine() - 2);

	if ( StageObject::ConditionOfData(m_pShip[_shipType]->m_shipArray[iLocalColumn][iLocalLine]) == StageObject::_CONDITION_DAMAGE_ )///<損傷していないマスじゃなければ
	{
		return false;
	}
	else	///<	損傷していないマス（_CONDITION_NOMAL_）だったので
	{
		m_pShip[_shipType]->m_shipArray[iLocalColumn][iLocalLine] += 10;	///<	損傷情報の桁を_CONDITION_DAMAGE_に引き上げる
	}
	//	轟沈判定
	CheckDestroy( _shipType );
	
	return true;
}

bool Player::CheckDestroy( const ShipObject::_SHIP_TYPE_NUM_ _shipType )
{
	if ( m_pShip[_shipType]->GetDeadFlag() )
		return true;
	int hitCount = 0;

	hitCount = CheckHitCount( _shipType );
	
	//	各艦のマス数に応じてカウントと照らしあわせて判定
	switch( _shipType )
	{
	case ShipObject::TYPE_AIRCARRIER:
		if ( hitCount >= 5 )
			m_pShip[_shipType]->SetDeadFlag(true);
		break;
	case ShipObject::TYPE_BATTLESHIP:
		if ( hitCount >= 4 )
			m_pShip[_shipType]->SetDeadFlag(true);
		break;
	case ShipObject::TYPE_CRUISER:
		if ( hitCount >= 3 )
			m_pShip[_shipType]->SetDeadFlag(true);
		break;
	case ShipObject::TYPE_DESTROYER:
	case ShipObject::TYPE_SUBMARINE:
		if ( hitCount >= 2 )
			m_pShip[_shipType]->SetDeadFlag(true);
		break;
	}

	if ( m_pShip[_shipType]->GetDeadFlag() )
		return true;

	return false;
}

int	Player::CheckHitCount( const ShipObject::_SHIP_TYPE_NUM_ _shipType )
{
	int hitCount = 0;
	//	轟沈判定を取る
	for ( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++)
	{
		for ( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++)
		{
			if ( StageObject::ConditionOfData(m_pShip[_shipType]->m_shipArray[iColumn][iLine]) == 
				StageObject::_CONDITION_DAMAGE_)
			{
				hitCount++;
			}
		}
	}
	return hitCount;
}