/**
*@file	StageObject.cpp
*@author	�T�c
*/

#include "StageObject.h"
#include "StateManager.h"

bool StageObject::Init()
{
	float tempX, tempY;
	//	�X�e�[�W�}�X�ڕ\��
	//	�v���C���[��
	for( int iPlayer=0; iPlayer<_PLAYER_NUM_; iPlayer++ ){
		//	�s
		for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
			//	��
			for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
				m_stageArray[iPlayer][iColumn][iLine] = 0;	///<	�v���C���[1�̃X�e�[�W�f�[�^������
				
				//	��_�̌v�Z�B�����̃��[�v�񐔂ɍ��킦�ău���b�N�������W�𒲐�
				tempX = ( iColumn*( _BLOCK_WIDTH_SIZE_ ))+( _BLOCK_WIDTH_SIZE_ );
				tempY = ( iLine*( _BLOCK_HEIGHT_SIZE_ ))+( _BLOCK_HEIGHT_SIZE_ );
				if( iPlayer == 1 )	//	�v���C���[2�̕\���̂�X���W�����炷�B
					tempX += _BLOCK_WIDTH_SIZE_*11;

				m_stageBlock[iPlayer][iColumn][iLine].Init( tempX, tempY, _BLOCK_WIDTH_SIZE_, _BLOCK_HEIGHT_SIZE_ );
			}
		}
	}
	return true;
}


void  StageObject::Free()
{

}

bool StageObject::CheckStageBlock( int _player, int _column, int _line, unsigned char _vol )
{
	if( m_stageArray[_player-1][_column][_line] == _vol )
	{
		return true;
	}
	return false;
}

