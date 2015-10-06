/**
*@file	Result.cpp
*@author	‹T“c
*/

#include "Result.h"

bool Result::Init()
{

	return true;
}

//	
int Result::Control()
{
	if( ResultOfAction() )

	return false;
}

//	
void Result::Draw()
{

	
}

//	
bool Result::ComStandby()
{
	return true;
}

int Result::ResultOfAction()
{

	for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ )	//	s
	{	
		for( int il=0; il<_STAGE_LINE_MAX_; il++ )	//	—ñ
		{
			
		}
	}
	return 0;
}