/**
*@file	Cruiser.h
*@author	亀田
*/

#ifndef _CRUISER_H_
#define _CRUISER_H_

#include "ShipObject.h"

class Cruiser : public ShipObject
{

public:
	/**
	*@brief コンストラクタ
	*/
	Cruiser::Cruiser():ShipObject()
	{

	}

	void Init( int _userID );

};


#endif