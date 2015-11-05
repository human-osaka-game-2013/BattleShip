/**
*@file	SetShip.cpp
*@author	�T�c
*/

#include "SetShip.h"

bool SetShip::Init()
{
	return false;
}

//	
int SetShip::Control()
{
	m_pStage->ResetSelect();	///<	�X�e�[�W�̑I����Ԃ����Z�b�g
	m_tempX = (float)m_pMouse->GetCursorPosX();	///<	�}�E�X���W�̍X�V
	m_tempY = (float)m_pMouse->GetCursorPosY();	///<	�}�E�X���W�̍X�V
	m_tempShip = m_pPlayer[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_ShipCount );
			
	if( !m_StateCompFlag )
	{
		int iCheckResult = 0;
		//	��u����u���Ȃ��֌W�Ȃ��A�E�N���b�N�ŋ����]������
		if( m_pMouse->MouseStCheck( MOUSE_R, PUSH ) ) {
			m_tempShip->RotationShip( 0, true );

		}
		iCheckResult = CheckBoard();

		if( iCheckResult == 2 )
			m_ShipCount++;

		if( m_ShipCount >= ShipObject::TYPE_MAX ){
			m_StateCompFlag = true;
			m_connectFlag = true;
			m_pStage->ResetSelect();
		}
	}
		
	return m_ShipCount;
}

//
int SetShip::CheckBoard()
{
	bool tempFlag = false;	///<	�l�X�g���[���Ȃ鎖��h�~���邽�߂ɁA�u���b�N�̃N���b�N���肪true

	//	�s
	for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
		//	��
		for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
			
			if( m_pStage->m_stageBlock[m_playerID-1][iColumn][iLine].HitBlockCheck( m_tempX, m_tempY ))
			{
				int iCheckResult=0;
				
				//	�X�e�[�W�u���b�N�̃`�F�b�N
				iCheckResult = m_pStage->CheckStageBlock( m_playerID, iColumn, iLine, m_tempShip, ShipObject::ARRAY_TYPE_SHIP, m_ShipCount );
				
				if( iCheckResult != 0 )	///<���u����}�X����Ȃ������B
				{	
					//	�u���Ȃ��͈͂������ꍇ���A�u���Ȃ��Ƃ��������X�e�[�W�ɃZ�b�g����
					m_pStage->SetRange( m_playerID, iColumn, iLine, m_tempShip->m_shipArray, StageObject::_SELECT_FALSE_ );
					return 1;
				}
				else ///<�u����}�X�B
				{
					m_pStage->SetRange( m_playerID, iColumn, iLine, m_tempShip->m_shipArray, StageObject::_SELECT_TRUE_);
					//	��u����}�X�ł���A���N���b�N����������
					if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) {
						m_pStage->SetShip( m_playerID, iColumn, iLine, m_tempShip );

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
	if( m_ShipCount < ShipObject::TYPE_MAX )
	{
		m_pDrawManager->VertexTransform( m_ShipCount + _TEX_AIRCARRIER_, m_tempShip->m_vertex, m_tempX, m_tempY, 1.f, 1.f, m_tempShip->GetDirection()*90.f );
	}
}

//	
bool SetShip::ComStandby()
{
	return true;
}