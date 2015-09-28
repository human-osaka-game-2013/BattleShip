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


int StageObject::CheckStageBlock( int _player, const int _column, const int _line, ShipObject* _ship, 
								ShipObject::_SHIP_ARRAY_TYPE_ _arrayType, const int _shipNum )
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
	case ShipObject::ARRAY_TYPE_MOVE:	///<	���̊֐��ł͈ړ��͈͂̃`�F�b�N�����͏o���Ȃ�
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
				if( _array[iColumn][iLine] != _CONDITION_NONE_ )
					return 1;	///<	�X�e�[�W�O�Ƀu���b�N�̎��̂��������ꍇ
			} else if( m_stageArray[_player][iStageCol][iStageLine] != _CONDITION_NONE_ )	{
				if( (m_stageArray[_player][iStageCol][iStageLine])%10 == _shipNum )
					continue;	///<	�����Ɠ����͎�i�����_�ł͎������g�j�̏ꍇ
				if( _array[iColumn][iLine] != _CONDITION_NONE_ )	
					return 2;	///<	�w�肵���u���b�N�͈̔͂ɂ��łɃX�e�[�W���(����ȊO��)���������݂��Ă����ꍇ
			}
		}
	}
	return 0;	///<�w�肵���͈͉͂��ɂ��ڐG�����Ȃ�����
}


int StageObject::CheckRangeOnStage(  int& _column, int& _line, 
							int _player, const float _x, const float _y, ShipObject* _ship, ShipObject::_SHIP_ARRAY_TYPE_ _arrayType)
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return -1;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���

	for( int iColumn = 0, iStageCol = _ship->GetArrayColumn()-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _ship->GetArrayLine()-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){

			bool bStageOutside = false;	///<	��̔z���񂪃X�e�[�W����͂ݏo�Ă��܂��ꍇ�̃t���O

			//	�w�肵���u���b�N���S��5�~5�}�X�͈͒��ׂ�ۂɁA�X�e�[�W�O�𒲂ׂĂ��܂�Ȃ��l��
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}

			if( !bStageOutside )
			{
				if(m_stageBlock[_player][iStageCol][iStageLine].HitBlockCheck( _x, _y ))
				{
					int iHitResult = m_stageArray[_player][iStageCol][iStageLine] /100;
					switch(iHitResult)
					{
					case 0:
					case 1:
					case 2:
						_column = iStageCol;
						_line = iStageLine;
						return iHitResult;
					default:
						return -1;
					}
				}
			}
		}

	}
	return -1;
}


bool StageObject::SetStageToRange( int _player, ShipObject* _ship, const int(*_array)[_SHIP_ARRAY_INDEX_], const int _shipCount )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���
	
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
				if( _array[iColumn][iLine] != _CONDITION_NONE_ ){
					continue;	///<	�X�e�[�W�O�Ɏw��͈͂̎��̂�����ƁA�͈͂̃Z�b�g�̂��悤�������̂Ŕ�΂�
				}
			}
			//	�w��͈͂ƍ��`�F�b�N���Ă���u���b�N�Ɏ����̋�ȊO�̏�񂪂������ꍇ�i���S���W�͍��͒��ׂ�K�v�͂Ȃ��j
			else if( (m_stageArray[_player][iStageCol][iStageLine]%10) != _shipCount) 
			{
				if( _array[iColumn][iLine] != _CONDITION_NONE_ ){
					SetRange( _player+1, iStageCol, iStageLine, _SELECT_FALSE_ );
				}
			}
			else if( _array[iColumn][iLine] != _CONDITION_NONE_ )
			{
				//----�����ňړ���̗\��ʒu�i�ł̋�ƃX�e�[�W�j�̃`�F�b�N���s��----
				//	�ړ���͈ړ��o���Ȃ��ꏊ�������ꍇ	(_player��1�����Ă���̂́i�z��̎w������j���X�̃v���C���[ID�ɒ�����)
				if( CheckStageBlock( _player+1, iStageCol, iStageLine, _ship, ShipObject::ARRAY_TYPE_SHIP, _shipCount ) !=0 ){
					SetRange( _player+1, iStageCol, iStageLine, _SELECT_FALSE_ );	
				}
				//	�ړ���͋�̔z�u���\�������ꍇ
				else{
					
					SetRange( _player+1, iStageCol, iStageLine, _SELECT_TRUE_ );	
				}
				//--------
			}
		}
	}


	return true;
}

