/**
*@file	Submarine.h
*@author	�T�c
*/

#ifndef _SUBMARINE_H_
#define _SUBMARINE_H_

#include "ShipObject.h"

class Submarine : public ShipObject
{

public:
	/**
	*@brief �R���X�g���N�^
	*/
	Submarine::Submarine():ShipObject()
	{

	}

	void Init( int _userID );

};

#endif