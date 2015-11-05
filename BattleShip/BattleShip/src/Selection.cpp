/**
*@file	Selection.cpp
*@author	�T�c
*/

#include "Selection.h"

bool Selection::Init()
{
	m_tabSelectFlag = false;
	m_areaSelectFlag= false;
	m_arrayCheckResult = 0;
	
	m_tempShip = m_pPlayer[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)(m_ShipCount) );
		
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
		if( !m_tabSelectFlag )	///<	�^�u���܂��I�΂�Ă��Ȃ��ꍇ
		{
			if( m_pPlayer[m_playerID-1]->CheckDestroy( static_cast<ShipObject::_SHIP_TYPE_NUM_>( m_ShipCount) ) )
			{
				MessageBoxA(0,"���̊͂͂��łɍ������Ă��܂��B\n�ΐ푊��̑I���܂ł��҂��������B",NULL,MB_OK);
				m_connectFlag = true;	///<	�ʐM�t���O�𗧂ĂĒʐM�̏����Ɉڂ�
				m_StateCompFlag = true;	///<	�s���I�����̂͊��������̂ŁA�t���O�𗧂Ă�
			}
			m_tabSelectFlag = TabCheck();
		}
		else if( !m_areaSelectFlag )	///<	�ΏۃG���A�Ȃǂ̑I�����I����Ă��Ȃ��ꍇ
		{
			m_areaSelectFlag = SetTypeArray();
			if( !m_areaSelectFlag )	///< �I�������͈͂Ƀf�[�^�������ior���̍s���͏o���Ȃ��j�ꍇ�A�^�u�̑I������������B
				m_tabSelectFlag = false;
		}
		else if( m_arrayCheckResult != 2 )	///<	�I�������͈͂͗L���Ŗ����ꍇ
		{
			m_pStage->ResetSelect();
			m_arrayCheckResult = SelectArrayCheck();
		}
		else{	///<	�s���I�����͈͑I�����������ꍇ
			m_connectFlag = true;	///<	�ʐM�t���O�𗧂ĂĒʐM�̏����Ɉڂ�
			m_StateCompFlag = true;	///<	�s���I�����̂͊��������̂ŁA�t���O�𗧂Ă�
		}
		
	}

	return ((m_StateCompFlag) ? 1 : 0);
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

	for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++ ){
		for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++ ){
			if( m_tempArray[iColumn][iLine] != StageObject::_CONDITION_NONE_)
			return true;
		}
	}

	MessageBoxA(0,"���̊͂ł̂��̍s���͑I���o���܂���B",NULL,MB_OK);
	return false;
}



int Selection::SelectArrayCheck( )
{
	int tempID;	///<�ǂ���̃v���C���[�̃X�e�[�W�z����������̔���p�ɃR�s�[
	int (*tempArray)[_SHIP_ARRAY_INDEX_];
	int iCheckResult = 0;
	int iColumn;	
	int iLine;

	//	�U���ƍ��G�Ȃ瑊�葤ID�A�ړ��Ȃ玩������ID��tempID�ɓ����
	switch( m_selectType )
	{
	case _SELECT_ACTION_:
	case _SELECT_SEARCH_:
		tempID = m_playerID/_PLAYER_NUM_? 1:2;	//���葤��ID������
		//	�s
		for( iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
			//	��
			for( iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
				
				if( m_pStage->m_stageBlock[tempID-1][iColumn][iLine].HitBlockCheck( m_tempX, m_tempY ))
				{
					//	�X�e�[�W�u���b�N�̃`�F�b�N
					switch( m_selectType )
					{
					case _SELECT_ACTION_:
						iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, 
																	ShipObject::ARRAY_TYPE_ACTION, m_ShipCount );
						tempArray = m_tempShip->m_actionArray;
						break;
					case _SELECT_SEARCH_:
						iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, 
																	ShipObject::ARRAY_TYPE_SEARCH, m_ShipCount );
						tempArray = m_tempShip->m_searchArray;
						break;
					}

					if( iCheckResult == -1 )	///<���u����}�X����Ȃ������B
					{	
						return -1;
					}
					else ///<�u����}�X�B
					{
						m_pStage->SetRange( tempID, iColumn, iLine, tempArray, StageObject::_SELECT_TRUE_ );
						//	��u����}�X�ł���A���N���b�N����������
						if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) 
						{
							m_pStage->SetRange( tempID, iColumn, iLine, tempArray, m_selectType );
							
							return 2;
						}
					}
				}
			}
		}
		break;

	case _SELECT_MOVE_:
		tempID = m_playerID;		//�������g��ID������
		int tempColumn, tempLine;	//	�ړ��O�̍��W
		m_tempShip->GetArrayPos( tempColumn, tempLine );
		tempArray = m_tempShip->m_moveArray;
		m_pStage->SetStageToRange( tempID, m_tempShip, tempArray, m_ShipCount );
		
		iCheckResult =  m_pStage->CheckRangeOnStage( iColumn, iLine, tempID, m_tempX, m_tempY, m_tempShip, ShipObject::ARRAY_TYPE_SHIP );

		float tempW = _BLOCK_WIDTH_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
		float tempH = _BLOCK_HEIGHT_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���

		if( iCheckResult == -1 )	///<���u����}�X����Ȃ������B
		{	
			return -1;
		}
		else if( iCheckResult == 1  )	///<�u����}�X�B
		{
			if(tempID == 1)	//�v���C���[ID��1�i=�z��̎w������0�j��������
			{
				m_tempX = iLine*tempW + tempW*1.5f ;		
				m_tempY = iColumn*tempH + tempH*1.5f;
			}
			else if(tempID == 2)
			{
				m_tempX = (iLine+_STAGE_HEIGHT_MAX_)*tempW + tempW*1.5f ;
				m_tempY = iColumn*tempH + tempH*1.5f;
			}
			m_tempShip->SetPosition( m_tempX, m_tempY, 0.5f );
			if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) 
			{
				m_pStage->RelocationShip( tempID, iColumn, iLine, m_tempShip, m_ShipCount );
				return 2;
			}
			return 1;
		}
		else
		{
			m_tempShip->GetArrayPos( iColumn, iLine );

			if(tempID == 1)	//�v���C���[ID��1�i=�z��̎w������0�j��������
			{
				m_tempX = iLine*tempW + tempW*1.5f ;		
				m_tempY = iColumn*tempH + tempH*1.5f;
			}
			else if(tempID == 2)
			{
				m_tempX = (iLine+_STAGE_HEIGHT_MAX_)*tempW + tempW*1.5f ;
				m_tempY = iColumn*tempH + tempH*1.5f;
			}
			m_tempShip->SetPosition( m_tempX, m_tempY, 0.5f );
		}
		
		break;
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
bool Selection::ComStandby()
{
#ifdef	_NOT_USE_COM_
	//�{���Ȃ瑊�葤�̃X�e�[�W��񂪗���܂ŁA�u�ʐM���v�Ȃǂ̉摜��\�����āA�҂����Ēu�����A
	//���̓e�X�g�ׁ̈A�������g�̃X�e�[�W���𑊎�ƌ����ĂāA�}�[�W����B
	
	return false;
#else
	return true;
#endif
}
