/**
*@file	SetShip.cpp
*@author	亀田
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

	CheckBoard();

	return m_SetCompFlag;
}

//
int SetShip::CheckBoard()
{
	bool tempFlag = false;	///<	ネストが深くなる事を防止するために、ブロックのクリック判定がtrue
	//	行
	for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
		//	列
		for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
			
			float tempX = m_pMouse->GetCursorPosX(), tempY = m_pMouse->GetCursorPosY();
			
			if( m_pStage->m_stageBlock[m_playerID-1][iColumn][iLine].HitBlockCheck( tempX, tempY )
				&& m_pMouse->MouseStCheck( MOUSE_L, PUSH ))
			{

				//	マス内のデータが空白（0）なら
				if(m_pStage->CheckStageBlock( m_playerID, iColumn, iLine, 0 ))
				{
					
				}
			}
		}
	}
}

//	
void SetShip::Draw()
{

}

//	
void SetShip::ComStandby()
{

}