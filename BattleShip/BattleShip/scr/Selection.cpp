/**
*@file	Selection.cpp
*@author	亀田
*/

#include "Selection.h"

bool Selection::Init()
{
	m_StateCompFlag = false;
	m_tabSelectFlag = false;
	m_areaSelectFlag= false;

	m_tempShip = m_pPlayer[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)m_ShipCount );
		
	m_actionFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY(),
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_actionFrame.SetColor( 255, 255, 255, 255 );
	
	m_searchFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY()+_TAB_HEIGHT_,
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_searchFrame.SetColor( 255, 255, 255, 255 );

	m_moveFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY()+_TAB_HEIGHT_*2, 
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_moveFrame.SetColor( 255, 255, 255, 255 );

	return false;
	
}

//	
int Selection::Control()
{
	m_tempX = m_pMouse->GetCursorPosX();
	m_tempY = m_pMouse->GetCursorPosY();

	if( !m_StateCompFlag )
	{
		if( !m_tabSelectFlag ){
			m_tabSelectFlag = TabCheck();
		}else if( !m_areaSelectFlag ){
			m_areaSelectFlag = SetTypeArray();
		}else{

		}
	}

	
	return m_ShipCount;
}


bool Selection::TabCheck()
{
	ResetTabFrame();
	bool tempFlag = false;

	//	選択タブごとのマウスとの接触判定
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

int Selection::SelectArrayCheck()
{


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
			0.f, 0.f, 1.f, _TAB_HEIGHT_/_TAB_WIDTH_,
			m_actionFrame.GetAlpha(), m_actionFrame.GetRed(), m_actionFrame.GetGreen(), m_actionFrame.GetBlue() );
		
		m_pDrawManager->VertexDraw( _TEX_TABFRAME_, m_searchFrame.GetPositionX(), m_searchFrame.GetPositionY(),
			m_searchFrame.GetWidth(), m_searchFrame.GetHeight(),
			0.f, _TAB_HEIGHT_/_TAB_WIDTH_, 1.f, (_TAB_HEIGHT_*2)/_TAB_WIDTH_,
			m_searchFrame.GetAlpha(), m_searchFrame.GetRed(), m_searchFrame.GetGreen(), m_searchFrame.GetBlue() );
		
		m_pDrawManager->VertexDraw( _TEX_TABFRAME_, m_moveFrame.GetPositionX(), m_moveFrame.GetPositionY(),
			m_moveFrame.GetWidth(), m_moveFrame.GetHeight(), 
			0.f, (_TAB_HEIGHT_*2)/_TAB_WIDTH_, 1.f, 1.f,
			m_moveFrame.GetAlpha(), m_moveFrame.GetRed(), m_moveFrame.GetGreen(), m_moveFrame.GetBlue() );

	}
	else{

	}
}

//	
void Selection::ComStandby()
{

}