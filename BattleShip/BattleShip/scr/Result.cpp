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
	//	��Ƀv���C���[�̔z��w���Ƃ��āA�C�����Ă���
	int tempID = (m_playerID%2) ? 1 : 0;


	if( ResultOfAction(0) )
	{

	}

	if( ResultOfAction(1) )
	{

	}

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

int Result::ResultOfAction( int _playerIndex )
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
					iReturn = 1; ///<
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
						iReturn = 2;
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
						iReturn = 1; ///<
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
							iReturn = 2;
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