
#include "TextField.h"

const byte TextField::ConvertNumFromWord( int _num )
{
	byte result = 0;
	switch( _num )
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		result = _num+0x30;
		break;
	case 10:
		result = '.';	///< Key.h“à‚ÌeKEYKINDŠî€‚ÅƒsƒŠƒIƒh‚ÍŒ»Ý10‚Æ”»’è
		break;
	default:
		result = 0x00;
		break;
	}
	return result;
}
