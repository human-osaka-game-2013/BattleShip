/**
*@file	Cruiser.h
*@author	�T�c
*/

#ifndef _CRUISER_H_
#define _CRUISER_H_

#include "ShipObject.h"

class Cruiser : public ShipObject
{

public:
	/**
	*@brief �R���X�g���N�^
	*/
	Cruiser::Cruiser( int _userID ):ShipObject( _userID )
	{

	}

	void Init();

};


#endif