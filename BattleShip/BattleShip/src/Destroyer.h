/**
*@file	Destroyer.h
*@author	�T�c
*/

#ifndef _DESTROYER_H_
#define _DESTROYER_H_

#include "ShipObject.h"

class Destroyer : public ShipObject {
 public:
	/**
	*@brief �R���X�g���N�^
	*/
	Destroyer::Destroyer( int _userID ) : ShipObject( _userID ) {

	}

	~Destroyer(){};

	void Init();

};


#endif