/**
*@file	DebugInterface.h
*@author	亀田
*@brief	デバッグ時のインターフェース関数
*/

#ifndef _DEBUGINTERFACE_H_
#define _DEBUGINTERFACE_H_

#include <windows.h>
#include <stdarg.h>
#include <cstdio>

void DebugMsgBox( TCHAR* tszParam, ... );

#endif