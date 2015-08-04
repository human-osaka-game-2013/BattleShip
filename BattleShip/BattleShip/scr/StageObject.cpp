/**
*@file	StageObject.cpp
*@author	�T�c
*/

#include "StageObject.h"

bool StageObject::Init()
{
	for( int iColumn = 0; iColumn < _STAGE_COLUMN_MAX_; iColumn ){
		for( int iLine = 0; iLine < _STAGE_LINE_MAX_; iLine )	{
			m_stageArray[0][iColumn][iLine] = 0;	///<	�v���C���[1�̃X�e�[�W�f�[�^������
			m_stageArray[1][iColumn][iLine] = 0;	///<	�v���C���[2�̃X�e�[�W�f�[�^������
		}
	}
}