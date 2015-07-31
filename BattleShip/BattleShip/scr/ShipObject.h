/**
*@file	ShipObject.h
*@author	亀田
*/

#ifndef _SHIPOBJECT_H_
#define _SHIPOBJECT_H_

#include "gameObject.h"

#define _SHIP_ARRAY_INDEX_	5	///<	駒の配列指数

/**
*@brief	駒の基底クラス
*/
class ShipObject:public CGameObject
{
public:
	/**
	*@brief	駒の種類列挙
	*/
	enum _SHIP_TYPE_NUM_
	{
		TYPE_NONE=-1,
		TYPE_AIRCARRIER,
		TYPE_BATTLESHIP,
		TYPE_CRUISER,
		TYPE_DESTROYER,
		TYPE_SUBMARINE,
		TYPE_MAX,
	};

private:
	int m_userID;

public:
	int m_shipArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の実体配列
	int m_actionArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の行動範囲配列。攻撃など移動、索敵範囲などに使用

public:
	/**
	*@brief	コンストラクタ
	*@details	駒配列の初期化とCGameObjectのコンストラクタを呼び出し
	*/
	ShipObject::ShipObject():CGameObject(){
		for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn ){
			for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine )	{
				m_shipArray[iColumn][iLine]=0;
				m_actionArray[iColumn][iLine]=0;
			}
		}
	}

	/**
	*@brief	初期化
	*/
	virtual void Init( _SHIP_TYPE_NUM_ _shipType, int _userID ) = 0;

public:
	/**
	*@brief	駒の持ち主ID取得
	*/
	int GetUserID(){ return m_userID; }	
};


#endif