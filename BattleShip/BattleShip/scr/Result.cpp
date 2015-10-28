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


	return m_resultBattle;
}

//	
void Result::Draw()
{
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
	
	
}

//	
bool Result::ComStandby()
{
	return true;
}

int Result::ResultOfAction( const int _playerIndex )
{
	int iReturn = 0;
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
			const int iShipNum = m_pStage->m_stageArray[_playerIndex][ic][il]%10;
			
			//	���Gor�U���̎w��������Ă��Ȃ��}�X��������
			if( iSelectNum < StageObject::_SEARCH_NOMAL_ )
			{
				continue;
			}
			//	�S�Ă͎̊�Ɍ��ʂ̂���w���������ꍇ�i_SEARCH_ALL_or_ACTION_ALL_�j
			else if( iSelectNum%2 == 0 )
			{
				//	�w������Ă���s�������G�ŁA������
				if( iSelectNum < StageObject::_ACTION_NOMAL_ &&
						iShipNum < ShipObject::TYPE_MAX )
				{
					iReturn = RESULT_SEARCH; ///<
				}
				//	�w������Ă���s�����U���ŁA������
				else if( iSelectNum >= StageObject::_ACTION_NOMAL_ &&
						iShipNum < ShipObject::TYPE_MAX)
				{
					//	���̃}�X�ɍU���w�����o�Ă����ꍇ�A�v���C���[�������Ă����Ƀq�b�g�̔��f������B
					if( m_pPlayer[_playerIndex]->DamageControl( ic, il, (ShipObject::_SHIP_TYPE_NUM_)iShipNum))
					{
						//	��ɍU�������������̂ŁA�X�e�[�W���̃f�[�^��������ԁi�Q���ڂ�_CONDITION_DAMAGE_�Ɂj������
						m_pStage->m_stageArray[_playerIndex][ic][il] += 10;
						iReturn = RESULT_ATTACK;
					}
				}
			}
			//	�ꕔ�͎̊�Ɍ��ʂ�����w���������ꍇ�i_SEARCH_NOMAL_or_ACTION_NOMAL_�j
			else
			{
				switch( iShipNum )
				{
				//	�����͈ȊO��������
				case ShipObject::TYPE_AIRCARRIER:
				case ShipObject::TYPE_BATTLESHIP:
				case ShipObject::TYPE_CRUISER:
				case ShipObject::TYPE_DESTROYER:
					//	�w������Ă���s�������G�ŁA������
					if( iSelectNum < StageObject::_ACTION_NOMAL_ &&
							iShipNum < ShipObject::TYPE_MAX )
					{
						iReturn = RESULT_SEARCH; ///<
					}
					//	�w������Ă���s�����U���ŁA������
					else if( iSelectNum >= StageObject::_ACTION_NOMAL_ &&
							iShipNum < ShipObject::TYPE_MAX)
					{
						//	���̃}�X�ɍU���w�����o�Ă����ꍇ�A�v���C���[�������Ă����Ƀq�b�g�̔��f������B
						if( m_pPlayer[_playerIndex]->DamageControl( ic, il, (ShipObject::_SHIP_TYPE_NUM_)iShipNum))
						{
							//	��ɍU�������������̂ŁA�X�e�[�W���̃f�[�^��������ԁi�Q���ڂ�_CONDITION_DAMAGE_�Ɂj������
							m_pStage->m_stageArray[_playerIndex][ic][il] += 10;
							iReturn = RESULT_ATTACK;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}
	
	
	return iReturn;
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
				int shipCondition = (pTempShip[_playerIndex]->m_shipArray[iColumn][iLine]/10)%10;
				if( shipCondition == StageObject::_CONDITION_DAMAGE_ ){	//�v���C���[���̔���
					iHitCount[_playerIndex]+=1;	//�q�b�g�񐔃C���N�������g
				}
				shipCondition = (pTempShip[_enemyIndex]->m_shipArray[iColumn][iLine]/10)%10;
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
	else if( iHitCount[_playerIndex] == _ANNIHILATION_NUM_ )
	{
		iResult = TYPE_DEFEAT;
	}
	else if( iHitCount[_enemyIndex] == _ANNIHILATION_NUM_ )
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