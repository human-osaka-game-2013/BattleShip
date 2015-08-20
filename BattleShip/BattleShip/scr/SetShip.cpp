/**
*@file	SetShip.cpp
*@author	‹T“c
*/

#include "SetShip.h"

bool SetShip::Init()
{
	m_SetCompFlag = false;
	m_SetCount = ShipObject::TYPE_AIRCARRIER;
	return false;
}

//	
bool SetShip::Control()
{
	



	return m_SetCompFlag;
}

//	
void SetShip::Draw()
{

}

//	
void SetShip::ComStandby()
{

}