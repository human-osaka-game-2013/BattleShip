/**
*@file	Submarine.h
*@author	亀田
*/

#ifndef _SUBMARINE_H_
#define _SUBMARINE_H_

#include "ShipObject.h"

class Submarine : public ShipObject {
 public:
	/**
	*@brief コンストラクタ
	*/
	Submarine::Submarine( int _userID ) : ShipObject( _userID ) {

	}

	~Submarine(){};

	void Init();

};

#endif