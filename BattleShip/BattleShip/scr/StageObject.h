#ifndef _STAGEOBJECT_H_
#define _STAGEOBJECT_H_

#include "gameObject.h"

#define _STAGE_COLUMN_MAX_ 10	///<	ステージの行数
#define _STAGE_LINE_MAX_	10	///<	ステージの列数

#define _PLAYER_NUM_ 2

class StageObject : public CGameObject
{
public:
	unsigned char m_stageArray[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];

public:
	bool Init();

	void Control(){};

	void Draw(){};

	bool HitStageCheck();
	
	void SetShip( ShipObject* _pShip );
};

#endif