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
			}
			//�X�e�[�W�̒��������ꍇ
			else if( ConditionOfData(m_stageArray[_player][iStageCol][iStageLine]) != _CONDITION_NONE_ ){
				//	��w���ɑ��݂���
				if( ShipTypeOfData(m_stageArray[_player][iStageCol][iStageLine]) == _shipNum ){
					continue;	///<	�����Ɠ����͎�i�����_�ł͎������g�j�̏ꍇ
				}
				else if( _array[iColumn][iLine] != _CONDITION_NONE_ ){
					return 2;	///<	�w�肵���u���b�N�͈̔͂ɂ��łɃX�e�[�W���(����ȊO��)���������݂��Ă����ꍇ
				}
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
					int iHitResult = SelectOfData(m_stageArray[_player][iStageCol][iStageLine]);
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
				continue;	///<	�X�e�[�W�O�Ɏw��͈͂̎��̂�����ƁA�͈͂̃Z�b�g�̂��悤�������̂Ŕ�΂�
	
			}
			//	�w�肳��ĂȂ�
			if(_array[iColumn][iLine] == _CONDITION_NONE_)
			{
				continue;
			}
			//	�w��͈͂ƍ��`�F�b�N���Ă���u���b�N�Ɏ����̋�ȊO�̏�񂪂������ꍇ�i���S���W�͍��͒��ׂ�K�v�͂Ȃ��j
			else if( ShipTypeOfData(m_stageArray[_player][iStageCol][iStageLine]) != _shipCount && 
				(m_stageArray[_player][iStageCol][iStageLine]/10) != _CONDITION_NONE_ ) 
			{
				SetRange( _player+1, iStageCol, iStageLine, _SELECT_FALSE_ );	
			}
			else
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
			if( !bStageOutside ){
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
	float tempX;	
	float tempY;
	if(_player == 0){	//�v���C���[ID��1�i=�z��̎w������0�j��������
		tempX = _line*tempW + tempW*1.5f ;
		tempY = _column*tempH + tempH*1.5f;
	}else{
		tempX = (_line+_STAGE_HEIGHT_MAX_)*tempW + tempW*1.5f ;
		tempY = _column*tempH + tempH*1.5f;
	}

	_ship->SetPosition( tempX, tempY, 0.5f );

	return true;
}

bool StageObject::SetRange( int _player, const int _column, const int _line, const _ARRAY_DATA_TYPE_SELECT_ _setType )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	�v���C���[ID��1��2�ȊO�������ꍇ

	_player--;	///<	�z��w���p�ɒ���

	//	�X�e�[�W���ŁA�����ׂĂ�z����̒��g��0���ᖳ��������i���U���Ȃǂ͈̔͏�񂪂���΁j
	if( SelectOfData(m_stageArray[_player][_column][_line]) != _CONDITION_NONE_ ){
		//        3���ڂ͑I�����Ȃ̂ŁA�I����񂾂�������l�ɂ��Ă���
		m_stageArray[_player][_column][_line] -= 100*SelectOfData(m_stageArray[_player][_column][_line]);
		m_stageArray[_player][_column][_line] += 100*_setType;
	}
	else{
		m_stageArray[_player][_column][_line] += 100*_setType;
	}
	return true;
}


bool StageObject::SetRange( int _player, const int _column, const int _line, 
							const int(*_array)[_SHIP_ARRAY_INDEX_], const int _selectNum )
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
				switch( _selectNum )
				{
				case GameState::_SELECT_ACTION_:
					//	�X�e�[�W���ŁA�����ׂĂ�z����̒��g��0���ᖳ��������i���U���Ȃǂ͈̔͏�񂪂���΁j
					if( SelectOfData(m_stageArray[_player][_column][_line]) != _CONDITION_NONE_ ){
						//        3���ڂ͑I�����Ȃ̂ŁA�I����񂾂�������l�ɂ��Ă���
						m_stageArray[_player][iStageCol][iStageLine] -= 100*SelectOfData(m_stageArray[_player][iStageCol][iStageLine]);
						m_stageArray[_player][iStageCol][iStageLine] += 100*(_array[iColumn][iLine]+(_ACTION_NOMAL_-1));
					}
					else{
						m_stageArray[_player][_column][_line] += 100*(_array[iColumn][iLine]+(_ACTION_NOMAL_-1));
					}

					break;
				case GameState::_SELECT_SEARCH_:
					//	�X�e�[�W���ŁA�����ׂĂ�z����̒��g��0���ᖳ��������i���U���Ȃǂ͈̔͏�񂪂���΁j
					if( SelectOfData(m_stageArray[_player][iStageCol][iStageLine]) != _CONDITION_NONE_ ){
						//        3���ڂ͑I�����Ȃ̂ŁA�I����񂾂�������l�ɂ��Ă���
						m_stageArray[_player][iStageCol][iStageLine] -= 100*SelectOfData(m_stageArray[_player][iStageCol][iStageLine]);
						m_stageArray[_player][iStageCol][iStageLine] += 100*(_array[iColumn][iLine]+(_SEARCH_NOMAL_-1));
					}
					else{
						m_stageArray[_player][iStageCol][iStageLine] += 100*(_array[iColumn][iLine]+(_SEARCH_NOMAL_-1));
					}

					break;
				}
			}
			
		}

	}
	return true;
}


