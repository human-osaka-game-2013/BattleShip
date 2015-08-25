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

	if( m_SetCount >= ShipObject::TYPE_MAX )
		m_SetCompFlag = true;

	
	if( !m_SetCompFlag )
	{
		int iCheckResult = 0;
		iCheckResult = CheckBoard();

		if( iCheckResult == 2 )
			m_SetCount++;
	}


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
				int iCheckResult=0;
				iCheckResult = m_pStage->CheckStageBlock( m_playerID, iColumn, iLine, 
												m_pPlayer[m_playerID]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_SetCount ));
				if( iCheckResult != 0 )	///<駒を置けるマスじゃなかった。
				{	
					return 1;
				}
				else	///<置けるマス。
				{
					m_pStage->SetShip(  m_playerID, iColumn, iLine, 
												m_pPlayer[m_playerID]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_SetCount ) );
					return 2;
				}
			}
		}
	}

	return 0;
}

//	
void SetShip::Draw()
{

}

//	
void SetShip::ComStandby()
{

}