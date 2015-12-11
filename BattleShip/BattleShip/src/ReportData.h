#ifndef _REPORTDATA_H_
#define _REPORTDATA_H_

#include "Player.h"

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
	*@brief	�s���I���܂ł̕��ώ���
	*/
	void SetSelectAveTime( const int _elapsed )
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