bool StageObject::SetRange( int _player, const int _column, const int _line, const int(*_array)[_SHIP_ARRAY_INDEX_],
					const _ARRAY_DATA_TYPE_SELECT_ _setType )
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
			/*	�X�e�[�W���ł���A
				�w�肵����̃f�[�^������ꍇ�i��͎̂��݂��Ă��邱�Ɓj
			*/
			if( !bStageOutside && ShipTypeOfData(m_stageArray[_player][iStageCol][iStageLine]) == _shipNum )
			{
				m_stageArray[_player][iStageCol][iStageLine] -= ShipOfData(m_stageArray[_player][iStageCol][iStageLine]);
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
			if( !bStageOutside ){
				m_stageArray[_player][iStageCol][iStageLine] += _ship->m_shipArray[iColumn][iLine];
			}
		}
	}

	_ship->SetArrayPos( _column, _line );	///<�@�z�u����s�Ɨ�̍��W���Z�b�g
	_ship->SetDeadFlag( false );///<���ݒu�����̂ŃI�u�W�F�N�g�̎��S�t���O��������
						
	//	��̊�_�i���S�_�j��\�ߎZ�o�����Ă���
	float tempW = _BLOCK_WIDTH_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
	float tempH = _BLOCK_HEIGHT_SIZE_;		///<	�X�e�[�W���1�R�}�̃T�C�Y�̓��͂��ȗ���
	float tempX;	
	float tempY;
	if(_player == 0)	//�v���C���[ID��1�i=�z��̎w������0�j��������
	{
		tempX = _line*tempW + tempW*1.5f ;		
		tempY = _column*tempH + tempH*1.5f;
	}
	else if(_player == 1)
	{
		tempX = (_line+_STAGE_HEIGHT_MAX_)*tempW + tempW*1.5f ;
		tempY = _column*tempH + tempH*1.5f;
	}
	_ship->SetPosition( tempX, tempY, 0.5f );
	
	return true;
}

void StageObject::ResetSelect()
{
	//	�v���C���[��
	for( int iPlayer=0; iPlayer<_PLAYER_NUM_; iPlayer++ )
	{	
		//	�s
		for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ )
		{	 
			//	��
			for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ )
			{	
				//	3���ڂ͑I�����Ȃ̂ŁA�I����񂾂�������l�ɂ��Ă���
				m_stageArray[iPlayer][iColumn][iLine] -= 100*(m_stageArray[iPlayer][iColumn][iLine]/100);
			}		
		}	
	}
}


//	�X�e�[�W�f�[�^�̓���
bool StageObject::MargeStage( ConnectStage* _pStage, const int _playerID, const int _enemyID, const int _customMargeType )
{

	if( _customMargeType != StateManager::STATE_SET_SHIP )
	{
		//	���葤�i_pStage�j�������Ă����A���݂��̃X�e�[�W�ɑ΂��čs�����A�I�����i3���ځj�ƁA
		//	���݂����g�̋�ɑ΂��Ă̍s���i�ړ��j�����X�V���Ă��B
		for( int iColumn = 0; iColumn < _STAGE_COLUMN_MAX_; iColumn++ ){
			for( int iLine = 0; iLine < _STAGE_LINE_MAX_; iLine++ ){
			//	���葤�̃X�e�[�W
			m_stageArray[_enemyID-1][iColumn][iLine] = 				
				( ShipOfData(_pStage->m_stageArray[_enemyID-1][iColumn][iLine])) +
				( SelectOfData(m_stageArray[_enemyID-1][iColumn][iLine])*100 );
			//	�������̃X�e�[�W
			m_stageArray[_playerID-1][iColumn][iLine] = 				
				( ShipOfData(m_stageArray[_playerID-1][iColumn][iLine])) +
				( SelectOfData(_pStage->m_stageArray[_playerID-1][iColumn][iLine])*100 );
			}
		}
	}
	else
	{
		memmove_s( m_stageArray[_enemyID-1], sizeof(int[_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_]),_pStage->m_stageArray[_enemyID-1] ,sizeof(int[_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_]));
	}

	return true;
}