#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <list>
#include "ShipObject.h"


class Player
{
private:
	int m_userID;
	std::list<ShipObject*> m_pShip;

public:
	/**
	*@brief	コンストラクタ
	*/
	Player( int _userID ): m_userID( _userID )
	{
		Init( m_userID );
	}

	/**
	*@brief	初期化
	*/
	void Init( int _userID );

	/**
	*@brief	駒情報取得
	*/
	ShipObject* GetShip( ShipObject::_SHIP_TYPE_NUM_ _shipType );
	
	/**
	*@brief	ユーザーID取得
	*/
	int GetUserID(){ return m_userID; }
};

#endif 
