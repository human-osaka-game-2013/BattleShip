#ifndef _REPORTDATA_H_
#define _REPORTDATA_H_

#include "Player.h"

#define _REWARD_MAX_	6
#define _SET_REPORTDATA_VAR_VOL_ 10

/**
*@brief	��ѕۑ��N���X
*@details	��т̕]�������邽�߂ɕK�v�ȃf�[�^�N���X
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
	*@brief	�s���I���܂ł̕��ώ���
	*/
	void UpdateSelectAveTime( const int _elapsed )
	{
		selectAveTime += _elapsed;
		selectAveTime = selectAveTime/2;
	}
	
	/**
	*@brief	�s���I���̉񐔂̃J�E���g�X�V
	*/
	void UpdateSelectCount( const int _selectType )
	{
		switch( _selectType )
		{
		case 0:	///<�U��
			attackCount++;
			break;
		case 1: ///<���G
			searchCount++;
			break;
		}
	}

	/**
	*@brief	�퓬���ʂ̉񐔂̃J�E���g�X�V
	*/
	void UpdateResultCount( const int _resultPlayer )
	{
		switch( _resultPlayer )
		{
		case 1:	///<����
			sightCount++;
			sightProbability = sightCount/searchCount;
			sightProbability *= 100.f;
			break;
		case 2: ///<���e
			hitCount++;
			hitProbability = hitCount/attackCount;
			hitProbability *= 100.f;
			break;
		}
	}

	/**
	*@brief	�����t���O�̍X�V
	*@details	�����t���O�Ɣ�e�񐔂̍X�V
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
			KOFlag = destroyFlag? (KOFlag | flagCheck<<iShip) : KOFlag;	//��̌����t���O���r�b�g�Ǘ����A���ʃr�b�g������`�����͂ŊǗ�
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