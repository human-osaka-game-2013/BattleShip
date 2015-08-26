/**
*@file	SetShip.cpp
*@author	�T�c
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
	
	if( !m_SetCompFlag )
	{
		int iCheckResult = 0;
		iCheckResult = CheckBoard();

		if( iCheckResult == 2 )
			m_SetCount++;
	}

	if( m_SetCount >= ShipObject::TYPE_MAX )
		m_SetCompFlag = true;

	return m_SetCompFlag;
}

//
int SetShip::CheckBoard()
{
	bool tempFlag = false;	///<	�l�X�g���[���Ȃ鎖��h�~���邽�߂ɁA�u���b�N�̃N���b�N���肪true
	m_pStage->ResetSelect();	///<	�X�e�[�W�̑I����Ԃ����Z�b�g
	
	//	�s
	for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
		//	��
		for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
			
			float tempX = m_pMouse->GetCursorPosX(), tempY = m_pMouse->GetCursorPosY();
			
			if( m_pStage->m_stageBlock[m_playerID-1][iColumn][iLine].HitBlockCheck( tempX, tempY ))
			{
				int iCheckResult=0;
				iCheckResult = m_pStage->CheckStageBlock( m_playerID, iColumn, iLine, 
												m_pPlayer[m_playerID]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_SetCount ));
				if( iCheckResult != 0 )	///<���u����}�X����Ȃ������B
				{	
					return 1;
				}
				else ///<�u����}�X�B
				{
					ShipObject* tempShip = m_pPlayer[m_playerID]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_SetCount );

					m_pStage->SetRange( m_playerID, iColumn, iLine, tempShip->m_shipArray);

					if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) {
						m_pStage->SetShip( m_playerID, iColumn, iLine, 
												m_pPlayer[m_playerID]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_SetCount ) );
					return 2;
					}
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