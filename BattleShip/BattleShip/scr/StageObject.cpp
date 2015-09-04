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
				tempX = ( iLine*( _BLOCK_WIDTH_SIZE_ ))+( _BLOCK_WIDTH_SIZE_ );
				tempY = ( iColumn*( _BLOCK_HEIGHT_SIZE_ ))+( _BLOCK_HEIGHT_SIZE_ );
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

int StageObject::CheckStageBlock( int _player, int _column, int _line, ShipObject* _ship )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return -1;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���

	for( int iColumn = 0, iStageCol = _column-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _line-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){

			bool bStageOutside = false;	///<	��̔z���񂪃X�e�[�W����͂ݏo�Ă��܂��ꍇ�̃t���O

			//	�w�肵���u���b�N���S��5�~5�}�X�͈͒��ׂ�ۂɁA�X�e�[�W�O�𒲂ׂĂ��܂�Ȃ��l��
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}

			//	�w�肵���u���b�N�͈͂��X�e�[�W����͂ݏo���ꍇ
			if( bStageOutside ){
				if( _ship->m_shipArray[iColumn][iLine] != 0 )
					return 1;	///<	�X�e�[�W����o�Ă��āA��̈ꕔ�����݂��Ă���΋�̂��͂ݏo�Ă���ꍇ�Ȃ̂ŁA�w�肵���ꏊ�͖����ł���B
			} else if( m_stageArray[_player][iStageCol][iStageLine] != 0 ) {
				if( _ship->m_shipArray[iColumn][iLine] != 0 )	///<	�X�e�[�W�ɋ�u����ꏊ
					return 2;
			}
		}
	}
	return 0;
}


bool StageObject::SetShip( int _player, int _column, int _line, ShipObject* _ship )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���

	for( int iColumn = 0, iStageCol = _column-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _line-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){
		
			bool bStageOutside = false;	///<	��̔z���񂪃X�e�[�W����͂ݏo�Ă��܂��ꍇ�̃t���O
		
			//	�w�肵���u���b�N���S��5�~5�}�X�͈͒��ׂ�ۂɁA�X�e�[�W�O�𒲂ׂĂ��܂�Ȃ��l��
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}
			//	�X�e�[�W���ŁA��Ȃ����
			if( !bStageOutside &&  m_stageArray[_player][iStageCol][iStageLine]%100 == 0 ){
				if( _ship->m_shipArray[iColumn][iLine] != 0 )
					m_stageArray[_player][iStageCol][iStageLine] = _ship->m_shipArray[iColumn][iLine];
			}
		}

	}
	return true;
}

bool StageObject::SetRange( int _player, int _column, int _line, const int(*_array)[_SHIP_ARRAY_INDEX_], int _setType)
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���

	for( int iColumn = 0, iStageCol = _column-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _line-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){

			bool bStageOutside = false;	///<	��̔z���񂪃X�e�[�W����͂ݏo�Ă��܂��ꍇ�̃t���O

			//	�w�肵���u���b�N���S��5�~5�}�X�͈͒��ׂ�ۂɁA�X�e�[�W�O�𒲂ׂĂ��܂�Ȃ��l��
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}

			//	�X�e�[�W���ŁA�����ׂĂ�z����̒��g��0���ᖳ��������i���U���Ȃǂ͈̔͏�񂪂���΁j
			if( !bStageOutside && _array[iColumn][iLine] != 0  ){
				m_stageArray[_player][iStageCol][iStageLine] += 100*_setType;
			}
		}

	}
	return true;
}

void StageObject::ResetSelect()
{
	//        �v���C���[��
	for( int iPlayer=0; iPlayer<_PLAYER_NUM_; iPlayer++ )
	{	
		//        �s
		for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ )
		{	 
			//        ��
			for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ )
			{	
				//        3���ڂ͑I�����Ȃ̂ŁA�I����񂾂�������l�ɂ��Ă���
				m_stageArray[iPlayer][iColumn][iLine] -= 100*(m_stageArray[iPlayer][iColumn][iLine]/100);
			}		
		}	
	}
}
