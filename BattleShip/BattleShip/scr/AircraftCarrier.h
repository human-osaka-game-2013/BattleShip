/**
*@file	AircraftCarrier.h
*@author	�T�c
*/

#ifndef _AIRCRAFTCARRIER_H_
#define _AIRCRAFTCARRIER_H_

#include "ShipObject.h"

class AircraftCarrier : public ShipObject
{
	

public:
	/**
	*@brief �R���X�g���N�^
	*/
	AircraftCarrier::AircraftCarrier( int _userID ):ShipObject( _userID )
	{

	}
	
	/**
	*@brief	������
	*@pragma[in]	_userID	
	*/
	void Init();


};


#endif