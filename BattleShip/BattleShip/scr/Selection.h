/**
*@file	Selection.h
*@author	亀田
*/

#ifndef _SELECTION_H_
#define _SELECTION_H_

#include "GameState.h"

#define _TAB_WIDTH_		128.f
#define _TAB_HEIGHT_	(float)_TAB_WIDTH_/3

class Selection : public GameState
{
private:
	bool m_tabSelectFlag;		///< タブを選択しているか
	bool m_areaSelectFlag;		///< 行動別の範囲を選択しているか
	_SELECT_NUM_ m_selectType;	///< 選択した行動の種類
	
	BoardOfFrame m_actionFrame;	///< 攻撃枠
	BoardOfFrame m_searchFrame;	///< 索敵枠
	BoardOfFrame m_moveFrame;	///< 移動枠

	int(*m_tempArray)[_SHIP_ARRAY_INDEX_];	///<どの配列データとのチェックを行うかの格納用

public:
	/**
	*@brief	コンストラクタ
	*@param	_type	現在選択している艦の種類
	*/
	Selection( ShipObject::_SHIP_TYPE_NUM_& _type ): GameState( _type ){}

	/**
	*@brief	戦闘行動選択での初期化
	*/
	bool Init();

	/**
	*@brief	戦闘行動選択でのサブルーチン処理
	*/
	int Control();
	
	/**
	*@brief	戦闘行動選択での描画
	*/
	void Draw();
	
	/**
	*@brief	戦闘行動選択での通信待機処理
	*/
	void ComStandby();

private:

	/**
	*@brief	タブのクリックの判定
	*/
	bool TabCheck();

	/**
	*@brief	行動選択別の配列をセット
	*@details	後にチェックする配列データはタブを選択した際にどれを使うか決まっているため、
				メンバに仮保存する為、ここで一度だけ配列データをセットする。
	*@todo	もし違う行動を選択する場合にはフラグの管理の関係からここはタブを再選択された際に再度通る予定。
	*/
	bool SetTypeArray();

	/**
	*@brief	行動選択時の範囲チェック
	*/
	int SelectArrayCheck();

	/**
	*@brief	タブの情報をリセット
	*@details	主にタブ情報のカラー値をリセット
	*/
	void ResetTabFrame();

};

#endif