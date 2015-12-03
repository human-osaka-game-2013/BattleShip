#include "Button.h"
#include "input.h"

char Button::Contorl( const float _x, const float _y, const char _inputState ) 
{

	if( HitBlockCheck( _x, _y ) && m_state != STATE_SELECT )
	{
		SetPosition( defaultPosX-(selectVol/2.f), defaultPosY-(selectVol/2.f), 0.5f );
		SetColor( 255, 200, 200, 200 );
		SetWidth( defaultWidth+selectVol );
		SetHeight( defaultHeight+selectVol );
		m_state = STATE_ON_CURSOR;

		//	ç∂ÉNÉäÉbÉN
		if( _inputState==PUSH )
		{
			m_state = STATE_SELECT;
		}
	}
	else if( _inputState==OFF && m_state != STATE_SELECT)
	{
		SetPosition( defaultPosX, defaultPosY, 0.5f );
		SetColor( 255, 255, 255, 255 );
		SetWidth( defaultWidth );
		SetHeight( defaultHeight );
		m_state = STATE_OFF_CURSOR;
	}
	if( m_state == STATE_SELECT )
	{
		SetPosition( defaultPosX+(selectVol/2.f), defaultPosY+(selectVol/2.f), 0.5f );
		SetColor( 255, 100, 100, 100 );
		SetWidth( defaultWidth-selectVol );
		SetHeight( defaultHeight-selectVol );
	}

	return static_cast<char>(m_state);
}