/**
*@file	SetShip.cpp
*@author	�T�c
*/

#include "SetShip.h"

bool SetShip::Init()
{
	m_StateCompFlag = false;
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
	}

	if( m_ShipCount >= ShipObject::TYPE_MAX ){
		m_StateCompFlag = true;
		m_pStage->ResetSelect();
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
				iCheckResult = m_pStage->CheckStageBlock( m_playerID, iColumn, iLine, m_tempShip, ShipObject::ARRAY_TYPE_SHIP );
				
				if( iCheckResult != 0 )	///<���u����}�X����Ȃ������B
				{	
					//	�u���Ȃ��͈͂������ꍇ���A�u���Ȃ��Ƃ��������X�e�[�W�ɃZ�b�g����
					m_pStage->SetRange( m_playerID, iColumn, iLine, m_tempShip->m_shipArray, 2 );
					return 1;
				}
				else ///<�u����}�X�B
				{
					m_pStage->SetRange( m_playerID, iColumn, iLine, m_tempShip->m_shipArray, 1);
					//	��u����}�X�ł���A���N���b�N����������
					if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) {
						m_pStage->SetShip( m_playerID, iColumn, iLine, m_tempShip );
						m_tempShip->SetArrayPos( iColumn, iLine );
						m_tempShip->SetDeadFlag( false );///<���ݒu�����̂ŃI�u�W�F�N�g�̎��S�t���O��������
						
						//	��̊�_�i���S�_�j��\�ߎZ�o�����Ă���
						float tempW = _BLOCK_WIDTH_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
						float tempH = _BLOCK_HEIGHT_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
						m_tempX = iLine*tempW + tempW*1.5f ;		
						m_tempY = iColumn*tempH + tempH*1.5f;
						m_tempShip->SetPosition( m_tempX, m_tempY, 0.5f );
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
void SetShip::ComStandby()
{

}