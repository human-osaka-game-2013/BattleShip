/**
*@file	Submarine.h
*@author	�T�c
*/

#ifndef _SUBMARINE_H_
#define _SUBMARINE_H_

#include "ShipObject.h"

class Submarine : public ShipObject {
 public:
	/**
	*@brief �R���X�g���N�^
	*/
	Submarine::Submarine( int _userID ) : ShipObject( _userID ) {

	}

	~Submarine(){};

	void Init();

};

#endif