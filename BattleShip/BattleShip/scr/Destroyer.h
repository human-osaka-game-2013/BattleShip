/**
*@file	Destroyer.h
*@author	亀田
*/

#ifndef _DESTROYER_H_
#define _DESTROYER_H_

#include "ShipObject.h"

class Destroyer : public ShipObject
{

public:
	/**
	*@brief コンストラクタ
	*/
	Destroyer::Destroyer():ShipObject()
	{

	}

	void Init( int _userID );

};


#endif