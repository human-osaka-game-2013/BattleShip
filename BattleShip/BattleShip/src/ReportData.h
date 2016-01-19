#ifndef _REPORTDATA_H_
#define _REPORTDATA_H_

#include "Player.h"

/**
*@brief	��ѕۑ��N���X
*@details	�퓬���ɐ�є���ɕK�v�ȃf�[�^�����W����N���X
*/
class ReportData {
 public:
	ReportData() {
		searchCount	= 0;
		attackCount	= 0;
		hitCount	= 0;
		sightCount	= 0;
		selectAveTime = 0;
		turnCount	= 0;
		damageCount	= 0;
		KOCount		= 0;
	}

	/**
	*@brief	�s���I���܂ł̕��ώ���
	*/
	void UpdateSelectAveTime( const int _elapsed ) {
		if (selectAveTime == 0) {
			selectAveTime = _elapsed;
		}else {
			selectAveTime += _elapsed;
			selectAveTime = selectAveTime/2;
		}
	}
	
	/**
	*@brief	�s���I���̉񐔂̃J�E���g�X�V
	*/
	void UpdateSelectCount( const int _selectType ) {
		switch (_selectType) {
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
	void UpdateResultCount( const int _result ) {
		switch (_result) {
		case 1:	///<����
			sightCount++;
			
			break;
		case 2: ///<���e
			hitCount++;
			
			break;
		}
	}

	/**
	*@brief	�����t���O�̍X�V
	*@details	�����t���O�Ɣ�e�񐔂̍X�V
	*/
	void UpdateKOCount( Player* const _pPlayer ) {
		int hitCheckCount = 0;
		bool destroyFlag = false;
		for ( int iShip = 0; iShip < ShipObject::TYPE_MAX; iShip++ ) {			
			destroyFlag = _pPlayer->CheckDestroy(static_cast<ShipObject::_SHIP_TYPE_NUM_>(iShip));
			if (destroyFlag) {
				KOCount++;
			}
			hitCheckCount+=_pPlayer->CheckHitCount(static_cast<ShipObject::_SHIP_TYPE_NUM_>(iShip));
		}
		SetDamageCount(hitCheckCount);
	}

	inline int GetSearchCount()	{ return searchCount; }
	inline int GetAttackCount()	{ return attackCount; }
	inline int GetHitCount()	{ return hitCount; }
	inline int GetSightCount()	{ return sightCount; }
	inline int GetAveTime()	{ return selectAveTime; }
	inline int GetTurnCount()	{ return turnCount; }
	inline int GetDamageCount()	{ return damageCount; }
	inline unsigned char GetKOCount() { return KOCount; }
	
	inline float GetHitProbability() {
		float hitProbability = 0.f;
		hitProbability = (static_cast<float>(hitCount)/static_cast<float>(attackCount))*100.f;
		return hitProbability; 
	}
	
	inline float GetSightProbability() {
		float sightProbability = 0.f;
		sightProbability = (static_cast<float>(sightCount)/static_cast<float>(searchCount))*100.f;
		return sightProbability; 
	}

	inline void SetSearchCount( int _searchCount)	{ searchCount = _searchCount; }
	inline void SetAttackCount( int _attackCount)	{ attackCount = _attackCount; }
	inline void SetHitCount( int _hitCount )		{ hitCount = _hitCount; }
	inline void SetSightCount( int _sightCount )	{ sightCount = _sightCount; }
	inline void SetAveTime( int _aveTime )			{ selectAveTime = _aveTime; }
	inline void SetTurnCount( int _turnCount )		{ turnCount = _turnCount; }
	inline void SetDamageCount( int _damageCount )	{ damageCount = _damageCount; }
	inline void SetKOCount( unsigned char _koFlag )		{ KOCount = _koFlag; }

 private:
	int		attackCount;
	int		searchCount;
	int		hitCount;
	int		sightCount;
	int		selectAveTime;
	int		turnCount;
	int		damageCount;
	unsigned char	KOCount;

};

#endif