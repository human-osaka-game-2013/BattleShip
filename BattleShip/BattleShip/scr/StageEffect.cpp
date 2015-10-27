/**
*@file	StageEffect.cpp
*@author	‹T“c
*/

#include "StageEffect.h"

bool StageEffect::Init()
{

	return false;
}

int StageEffect::Control()
{


	return ((m_StateCompFlag) ? 1 : 0);
}

//	
void StageEffect::Draw()
{

}

bool StageEffect::ComStandby()
{
	return true;
}