/**
*@file	Result.cpp
*@author	�T�c
*/

#include "Result.h"

bool Result::Init()
{

	return true;
}

//	
int Result::Control()
{
	
	if( !m_StateCompFlag ){
		//	��Ƀv���C���[�̔z��w���Ƃ��āA�C�����Ă���
		int tempPlID = (m_playerID%2) ? 0 : 1;
		int tempEnID = (m_playerID%2) ? 1 : 0;
		m_resultPlayer = ResultOfAction(tempPlID);
		m_resultEnemy = ResultOfAction(tempEnID);
		if( m_resultPlayer != 0 )
		{

		}

		if( m_resultEnemy != 0 )
		{

		}
		m_resultBattle = ResultProgressOfBattle( tempPlID, tempEnID );

		m_StateCompFlag = true;
		m_connectFlag = true;
	}


	//	�퓬���ʂ̉��\��
	switch( m_resultPlayer )
	{
	case RESULT_SEARCH:
		MessageBoxA(0,"�G�ɔ������ꂽ�I","�퓬����",MB_OK);
		break;
	case RESULT_ATTACK:
		MessageBoxA(0,"�U�����ꂽ�I","�퓬����",MB_OK);
		break;
	}
	switch( m_resultEnemy )
	{
	case RESULT_SEARCH:
		MessageBoxA(0,"���G�����I","�퓬����",MB_OK);
		break;
	case RESULT_ATTACK:
		MessageBoxA(0,"�U�������������I","�퓬����",MB_OK);
		break;
	}

	return m_resultBattle;
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

int Result::ResultOfAction( const int _playerIndex )
{
	int iReturn = RESULT_NONE;
	/**
	*@details	Selection�N���X�ő��葤�̃X�e�[�W�f�[�^�Ǝ��g�̃X�e�[�W�͓����ς݂Ȃ̂ŁA
				���[�J���̃f�[�^���Ŏ����Ƒ���̃f�[�^���𔻒肵�Ă��܂��B
	*/

	for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ )	//	�s
	{	
		for( int il=0; il<_STAGE_LINE_MAX_; il++ )	//	��
		{
			//	�X�e�[�W�̊e�����͉��x���A�N�Z�X����\���������ׁA�R�s�[���ď����ł��A�N�Z�X�̃��X�����炷
			const int iSelectNum = m_pStage->m_stageArray[_playerIndex][ic][il]/100;
			const int iConditionNum = (m_pStage->m_stageArray[_playerIndex][ic][il]/10)%10;
			const int iShipNum = m_pStage->m_stageArray[_playerIndex][ic][il]%10;
			
			//	���Gor�U���̎w��������Ă��āA�������}�X��������
			if( iConditionNum != StageObject::_CONDITION_NONE_ && iSelectNum > StageObject::_SELECT_FALSE_ )
			{
				JudgmentOfActionProcess( iReturn, _playerIndex, ic, il, iSelectNum, iShipNum );
			}
		}
	}
	
	
	return iReturn;
}

