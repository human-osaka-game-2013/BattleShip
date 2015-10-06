/**
*@file	Result.cpp
*@author	亀田
*/

#include "Result.h"

bool Result::Init()
{

	return true;
}

//	
int Result::Control()
{
	//	先にプレイヤーの配列指数として、修正しておく
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
	*@details	Selectionクラスで相手側のステージデータと自身のステージは同期済みなので、
				ローカルのデータ内で自分と相手のデータ情報を判定してしまう。
	*/

	for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ )	//	行
	{	
		for( int il=0; il<_STAGE_LINE_MAX_; il++ )	//	列
		{
			//	ステージの各桁情報は何度もアクセスする可能性が高い為、コピーして少しでもアクセスのロスを減らす
			const int iSelectNum = m_pStage->m_stageArray[_playerIndex][ic][il]/100;
			const int iShipNum = m_pStage->m_stageArray[_playerIndex][ic][il]%10;
			
			//	索敵or攻撃の指示がされていないマスだったら
			if( iSelectNum < StageObject::_SEARCH_NOMAL_ )
			{
				continue;
			}
			//	全ての艦種に効果のある指示だった場合（_SEARCH_ALL_or_ACTION_ALL_）
			else if( iSelectNum%2 == 0 )
			{
				//	指示されている行動が索敵で、駒があれば
				if( iSelectNum < StageObject::_ACTION_NOMAL_ &&
						iShipNum < ShipObject::TYPE_MAX )
				{
					iReturn = 1; ///<
				}
				//	指示されている行動が攻撃で、駒があれば
				else if( iSelectNum >= StageObject::_ACTION_NOMAL_ &&
						iShipNum < ShipObject::TYPE_MAX)
				{
					//	そのマスに攻撃指示が出ていた場合、プレイヤーが持っている駒にヒットの判断させる。
					if( m_pPlayer[_playerIndex]->DamageControl( ic, il, (ShipObject::_SHIP_TYPE_NUM_)iShipNum))
					{
						//	駒に攻撃が当たったので、ステージ側のデータも損傷状態（２桁目を_CONDITION_DAMAGE_に）をつける
						m_pStage->m_stageArray[_playerIndex][ic][il] += 10;
						iReturn = 2;
					}
				}
			}
			//	一部の艦種に効果がある指示だった場合（_SEARCH_NOMAL_or_ACTION_NOMAL_）
			else
			{
				switch( iShipNum )
				{
				//	潜水艦以外だったら
				case ShipObject::TYPE_AIRCARRIER:
				case ShipObject::TYPE_BATTLESHIP:
				case ShipObject::TYPE_CRUISER:
				case ShipObject::TYPE_DESTROYER:
					//	指示されている行動が索敵で、駒があれば
					if( iSelectNum < StageObject::_ACTION_NOMAL_ &&
							iShipNum < ShipObject::TYPE_MAX )
					{
						iReturn = 1; ///<
					}
					//	指示されている行動が攻撃で、駒があれば
					else if( iSelectNum >= StageObject::_ACTION_NOMAL_ &&
							iShipNum < ShipObject::TYPE_MAX)
					{
						//	そのマスに攻撃指示が出ていた場合、プレイヤーが持っている駒にヒットの判断させる。
						if( m_pPlayer[_playerIndex]->DamageControl( ic, il, (ShipObject::_SHIP_TYPE_NUM_)iShipNum))
						{
							//	駒に攻撃が当たったので、ステージ側のデータも損傷状態（２桁目を_CONDITION_DAMAGE_に）をつける
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