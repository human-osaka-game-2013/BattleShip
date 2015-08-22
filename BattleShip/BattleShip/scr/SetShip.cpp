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
	
	m_SetCompFlag = false;

	CheckBoard();

	return m_SetCompFlag;
}

//
int SetShip::CheckBoard()
{
	bool tempFlag = false;	///<	�l�X�g���[���Ȃ鎖��h�~���邽�߂ɁA�u���b�N�̃N���b�N���肪true
	//	�s
	for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
		//	��
		for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
			
			float tempX = m_pMouse->GetCursorPosX(), tempY = m_pMouse->GetCursorPosY();
			
			if( m_pStage->m_stageBlock[m_playerID-1][iColumn][iLine].HitBlockCheck( tempX, tempY )
				&& m_pMouse->MouseStCheck( MOUSE_L, PUSH ))
			{

				//	�}�X���̃f�[�^���󔒁i0�j�Ȃ�
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