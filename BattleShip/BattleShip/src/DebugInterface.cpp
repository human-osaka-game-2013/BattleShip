/**
*@file	DebugInterface.cpp
*@author	�T�c
*@brief	�f�o�b�O���̃C���^�[�t�F�[�X�֐�
*/
#include <windows.h>

#include"DebugInterface.h"


void DebugMsgBox( char* tszParam, ... )
{
	TCHAR tszStr[1024];
	va_list list;
	va_start( list, tszParam );
	vsprintf_s( tszStr, 1024, tszParam, list );

	MessageBox( GetForegroundWindow(), tszStr, TEXT("DEBUG"), MB_OK );
}