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
	m_effectCount++;

	if( _END_COUNT_OF_EFFECT_ >= m_effectCount )
	{
		m_pStage->ResetSelect();
		m_StateCompFlag = true;
	}

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