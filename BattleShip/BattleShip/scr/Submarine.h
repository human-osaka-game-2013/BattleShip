/**
*@file	Submarine.h
*@author	亀田
*/

#ifndef _SUBMARINE_H_
#define _SUBMARINE_H_

#include "ShipObject.h"

class Submarine : public ShipObject
{

public:
	/**
	*@brief コンストラクタ
	*/
	Submarine::Submarine():ShipObject()
	{

	}

	void Init( int _userID );

};

#endif