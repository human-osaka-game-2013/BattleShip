/**
*@file	Selection.cpp
*@author	�T�c
*/

#include "Selection.h"

bool Selection::Init( ShipObject::_SHIP_TYPE_NUM_ _type )
{
	m_StateCompFlag = false;
	m_ShipCount = _type;		///< �Ăяo�����iStateManager�j���珉���͎�̒l�����炤�̂�
	return false;
	
}

//	
int Selection::Control()
{
	if( !m_StateCompFlag )
	{
		/*
		*@todo	���͓���e�X�g�Ƃ��ċ�Ƃ̍s���I���̊������E�N���b�N��
		*/
		if( m_pMouse->MouseStCheck( MOUSE_R, PUSH ) )
			m_ShipCount++;
	}

	if( m_ShipCount >= ShipObject::TYPE_MAX ){
		m_StateCompFlag = true;		
	}
	return m_ShipCount;
}

//	
void Selection::Draw()
{

}

//	
void Selection::ComStandby()
{

}