/**
*@file	StageObject.h
*@author	亀田
*/

#ifndef _STAGEOBJECT_H_
#define _STAGEOBJECT_H_

#include "gameObject.h"
#include "ShipObject.h"

#define _STAGE_COLUMN_MAX_ 10	///<	ステージの行数
#define _STAGE_LINE_MAX_	10	///<	ステージの列数

#define _PLAYER_NUM_ 2

class StageObject : public CGameObject
{
public:
	unsigned char m_stageArray[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];

public:
	/**
	*@brief	コンストラクタ
	*/
	StageObject::StageObject() : CGameObject(){
		for( int iColumn = 0; iColumn < _STAGE_COLUMN_MAX_; iColumn++ ){
			for( int iLine = 0; iLine < _STAGE_LINE_MAX_; iLine++ )	{
				m_stageArray[0][iColumn][iLine] = 0;	///<	プレイヤー1のステージデータ初期化
				m_stageArray[1][iColumn][iLine] = 0;	///<	プレイヤー2のステージデータ初期化
			}
		}
	}

	bool Init();

	void Control(){};

	void Draw(){};

	bool HitStageCheck();
	
	void SetShip( ShipObject* _pShip );
};

#endif