//
void Result::JudgmentOfActionProcess( int& _iReturn, const int _plIndex, int& _column, int& _line,
										const int _selectNum, const int _shipNum )
{
	
	//	�S�Ă͎̊�Ɍ��ʂ̂���w���������ꍇ�i_SEARCH_ALL_or_ACTION_ALL_�j
	if( _selectNum%2 == 0 )
	{
		//	�w������Ă���s�������G�ŁA������
		if( _selectNum < StageObject::_ACTION_NOMAL_ &&
			_shipNum < ShipObject::TYPE_MAX )
		{
			_iReturn = RESULT_SEARCH;
		}
		//	�w������Ă���s�����U���ŁA������
		else if( _selectNum >= StageObject::_ACTION_NOMAL_ &&
				_shipNum < ShipObject::TYPE_MAX)
		{
			//	���̃}�X�ɍU���w�����o�Ă����ꍇ�A�v���C���[�������Ă����Ƀq�b�g�̔��f������B
			if( m_pPlayer[_plIndex]->DamageControl( _column, _line, (ShipObject::_SHIP_TYPE_NUM_)_shipNum))
			{
				//	��ɍU�������������̂ŁA�X�e�[�W���̃f�[�^��������ԁi�Q���ڂ�_CONDITION_DAMAGE_�Ɂj������
				m_pStage->m_stageArray[_plIndex][_column][_line] += 10;
				_iReturn = RESULT_ATTACK;
			}
		}
	}
	//	�ꕔ�͎̊�Ɍ��ʂ�����w���������ꍇ�i_SEARCH_NOMAL_or_ACTION_NOMAL_�j
	else
	{
		switch( _shipNum )
		{
		//	�����͈ȊO��������
		case ShipObject::TYPE_AIRCARRIER:
		case ShipObject::TYPE_BATTLESHIP:
		case ShipObject::TYPE_CRUISER:
		case ShipObject::TYPE_DESTROYER:
			//	�w������Ă���s�������G�ŁA������
			if( _selectNum < StageObject::_ACTION_NOMAL_ &&
					_shipNum < ShipObject::TYPE_MAX )
			{
				_iReturn = RESULT_SEARCH; ///<
			}
			//	�w������Ă���s�����U���ŁA������
			else if( _selectNum >= StageObject::_ACTION_NOMAL_ &&
					_shipNum < ShipObject::TYPE_MAX)
			{
				//	���̃}�X�ɍU���w�����o�Ă����ꍇ�A�v���C���[�������Ă����Ƀq�b�g�̔��f������B
				if( m_pPlayer[_plIndex]->DamageControl( _column, _line, (ShipObject::_SHIP_TYPE_NUM_)_shipNum))
				{
					//	��ɍU�������������̂ŁA�X�e�[�W���̃f�[�^��������ԁi�Q���ڂ�_CONDITION_DAMAGE_�Ɂj������
					m_pStage->m_stageArray[_plIndex][_column][_line] += 10;
					_iReturn = RESULT_ATTACK;
				}
			}
			break;
		}
	}
}


int Result::ResultProgressOfBattle( const int _playerIndex, const int _enemyIndex )
{
	int iResult = -1;
	int iHitCount[_PLAYER_NUM_] ={0,0};
	ShipObject* pTempShip[_PLAYER_NUM_];

	for( int iShip = 0; iShip < ShipObject::TYPE_MAX; iShip++ )
	{
		//	�v���C���[�̒��ׂ��̃|�C���^���Z�b�g
		pTempShip[_playerIndex] = m_pPlayer[_playerIndex]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
		//	�G�̒��ׂ��̃|�C���^���Z�b�g
		pTempShip[_enemyIndex] = m_pPlayer[_enemyIndex]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
		
		for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++ )
		{
			for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++ )
			{
				int shipCondition = StageObject::ConditionOfData(pTempShip[_playerIndex]->m_shipArray[iColumn][iLine]);
				if( shipCondition == StageObject::_CONDITION_DAMAGE_ ){	//�v���C���[���̔���
					iHitCount[_playerIndex]+=1;	//�q�b�g�񐔃C���N�������g
				}
				shipCondition = StageObject::ConditionOfData(pTempShip[_enemyIndex]->m_shipArray[iColumn][iLine]);
				if( shipCondition == StageObject::_CONDITION_DAMAGE_ ){	//�G���̔���
					iHitCount[_enemyIndex]+=1;	//�q�b�g�񐔃C���N�������g
				}
			}
		}
	}

	if( iHitCount[_playerIndex] == iHitCount[_enemyIndex] )
	{
		iResult = TYPE_DRAW;
	}
	else if( iHitCount[_playerIndex] >= _ANNIHILATION_NUM_ )
	{
		iResult = TYPE_DEFEAT;
	}
	else if( iHitCount[_enemyIndex] >= _ANNIHILATION_NUM_ )
	{
		iResult = TYPE_VICTORY;
	}
	else if( iHitCount[_playerIndex] > iHitCount[_enemyIndex] )
	{
		iResult = TYPE_SUPERIORITY;
	}
	else
	{
		iResult = TYPE_INFERIORITY;
	}

	return iResult;
}