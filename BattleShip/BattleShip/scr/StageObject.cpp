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

int StageObject::CheckStageBlock( int _player, int _column, int _line, ShipObject* _ship, ShipObject::_SHIP_ARRAY_TYPE_ _arrayType )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return -1;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	int(*_array)[_SHIP_ARRAY_INDEX_];	///<�ǂ̔z��f�[�^�Ƃ̃`�F�b�N���s�����̊i�[�p
	_player--;	///<	�z��w���p�ɒ���
	
	//---�ǂ̔z��f�[�^���`�F�b�N���邩�̕���---
	switch( _arrayType )
	{
	case ShipObject::ARRAY_TYPE_SHIP:
		_array = _ship->m_shipArray;
		break;
	case ShipObject::ARRAY_TYPE_ACTION:
		_array = _ship->m_actionArray;
		break;
	case ShipObject::ARRAY_TYPE_SEARCH:
		_array = _ship->m_searchArray;
		break;
	case ShipObject::ARRAY_TYPE_MOVE:
		return -1;
	
	}//---

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
				if( _array[iColumn][iLine] != 0 )
					return 1;	///<	�X�e�[�W�O�Ƀu���b�N�̎��̂��������ꍇ
			} else if( m_stageArray[_player][iStageCol][iStageLine] != 0 ) {
				if( _array[iColumn][iLine] != 0 )	
					return 2;	///<	�w�肵���u���b�N�͈̔͂ɂ��łɃX�e�[�W��ŉ��������݂��Ă����ꍇ
			}
		}
	}
	return 0;	///<�w�肵���͈͉͂��ɂ��ڐG�����Ȃ�����
}

int StageObject::CheckStageBlock( int _player, int _column, int _line, ShipObject* _ship, 
	const int(*_array)[_SHIP_ARRAY_INDEX_], int _shipCount )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���
	int iStageCol;
	int iStageLine;
	
	for( int iColumn = 0, iStageCol = _ship->GetArrayColumn()-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _ship->GetArrayLine()-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){

			bool bStageOutside = false;	///<	��̔z���񂪃X�e�[�W����͂ݏo�Ă��܂��ꍇ�̃t���O

			//	�w�肵���u���b�N���S��5�~5�}�X�͈͒��ׂ�ۂɁA�X�e�[�W�O�𒲂ׂĂ��܂�Ȃ��l��
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}

			//	�w�肵���u���b�N�͈͂��X�e�[�W����͂ݏo���ꍇ
			if( bStageOutside ){
				if( _array[iColumn][iLine] != 0 ){
					return 
				}
			} else if( (m_stageArray[_player][iStageCol][iStageLine]%10) != _shipCount+1 
					&& iStageCol != 0 && iStageLine != 0 ) {
				if( _array[iColumn][iLine] != 0 )
					SetRange( _player+1, iStageCol, iStageLine, 2 );
				continue;
			}
			if( _array[iColumn][iLine] != 0 ){
				
				SetRange( _player+1, iStageCol, iStageLine, 1 );
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

bool StageObject::SetRange( int _player, int _column, int _line, int _setType )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���

	//	�X�e�[�W���ŁA�����ׂĂ�z����̒��g��0���ᖳ��������i���U���Ȃǂ͈̔͏�񂪂���΁j
	if( (m_stageArray[_player][_column][_line] / 100) != 0 ){
		//        3���ڂ͑I�����Ȃ̂ŁA�I����񂾂�������l�ɂ��Ă���
		m_stageArray[_player][_column][_line] -= 100*(m_stageArray[_player][_column][_line]/100);
		m_stageArray[_player][_column][_line] += 100*_setType;
	}
	else{
		m_stageArray[_player][_column][_line] += 100*_setType;
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
