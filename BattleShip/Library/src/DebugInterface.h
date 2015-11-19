/**
*@file	DebugInterface.h
*@author	亀田
*@brief	デバッグ時のインターフェース関数
*/

#ifndef _DEBUGINTERFACE_H_
#define _DEBUGINTERFACE_H_


#include <stdarg.h>
#include <cstdio>

void DebugMsgBox( char* tszParam, ... );

#endif