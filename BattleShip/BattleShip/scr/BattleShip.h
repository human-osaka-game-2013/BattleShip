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
	BattleShip::BattleShip():ShipObject()
	{

	}

	void Init( int _userID );

};


#endif