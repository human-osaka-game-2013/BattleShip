/**
*@file	SetShip.cpp
*@author	ãTìc
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
	
	m_SetCompFlag = false;

	//	çs
	for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
		//	óÒ
		for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
			bool tempFlag = false;
			float tempX = m_pMouse->GetCursorPosX(), tempY = m_pMouse->GetCursorPosY();
			
			if( m_pStage->m_stageBlock[m_playerID-1][iColumn][iLine].HitBlockCheck( tempX, tempY )
				&& m_pMouse->MouseStCheck( MOUSE_L, PUSH ))
			{
				
			}
		}
	}

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