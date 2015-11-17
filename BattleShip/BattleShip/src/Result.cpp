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

		//	戦闘結果の仮表示
		//	自プレイヤー側に起きたイベント（敵の行動選択による結果）
		switch( m_resultPlayer )
		{
		case RESULT_SEARCH:
			m_tempStr1 = m_pGameLog->GetPhrase(FixedPhrase::RESULT_DISCOVERED_STR);
			break;
		case RESULT_ATTACK:
			m_tempStr1 = m_pGameLog->GetPhrase(FixedPhrase::RESULT_HIT_STR);
			break;
		}
		//	敵側に起きたイベント（自プレイヤーの行動選択による結果
		switch( m_resultEnemy )
		{
		case RESULT_SEARCH:
			m_tempStr2 = m_pGameLog->GetPhrase(FixedPhrase::RESULT_SIGHT_STR);
			break;
		case RESULT_ATTACK:
			m_tempStr2 = m_pGameLog->GetPhrase(FixedPhrase::RESULT_IMPACT_STR);
			break;
		}
		//	何かイベントがあった場合、ログに追加する
		if( m_resultPlayer > 0 )
			m_pGameLog->AddStream( m_tempStr1.c_str(), _LOG_COLOR_WARNING_ );
		if( m_resultEnemy > 0 )
			m_pGameLog->AddStream( m_tempStr2.c_str(), _LOG_COLOR_SUCCESS_ );
		
		switch( m_resultBattle )
		{
		case TYPE_INFERIORITY:
			m_tempStr1 = m_pGameLog->GetPhrase(FixedPhrase::RESULT_INFERIORITY_STR);
			m_pGameLog->AddStream( m_tempStr1.c_str(), _LOG_COLOR_WARNING_ );
			break;
		case TYPE_DRAW:
			m_tempStr1 = m_pGameLog->GetPhrase(FixedPhrase::RESULT_DRAW_STR);
			m_pGameLog->AddStream( m_tempStr1.c_str(), _LOG_COLOR_NOMAL_ );
			break;
		case TYPE_SUPERIORITY:
			m_tempStr1 = m_pGameLog->GetPhrase(FixedPhrase::RESULT_SUPERIORITY_STR);
			m_pGameLog->AddStream( m_tempStr1.c_str(), _LOG_COLOR_SUCCESS_ );
			break;
		}
		
		m_StateCompFlag = true;
	}

	return m_resultBattle;
}

//	
void Result::Draw()
{
	
	
	
}

int Result::ResultOfAction( const int _playerIndex )
{
	int iReturn = RESULT_NONE;
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
			const int iConditionNum = (m_pStage->m_stageArray[_playerIndex][ic][il]/10)%10;
			const int iShipNum = m_pStage->m_stageArray[_playerIndex][ic][il]%10;
			
			//	索敵or攻撃の指示がされていて、且つ駒があるマスだったら
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
	
	//	全ての艦種に効果のある指示だった場合（_SEARCH_ALL_or_ACTION_ALL_）
	if( _selectNum%2 == 0 )
	{
		//	指示されている行動が索敵で、駒があれば
		if( _selectNum < StageObject::_ACTION_NOMAL_ &&
			_shipNum < ShipObject::TYPE_MAX )
		{
			_iReturn = RESULT_SEARCH;
		}
		//	指示されている行動が攻撃で、駒があれば
		else if( _selectNum >= StageObject::_ACTION_NOMAL_ &&
				_shipNum < ShipObject::TYPE_MAX)
		{
			//	そのマスに攻撃指示が出ていた場合、プレイヤーが持っている駒にヒットの判断させる。
			if( m_pPlayer[_plIndex]->DamageControl( _column, _line, (ShipObject::_SHIP_TYPE_NUM_)_shipNum))
			{
				//	駒に攻撃が当たったので、ステージ側のデータも損傷状態（２桁目を_CONDITION_DAMAGE_に）をつける
				m_pStage->m_stageArray[_plIndex][_column][_line] += 10;
				_iReturn = RESULT_ATTACK;
			}
		}
	}
	//	一部の艦種に効果がある指示だった場合（_SEARCH_NOMAL_or_ACTION_NOMAL_）
	else
	{
		switch( _shipNum )
		{
		//	潜水艦以外だったら
		case ShipObject::TYPE_AIRCARRIER:
		case ShipObject::TYPE_BATTLESHIP:
		case ShipObject::TYPE_CRUISER:
		case ShipObject::TYPE_DESTROYER:
			//	指示されている行動が索敵で、駒があれば
			if( _selectNum < StageObject::_ACTION_NOMAL_ &&
					_shipNum < ShipObject::TYPE_MAX )
			{
				_iReturn = RESULT_SEARCH; ///<
			}
			//	指示されている行動が攻撃で、駒があれば
			else if( _selectNum >= StageObject::_ACTION_NOMAL_ &&
					_shipNum < ShipObject::TYPE_MAX)
			{
				//	そのマスに攻撃指示が出ていた場合、プレイヤーが持っている駒にヒットの判断させる。
				if( m_pPlayer[_plIndex]->DamageControl( _column, _line, (ShipObject::_SHIP_TYPE_NUM_)_shipNum))
				{
					//	駒に攻撃が当たったので、ステージ側のデータも損傷状態（２桁目を_CONDITION_DAMAGE_に）をつける
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
		//	プレイヤーの調べる駒のポインタをセット
		pTempShip[_playerIndex] = m_pPlayer[_playerIndex]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
		//	敵の調べる駒のポインタをセット
		pTempShip[_enemyIndex] = m_pPlayer[_enemyIndex]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
		
		for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++ )
		{
			for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++ )
			{
				int shipCondition = StageObject::ConditionOfData(pTempShip[_playerIndex]->m_shipArray[iColumn][iLine]);
				if( shipCondition == StageObject::_CONDITION_DAMAGE_ ){	//プレイヤー側の判定
					iHitCount[_playerIndex]+=1;	//ヒット回数インクリメント
				}
				shipCondition = StageObject::ConditionOfData(pTempShip[_enemyIndex]->m_shipArray[iColumn][iLine]);
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
	else if( iHitCount[_playerIndex] >= _ANNIHILATION_NUM_ )
	{
		iResult = TYPE_DEFEAT;
	}
	else if( iHitCount[_enemyIndex] >= _ANNIHILATION_NUM_ )
	{
		iResult = TYPE_VICTORY;
	}
	else if( iHitCount[_playerIndex] < iHitCount[_enemyIndex] )
	{
		iResult = TYPE_SUPERIORITY;
	}
	else
	{
		iResult = TYPE_INFERIORITY;
	}

	return iResult;
}