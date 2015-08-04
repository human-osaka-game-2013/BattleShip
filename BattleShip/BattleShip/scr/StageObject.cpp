/**
*@file	StageObject.cpp
*@author	亀田
*/

#include "StageObject.h"

bool StageObject::Init()
{
	for( int iColumn = 0; iColumn < _STAGE_COLUMN_MAX_; iColumn ){
		for( int iLine = 0; iLine < _STAGE_LINE_MAX_; iLine )	{
			m_stageArray[0][iColumn][iLine] = 0;	///<	プレイヤー1のステージデータ初期化
			m_stageArray[1][iColumn][iLine] = 0;	///<	プレイヤー2のステージデータ初期化
		}
	}
}