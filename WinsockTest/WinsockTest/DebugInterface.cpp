/**
*@file	DebugInterface.cpp
*@author	亀田
*@brief	デバッグ時のインターフェース関数
*/

#include"DebugInterface.h"


void DebugMsgBox( TCHAR* tszParam, ... )
{
	TCHAR tszStr[1024];
	va_list list;
	va_start( list, tszParam );
	vsprintf_s( tszStr, 1024, tszParam, list );

	MessageBox( GetForegroundWindow(), tszStr, TEXT("DEBUG"), MB_OK );
}