#include "ConnectSetting.h"

void ConnectSetting::Control()
{
	if( m_pMouse->MouseStCheck( MOUSE_L, PUSH ) ){
		
	}

	
}

//	�O���t�@�C���̏����Z�b�g
void ConnectSetting::SetTable( char* _p, int _iColumn, int _iLine )
{
	
	switch( _iColumn )
	{
	case 0:
		if( memcmp( _p, "Server", 6) == 0 ){
			sockType = false;
		}else if( memcmp( _p, "Client",6) == 0 ){
			sockType = true;
		}
		break;
	case 1:
		if( sockType ){	///<	�h���C�������K�v�Ȃ̂̓N���C�A���g�������Ȃ̂�
			if( memcmp( _p, "localhost", 9) == 0 ){
				strAddr = "127.0.0.1";
			}else{
				strAddr = _p;
			}
		}
		break;
	case 2:
		strPort = atoi(_p);

		break;
	}
}