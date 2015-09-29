/**
*@file	StageObject.h
*@author	亀田
*/

#ifndef _STAGEOBJECT_H_
#define _STAGEOBJECT_H_

#include "StageDefineList.h"
#include "ShipObject.h"
#include "BoardOfFrame.h"

#define _PLAYER_NUM_ 2

/**
*@brief	ステージオブジェクトクラス
*@details	ゲーム中のステージを管理するクラス
*/
class StageObject : public CGameObject
{
public:
	/*
	*@brief	ステージの配列データの種類の列挙（選択など）
	*@details	盤面のマスが選択されているかや、行動可能範囲などの種類の列挙。
				索敵や攻撃位置の情報もこちらで管理する。
	*/
	enum _ARRAY_DATA_TYPE_SELECT_
	{
		_SELECT_NOMAL_,	///<選択されていない
		_SELECT_TRUE_,	///<選択されている
		_SELECT_FALSE_,	///<選択出来ない
		_SEARCH_NOMAL_,	///<索敵をする範囲
		_SEARCH_ALL_,	///<索敵をする範囲（全ての艦）
		_ACTION_NOMAL_,	///<攻撃する範囲
		_ACTION_ALL_	///<攻撃する範囲（全ての艦）
	
	};
	
	/*
	*@brief	ステージの配列データの種類の列挙（損害状況）
	*@details	盤面のマスの駒があるかどうかは、ステージでは2桁目が0の時点で駒は存在しないはずです。
	*/
	enum _ARRAY_DATA_TYPE_CONDITION_
	{
		_CONDITION_NONE_,	///<駒が無い
		_CONDITION_NOMAL_,	///<駒がある
		_CONDITION_DAMAGE_	///<駒が損傷している
	};


public:
	int				m_stageArray[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<ステージ上の情報
	BoardOfFrame	m_stageBlock[_PLAYER_NUM_][_STAGE_COLUMN_MAX_][_STAGE_LINE_MAX_];	///<ステージブロックの座標

public:
	/**
	*@brief	コンストラクタ
	*/
	StageObject() : CGameObject(){
			
	}

	bool Init();

	void Control(){};

	void Draw(){};

	/**
	*@brief	ステージブロックのチェック(駒との判定)
	*@param[in]	_player	プレイヤーのID
	*@param[in]	_column	行
	*@param[in]	_line	列
	*@param[in]	_ship	指定したブロック中心に比較する駒のポインタ
	*@param[in] _arrayType	チェックする配列のタイプ（ShipObject::_SHIP_ARRAY_TYPE_から）
	*@param[in]	_shipNum	自分自身の駒に接触していた場合
	*@return	0：ステージ上の指定範囲とブロックの実体が接触していない場合。@n
				1：ステージ外にブロックの実体があった場合。@n
				2：指定したブロックの範囲にすでにステージ上で何かが存在していた場合。@n
				-1：上記以外の事が発生した場合。
	*/
	int CheckStageBlock( int _player, const int _column, const int _line, ShipObject* _ship,  
							ShipObject::_SHIP_ARRAY_TYPE_ _arrayType, const int _shipNum );
	
	/**
	*@brief	あるステージ上の範囲と画面上の座標XYとの判定
	*@details	主に画面上の座標が指しているブロックの中身を調べる。@n
	*@todo		今回は移動可能範囲を指している場合を調べるための関数として作りました。
	*@param[out] _column	指している座標の行の値
	*@param[out] _line		指している座標の列の値	
	*@param[in]	_player	プレイヤーのID
	*@param[in]	_x		画面上の調べたい座標X
	*@param[in]	_y		画面上の調べたい座標Y
	*@param[in]	_ship	範囲の中心となる駒オブジェクトのポインタ
	*@param[in] _arrayType	チェックする配列のタイプ（ShipObject::_SHIP_ARRAY_TYPE_から）
	*@return	0：選択されていないブロックを指している場合。@n
				1：選択可能ブロックを指している場合。@n
				2：選択不可能ブロックを指している場合。@n
				-1：上記以外の事が発生した場合（またはそもそもブロックに接触していない場合）。
	*/
	int CheckRangeOnStage( int& _column, int& _line, 
							int _player, const float _x, const float _y, ShipObject* _ship, ShipObject::_SHIP_ARRAY_TYPE_ _arrayType );

	/**
	*@brief		ステージブロックと指定範囲のセット
	*@details	駒中心に配列範囲を重ねあわせて、その指定範囲とステージとの判定に応じて
				範囲情報をステージにセットする。@n
	*@todo		この関数は移動範囲のチェックを行う為に作ったもの。出来ることならすでにある関数で代用したい。
	*@param[in]	_player	プレイヤーのID
	*@param[in]	_ship	配列範囲の中心とする為の駒のポインタ
	*@param[in] _tempArray	配列範囲
	*@param[in]	_shipNum	自分自身の駒に接触していた場合判定を取らないようにする
	*@return	true：範囲セットが成功
				false：範囲セットが失敗した場合。
	*/
	bool SetStageToRange( int _player, ShipObject* _ship, 
		const int(*_array)[_SHIP_ARRAY_INDEX_], const int _shipNum );

	/**
	*@brief	ステージブロックへ駒情報をセット
	*@param[in]	_player	プレイヤーのID
	*@param[in]	_column	行
	*@param[in]	_line	列
	*@param[in]	_ship	指定したブロック中心にセットする駒のポインタ
	*@return	false：何らかの原因でセットが失敗。@n
				true：無事に情報をセット完了。
	*/
	bool SetShip( int _player, const int _column, const int _line, ShipObject* _ship );

	/**
	*@brief	ステージブロックへ指定範囲情報をセット（1マスのみ）
	*@details	1マスのみステージブロックの3桁目に情報（_ARRAY_DATA_TYPE_SELECT_）をセットする
	*@param[in]	_player	プレイヤーのID
	*@param[in]	_column	行
	*@param[in]	_line	列
	*@param[in]	_setType	範囲情報を何の値でセットするか
	*@return	false：何らかの原因でセットが失敗。@n
				true：無事に情報をセット完了。
	*/
	bool SetRange( int _player, const int _column, const int _line, const _ARRAY_DATA_TYPE_SELECT_ _setType );

	/**
	*@brief	ステージブロックへ指定範囲情報をセット
	*@details	_arrayの範囲でデータを_selectNumの内容に応じてステージにセット。
				現在は索敵or攻撃の情報をセットする専用
	*@param[in]	_player	プレイヤーのID
	*@param[in]	_column	行
	*@param[in]	_line	列
	*@param[in]	_array	指定したブロック中心にセットする配列情報
	*@param[in]	_selectNum	範囲情報を何の値でセットするか
	*@return	false：何らかの原因でセットが失敗。@n
				true：無事に情報をセット完了。
	*/
	bool SetRange( int _player, const int _column, const int _line, 
					const int(*_array)[_SHIP_ARRAY_INDEX_], const int _selectNum );

	/**
	*@brief	ステージブロックへ指定範囲情報をセット
	*@details	_arrayの範囲でデータを_setTypeで3桁目にステージにセット
	*@param[in]	_player	プレイヤーのID
	*@param[in]	_column	行
	*@param[in]	_line	列
	*@param[in]	_array	指定したブロック中心にセットする配列情報
	*@param[in]	_setType	範囲情報を何の値でセットするか
	*@return	false：何らかの原因でセットが失敗。@n
				true：無事に情報をセット完了。
	*/
	bool SetRange( int _player, const int _column, const int _line, const int(*_array)[_SHIP_ARRAY_INDEX_], 
					const _ARRAY_DATA_TYPE_SELECT_ _setType );


	/**
	*@brief	ステージブロックへ駒情報を再配置
	*@param[in]	_player	プレイヤーのID
	*@param[in]	_column	行
	*@param[in]	_line	列
	*@param[in]	_ship	指定したブロック中心にセットする駒のポインタ
	*@param[in]	_shipNum	自分自身の駒に接触していた場合判定を取らないようにする
	*@return	false：何らかの原因でセットが失敗。@n
				true：無事に情報をセット完了。
	*/
	bool RelocationShip( int _player, const int _column, const int _line, ShipObject* _ship, const int _shipNum );

	/**
	*@brief	ステージブロックの選択状態を解除
	*/
	void ResetSelect();

	/**
	*@brief	解放処理
	*/
	void  Free();
};

#endif