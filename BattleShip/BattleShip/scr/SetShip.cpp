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
	m_pStage->ResetSelect();	///<	�X�e�[�W�̑I����Ԃ����Z�b�g

	if( !m_SetCompFlag )
	{
		int iCheckResult = 0;
		//	��u����u���Ȃ��֌W�Ȃ��A�E�N���b�N�ŋ����]������
		if( m_pMouse->MouseStCheck( MOUSE_R, PUSH ) ) {
			ShipObject* tempShip = m_pPlayer[m_playerID]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_SetCount );
			tempShip->RotationShip( 0, true );
		}
		iCheckResult = CheckBoard();

		if( iCheckResult == 2 )
			m_SetCount++;
	}

	if( m_SetCount >= ShipObject::TYPE_MAX ){
		m_SetCompFlag = true;
		m_pStage->ResetSelect();
	}
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
			
			if( m_pStage->m_stageBlock[m_playerID-1][iColumn][iLine].HitBlockCheck( tempX, tempY ))
			{
				int iCheckResult=0;
				ShipObject* tempShip = m_pPlayer[m_playerID]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_SetCount );
				//	�X�e�[�W�u���b�N�̃`�F�b�N
				iCheckResult = m_pStage->CheckStageBlock( m_playerID, iColumn, iLine, tempShip);
				
				if( iCheckResult != 0 )	///<���u����}�X����Ȃ������B
				{	
					//	�u���Ȃ��͈͂������ꍇ���A�u���Ȃ��Ƃ��������X�e�[�W�ɃZ�b�g����
					m_pStage->SetRange( m_playerID, iColumn, iLine, tempShip->m_shipArray, 2 );
					return 1;
				}
				else ///<�u����}�X�B
				{
					m_pStage->SetRange( m_playerID, iColumn, iLine, tempShip->m_shipArray, 1);
					//	��u����}�X�ł���A���N���b�N����������
					if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) {
						m_pStage->SetShip( m_playerID, iColumn, iLine, tempShip );
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