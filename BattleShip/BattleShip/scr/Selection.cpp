/**
*@file	Selection.cpp
*@author	亀田
*/

#include "Selection.h"

bool Selection::Init( ShipObject::_SHIP_TYPE_NUM_ _type )
{
	m_StateCompFlag = false;
	m_ShipCount = _type;		///< 呼び出し元（StateManager）から初期艦種の値をもらうので
	return false;
	
}

//	
int Selection::Control()
{
	if( !m_StateCompFlag )
	{
		/*
		*@todo	今は動作テストとして駒ごとの行動選択の完了を右クリックで
		*/
		if( m_pMouse->MouseStCheck( MOUSE_R, PUSH ) )
			m_ShipCount++;
	}

	if( m_ShipCount >= ShipObject::TYPE_MAX ){
		m_StateCompFlag = true;		
	}
	return m_ShipCount;
}

//	
void Selection::Draw()
{

}

//	
void Selection::ComStandby()
{

}