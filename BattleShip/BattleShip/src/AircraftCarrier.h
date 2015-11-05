/**
*@file	AircraftCarrier.h
*@author	亀田
*/

#ifndef _AIRCRAFTCARRIER_H_
#define _AIRCRAFTCARRIER_H_

#include "ShipObject.h"

class AircraftCarrier : public ShipObject
{
	

public:
	/**
	*@brief コンストラクタ
	*/
	AircraftCarrier::AircraftCarrier( int _userID ):ShipObject( _userID )
	{

	}
	
	/**
	*@brief	初期化
	*@pragma[in]	_userID	
	*/
	void Init();


};


#endif