bool StageObject::SetShip( int _player, const int _column, const int _line, ShipObject* _ship )
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
			if( !bStageOutside &&  m_stageArray[_player][iStageCol][iStageLine]%100 == _CONDITION_NONE_ ){
				if( _ship->m_shipArray[iColumn][iLine] != _CONDITION_NONE_ )
					m_stageArray[_player][iStageCol][iStageLine] = _ship->m_shipArray[iColumn][iLine];
			}
		}

	}

	_ship->SetArrayPos( _column, _line );	///<�@�z�u����s�Ɨ�̍��W���Z�b�g
	_ship->SetDeadFlag( false );///<���ݒu�����̂ŃI�u�W�F�N�g�̎��S�t���O��������
						
	//	��̊�_�i���S�_�j��\�ߎZ�o�����Ă���
	float tempW = _BLOCK_WIDTH_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
	float tempH = _BLOCK_HEIGHT_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
	float tempX = _line*tempW + tempW*1.5f ;		
	float tempY = _column*tempH + tempH*1.5f;
	_ship->SetPosition( tempX, tempY, 0.5f );

	return true;
}

bool StageObject::SetRange( int _player, const int _column, const int _line, const int _setType )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���

	//	�X�e�[�W���ŁA�����ׂĂ�z����̒��g��0���ᖳ��������i���U���Ȃǂ͈̔͏�񂪂���΁j
	if( (m_stageArray[_player][_column][_line] / 100) != _CONDITION_NONE_ ){
		//        3���ڂ͑I�����Ȃ̂ŁA�I����񂾂�������l�ɂ��Ă���
		m_stageArray[_player][_column][_line] -= 100*(m_stageArray[_player][_column][_line]/100);
		m_stageArray[_player][_column][_line] += 100*_setType;
	}
	else{
		m_stageArray[_player][_column][_line] += 100*_setType;
	}
	return true;
}

bool StageObject::SetRange( int _player, const int _column, const int _line, const int(*_array)[_SHIP_ARRAY_INDEX_], const int _setType)
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
			if( !bStageOutside && _array[iColumn][iLine] != _CONDITION_NONE_  ){
				m_stageArray[_player][iStageCol][iStageLine] += 100*_setType;
			}
		}

	}
	return true;
}


bool StageObject::RelocationShip( int _player, const int _column, const int _line, ShipObject* _ship, const int _shipNum )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���

	int tempColunm;
	int tempLine;
	_ship->GetArrayPos( tempColunm, tempLine );

	for( int iColumn = 0, iStageCol = tempColunm-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = tempLine-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){
		
			bool bStageOutside = false;	///<	��̔z���񂪃X�e�[�W����͂ݏo�Ă��܂��ꍇ�̃t���O
		
			//	�w�肵���u���b�N���S��5�~5�}�X�͈͒��ׂ�ۂɁA�X�e�[�W�O�𒲂ׂĂ��܂�Ȃ��l��
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}
			//	�X�e�[�W���ŁA��Ȃ����
			if( !bStageOutside &&  m_stageArray[_player][iStageCol][iStageLine]%100 == _shipNum )
			{
				m_stageArray[_player][iStageCol][iStageLine] -= m_stageArray[_player][iStageCol][iStageLine]%100;
			}
		}

	}

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
				if( _ship->m_shipArray[iColumn][iLine] != _CONDITION_NONE_ )
					m_stageArray[_player][iStageCol][iStageLine] += _ship->m_shipArray[iColumn][iLine];
			}
		}

	}

	_ship->SetArrayPos( _column, _line );	///<�@�z�u����s�Ɨ�̍��W���Z�b�g
	_ship->SetDeadFlag( false );///<���ݒu�����̂ŃI�u�W�F�N�g�̎��S�t���O��������
						
	//	��̊�_�i���S�_�j��\�ߎZ�o�����Ă���
	float tempW = _BLOCK_WIDTH_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
	float tempH = _BLOCK_HEIGHT_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
	float tempX = _line*tempW + tempW*1.5f ;		
	float tempY = _column*tempH + tempH*1.5f;
	_ship->SetPosition( tempX, tempY, 0.5f );

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
