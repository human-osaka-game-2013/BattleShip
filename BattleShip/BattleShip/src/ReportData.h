#ifndef _REPORTDATA_H_
#define _REPORTDATA_H_

#include "Player.h"

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
	}

	/**
	*@brief	行動選択までの平均時間
	*/
	void SetSelectAveTime( const int _elapsed )
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
			break;
		case 2: ///<着弾
			hitCount++;
			break;
		}
	}

	/**
	*@brief	撃沈フラグの更新
	*@details	撃沈フラグと被弾回数の更新
	*/
	void UpdateKOFlag( Player* const _player )
	{

	}

public:
	inline int GetSearchCount()	{ return searchCount; }
	inline int GetAttackCount()	{ return attackCount; }
	inline int GetHitCount()	{ return hitCount; }
	inline int GetSightCount()	{ return sightCount; }
	inline int GetAveCount()	{ return selectAveTime; }
	inline int GetTurnCount()	{ return turnCount; }
	inline int GetDamageCount()	{ return damageCount; }
	inline byte GetKOFlag()		{ return KOFlag; }

};

#endif