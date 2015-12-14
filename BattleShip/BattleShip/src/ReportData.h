#ifndef _REPORTDATA_H_
#define _REPORTDATA_H_

#include "Player.h"

#define _REWARD_MAX_	6
#define _SET_REPORTDATA_VAR_VOL_ 10

/**
*@brief	戦績保存クラス
*@details	戦績の評価をするために必要なデータクラス
*/
class ReportData
{
private:
	int		attackCount;
	int		searchCount;
	int		hitCount;
	int		sightCount;
	int		selectAveTime;
	int		turnCount;
	int		damageCount;
	byte	KOFlag;
	float	hitProbability;
	float	sightProbability;

public:
	ReportData()
	{
		searchCount	= 0;
		attackCount	= 0;
		hitCount	= 0;
		sightCount	= 0;
		selectAveTime = 0;
		turnCount	= 0;
		damageCount	= 0;
		KOFlag		= 0x00;
		hitProbability	= 0.f;
		sightProbability= 0.f;
	}

	/**
	*@brief	行動選択までの平均時間
	*/
	void UpdateSelectAveTime( const int _elapsed )
	{
		selectAveTime += _elapsed;
		selectAveTime = selectAveTime/2;
	}
	
	/**
	*@brief	行動選択の回数のカウント更新
	*/
	void UpdateSelectCount( const int _selectType )
	{
		switch( _selectType )
		{
		case 0:	///<攻撃
			attackCount++;
			break;
		case 1: ///<索敵
			searchCount++;
			break;
		}
	}

	/**
	*@brief	戦闘結果の回数のカウント更新
	*/
	void UpdateResultCount( const int _resultPlayer )
	{
		switch( _resultPlayer )
		{
		case 1:	///<発見
			sightCount++;
			sightProbability = sightCount/searchCount;
			sightProbability *= 100.f;
			break;
		case 2: ///<着弾
			hitCount++;
			hitProbability = hitCount/attackCount;
			hitProbability *= 100.f;
			break;
		}
	}

	/**
	*@brief	撃沈フラグの更新
	*@details	撃沈フラグと被弾回数の更新
	*/
	void UpdateKOFlag( Player* const _pPlayer )
	{
		for( int iShip = 0; iShip < ShipObject::TYPE_MAX; iShip++ )
		{
			bool destroyFlag = false;
			byte flagCheck = 0x00;
			destroyFlag = _pPlayer->CheckDestroy(static_cast<ShipObject::_SHIP_TYPE_NUM_>(iShip));
			if( destroyFlag )
			{
				flagCheck = 0x01;
			}
			KOFlag = destroyFlag? (KOFlag | flagCheck<<iShip) : KOFlag;	//駒の撃沈フラグをビット管理し、下位ビットから空母～潜水艦で管理
		}
	}

public:
	inline int GetSearchCount()	{ return searchCount; }
	inline int GetAttackCount()	{ return attackCount; }
	inline int GetHitCount()	{ return hitCount; }
	inline int GetSightCount()	{ return sightCount; }
	inline int GetAveTime()	{ return selectAveTime; }
	inline int GetTurnCount()	{ return turnCount; }
	inline int GetDamageCount()	{ return damageCount; }
	inline byte GetKOFlag()		{ return KOFlag; }
	inline float GetHitProbability(){ return hitProbability; }
	inline float GetSightProbability(){ return sightProbability; }

public:
	inline void SetSearchCount( int _searchCount)	{ searchCount = _searchCount; }
	inline void SetAttackCount( int _attackCount)	{ attackCount = _attackCount; }
	inline void SetHitCount( int _hitCount )		{ hitCount = _hitCount; }
	inline void SetSightCount( int _sightCount )	{ sightCount = _sightCount; }
	inline void SetAveTime( int _aveTime )			{ selectAveTime = _aveTime; }
	inline void SetTurnCount( int _turnCount )		{ turnCount = _turnCount; }
	inline void SetDamageCount( int _damageCount )	{ damageCount = _damageCount; }
	inline void SetKOFlag( byte _koFlag )		{ KOFlag = _koFlag; }
	inline void SetHitProbability( float _hitProbability ){ hitProbability = _hitProbability; }
	inline void SetSightProbability( float _sightProbability){ sightProbability = _sightProbability; }
};

#endif