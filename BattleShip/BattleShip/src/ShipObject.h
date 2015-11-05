/**
*@file	ShipObject.h
*@author	亀田
*/

#ifndef _SHIPOBJECT_H_
#define _SHIPOBJECT_H_

#include "gameObject.h"
#include "read_file.h"
#include "BoardOfFrame.h"
#include "StageDefineList.h"
#include "DrawStructList.h"
#include "ConnectStruct.h"

#define _SHIP_INIT_DIR_	CGameObject::CH_UP

/**
*@brief	駒の基底クラス
*/
class ShipObject:public CGameObject, public ReadFile
{
public:
	/**
	*@brief	駒の艦種類列挙
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

	/**
	*@brief	駒の配列種類
	*/
	enum _SHIP_ARRAY_TYPE_
	{
		ARRAY_TYPE_SHIP,
		ARRAY_TYPE_ACTION,
		ARRAY_TYPE_SEARCH,
		ARRAY_TYPE_MOVE,
		ARRAY_TYPE_MAX,
	};

	/**
	*@brief	駒のテーブル情報種類
	*/
	enum _SHIP_TABLE_NUM_
	{
		TABLE_SHIP,
		TABLE_ACTION = _SHIP_ARRAY_INDEX_,
		TABLE_SEARCH = TABLE_ACTION+_SHIP_ARRAY_INDEX_,
		TABLE_MOVE = TABLE_SEARCH+_SHIP_ARRAY_INDEX_,
		TABLE_MAX = TABLE_MOVE+_SHIP_ARRAY_INDEX_
	};

private:
	int m_userID;
	int m_posColumn;
	int m_posLine;

public:
	int m_shipArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の実体配列
	CUSTOMVERTEX	m_vertex[4];	///<	駒の矩形生成時のローカル座標

	int m_actionArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の攻撃範囲配列
	int m_searchArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の索敵範囲配列
	int m_moveArray[_SHIP_ARRAY_INDEX_][_SHIP_ARRAY_INDEX_];	///<	駒の移動範囲配列
	
public:
	/**
	*@brief	コンストラクタ
	*@details	駒配列の初期化とCGameObjectのコンストラクタを呼び出し
	*/
	ShipObject::ShipObject( int _userID ) : CGameObject(){
		for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++ ){
			for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++ )	{
				m_shipArray[iColumn][iLine]=0;
				m_actionArray[iColumn][iLine]=0;
				m_searchArray[iColumn][iLine]=0;
				m_moveArray[iColumn][iLine]=0;
				m_userID = _userID;
			}
		}
		SetDirection( _SHIP_INIT_DIR_ );
	}

	/**
	*@brief	初期化
	*/
	virtual void Init() = 0;

	void Control(){};

	void Draw(){};

	/**
	*@brief	読み取ったデータをテーブルにセット
	*@details	駒データ版
	*/
	void SetTable( char* _p, int _iColumn, int _iLine);

	/**
	*@brief	駒回転処理
	*@param[in]	_array	回転させる配列
	*@param[in] _rotType	回転させる方向。true：右回転, false：左回転。
	*/
	bool RotationShip( int _arrayType, bool _rotType );

	/**
	*@brief	頂点情報の初期化
	*@details	駒の描画はShipObject内の配置情報を頼りにするため、
				通常の描画（中心点or左上基準の矩形生成描画）では出来ないので
				駒ごとに矩形のローカル座標を作ってやる必要がある。
	*/
	void InitVertex( _SHIP_TYPE_NUM_ _shipType );

	/**
	*@brief	解放処理
	*/
	void  Free();

public:
	/**
	*@brief	駒の持ち主ID取得
	*/
	int GetUserID(){ return m_userID; }	

	/**
	*@brief	ステージ上での駒の中心位置のセット
	*/
	void SetArrayPos( int _column, int _line ){ 
		m_posColumn = _column;
		m_posLine	= _line;
	}

	/**
	*@brief	ステージ上での駒の中心位置の取得
	*/
	void GetArrayPos( int& _column, int& _line ){ 
		_column	= m_posColumn;
		_line	= m_posLine;
	}
	/**
	*@brief	ステージ上での駒の中心位置の取得（行）
	*/
	inline int GetArrayColumn(){ return m_posColumn; }
	/**
	*@brief	ステージ上での駒の中心位置の取得（列）
	*/
	inline int GetArrayLine(){ return m_posLine; }

	/**
	*@brief	通信用の構造体に駒データをセット
	*/
	void SetConnectShipData( ConnectShip* _pCShip );

	/**
	*@brief	駒のデータのセット
	*@details	通信クラスから引っ張ってきた駒データを自身の保持してる
				相手側データにセット
	*/
	void SetShipData( ConnectShip* _pCShip );
};


#endif