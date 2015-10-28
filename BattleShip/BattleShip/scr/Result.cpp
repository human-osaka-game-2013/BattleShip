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
	if( !m_StateCompFlag ){
		//	先にプレイヤーの配列指数として、修正しておく
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
	//	戦闘結果の仮表示
	switch( m_resultPlayer )
	{
	case RESULT_SEARCH:
		MessageBoxA(0,"敵に発見された！","戦闘結果",MB_OK);
		break;
	case RESULT_ATTACK:
		MessageBoxA(0,"攻撃された！","戦闘結果",MB_OK);
		break;
	}
	switch( m_resultEnemy )
	{
	
	case RESULT_SEARCH:
		MessageBoxA(0,"索敵成功！","戦闘結果",MB_OK);
		break;
	case RESULT_ATTACK:
		MessageBoxA(0,"攻撃が当たった！","戦闘結果",MB_OK);
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
					iReturn = RESULT_SEARCH; ///<
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
						iReturn = RESULT_ATTACK;
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
						iReturn = RESULT_SEARCH; ///<
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
		//	プレイヤーの調べる駒のポインタをセット
		pTempShip[_playerIndex] = m_pPlayer[_playerIndex]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
		//	敵の調べる駒のポインタをセット
		pTempShip[_enemyIndex] = m_pPlayer[_enemyIndex]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
		
		for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++ )
		{
			for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++ )
			{
				int shipCondition = (pTempShip[_playerIndex]->m_shipArray[iColumn][iLine]/10)%10;
				if( shipCondition == StageObject::_CONDITION_DAMAGE_ ){	//プレイヤー側の判定
					iHitCount[_playerIndex]+=1;	//ヒット回数インクリメント
				}
				shipCondition = (pTempShip[_enemyIndex]->m_shipArray[iColumn][iLine]/10)%10;
				if( shipCondition == StageObject::_CONDITION_DAMAGE_ ){	//敵側の判定
					iHitCount[_enemyIndex]+=1;	//ヒット回数インクリメント
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