/**
*@file	BattleShip.h
*@author	亀田
*/

#ifndef _BATTLESHIP_H_
#define _BATTLESHIP_H_

#include "ShipObject.h"

class BattleShip : public ShipObject
{

public:
	/**
	*@brief コンストラクタ
	*/
	BattleShip::BattleShip( int _userID ):ShipObject( _userID )
	{

	}

	void Init();

};


#endif