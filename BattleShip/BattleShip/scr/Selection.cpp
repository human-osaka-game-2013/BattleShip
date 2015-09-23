/**
*@file	Selection.cpp
*@author	�T�c
*/

#include "Selection.h"

bool Selection::Init()
{
	m_StateCompFlag = false;
	m_tabSelectFlag = false;
	m_areaSelectFlag= false;

	m_tempShip = m_pPlayer[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_ShipCount );
		
	m_actionFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY()+_TAB_HEIGHT_*2, 
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_actionFrame.SetColor( 255, 255, 255, 255 );
	
	m_searchFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY()+_TAB_HEIGHT_,
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_searchFrame.SetColor( 255, 255, 255, 255 );

	m_moveFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY(),
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_moveFrame.SetColor( 255, 255, 255, 255 );

	return false;
	
}

//	
int Selection::Control()
{
	m_tempX = (float)m_pMouse->GetCursorPosX();
	m_tempY = (float)m_pMouse->GetCursorPosY();

	if( !m_StateCompFlag )
	{
		if( !m_tabSelectFlag ){
			m_tabSelectFlag = TabCheck();
		}else if( !m_areaSelectFlag ){
			m_areaSelectFlag = SetTypeArray();
		}else{
			m_pStage->ResetSelect();
			SelectArrayCheck();
		}
	}

	
	return m_ShipCount;
}


bool Selection::TabCheck()
{
	ResetTabFrame();
	bool tempFlag = false;

	//	�I���^�u���Ƃ̃}�E�X�Ƃ̐ڐG����
	if( m_actionFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		m_actionFrame.SetColor( 255, 150, 150, 150 );
		if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			m_selectType = _SELECT_ACTION_;
			tempFlag = true;
		}
	}
	if( m_searchFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		m_searchFrame.SetColor( 255, 150, 150, 150 );
		if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			m_selectType = _SELECT_SEARCH_;
			tempFlag = true;
		}
	}
	if( m_moveFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		m_moveFrame.SetColor( 255, 150, 150, 150 );
		if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			m_selectType = _SELECT_MOVE_;
			tempFlag = true;
		}
	}

	return tempFlag;
}


bool Selection::SetTypeArray()
{
	switch( m_selectType )
	{
	case _SELECT_ACTION_:
		m_tempArray = m_tempShip->m_actionArray;
		break;
	case _SELECT_SEARCH_:
		m_tempArray = m_tempShip->m_searchArray;
		break;
	case _SELECT_MOVE_:
		m_tempArray = m_tempShip->m_moveArray;
		break;
	}

	return true;
}

int Selection::SelectArrayCheck(  )
{
	int tempID = m_playerID;	///<�ǂ���̃v���C���[�̃X�e�[�W�z����������̔���p�ɃR�s�[
	int (*tempArray)[_SHIP_ARRAY_INDEX_];

	//	�U���ƍ��G�Ȃ瑊�葤ID�A�ړ��Ȃ玩������ID���g������
	switch( m_selectType )
	{
	case _SELECT_ACTION_:
	case _SELECT_SEARCH_:
		if( --tempID <= 0 )	///<�`�F�b�N����X�e�[�W�z��̎w���̔���
			tempID+=2;
		break;
	case _SELECT_MOVE_:
		
		break;
	}

	//	�s
	for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
		//	��
		for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
			
			if( m_pStage->m_stageBlock[tempID-1][iColumn][iLine].HitBlockCheck( m_tempX, m_tempY ))
			{
				int iCheckResult=0;
				//	�X�e�[�W�u���b�N�̃`�F�b�N
				switch( m_selectType )
				{
				case _SELECT_ACTION_:
					iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, ShipObject::ARRAY_TYPE_ACTION );
					tempArray = m_tempShip->m_actionArray;
					break;
				case _SELECT_SEARCH_:
					iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, ShipObject::ARRAY_TYPE_SEARCH );
					tempArray = m_tempShip->m_searchArray;
					break;
				case _SELECT_MOVE_:
					iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, ShipObject::ARRAY_TYPE_MOVE );
					tempArray = m_tempShip->m_moveArray;
					break;
				}

				
				
				
				if( iCheckResult == 2 )	///<���u����}�X����Ȃ������B
				{	
					//	�u���Ȃ��͈͂������ꍇ���A�u���Ȃ��Ƃ��������X�e�[�W�ɃZ�b�g����
					m_pStage->SetRange( tempID, iColumn, iLine, tempArray, 2 );
					return 1;
				}
				else ///<�u����}�X�B
				{
					m_pStage->SetRange( tempID, iColumn, iLine, tempArray, 1);
					//	��u����}�X�ł���A���N���b�N����������
					if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) {
						m_pStage->SetShip( tempID, iColumn, iLine, m_tempShip );
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

void Selection::ResetTabFrame()
{
	m_actionFrame.SetColor( 255, 255, 255, 255 );
	m_searchFrame.SetColor( 255, 255, 255, 255 );
	m_moveFrame.SetColor( 255, 255, 255, 255 );

}

//	
void Selection::Draw()
{
	if( !m_tabSelectFlag ){
		m_pDrawManager->VertexDraw( _TEX_TABFRAME_, m_actionFrame.GetPositionX(), m_actionFrame.GetPositionY(),
			m_actionFrame.GetWidth(), m_actionFrame.GetHeight(),
			0.f, (_TAB_HEIGHT_*2)/_TAB_WIDTH_, 1.f, 1.f,
			m_actionFrame.GetAlpha(), m_actionFrame.GetRed(), m_actionFrame.GetGreen(), m_actionFrame.GetBlue() );
		
		m_pDrawManager->VertexDraw( _TEX_TABFRAME_, m_searchFrame.GetPositionX(), m_searchFrame.GetPositionY(),
			m_searchFrame.GetWidth(), m_searchFrame.GetHeight(),
			0.f, _TAB_HEIGHT_/_TAB_WIDTH_, 1.f, (_TAB_HEIGHT_*2)/_TAB_WIDTH_,
			m_searchFrame.GetAlpha(), m_searchFrame.GetRed(), m_searchFrame.GetGreen(), m_searchFrame.GetBlue() );
		
		m_pDrawManager->VertexDraw( _TEX_TABFRAME_, m_moveFrame.GetPositionX(), m_moveFrame.GetPositionY(),
			m_moveFrame.GetWidth(), m_moveFrame.GetHeight(), 
			0.f, 0.f, 1.f, _TAB_HEIGHT_/_TAB_WIDTH_,
			m_moveFrame.GetAlpha(), m_moveFrame.GetRed(), m_moveFrame.GetGreen(), m_moveFrame.GetBlue() );

	}
	else{

	}
}

//	
void Selection::ComStandby()
{

}