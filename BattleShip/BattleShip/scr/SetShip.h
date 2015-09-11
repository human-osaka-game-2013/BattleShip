/**
*@file	SetShip.h
*@author	亀田
*/

#ifndef _SETSHIP_H_
#define _SETSHIP_H_

#include "GameState.h"
#include "Player.h"
#include "StageObject.h"

class SetShip : public GameState
{
private:
	bool m_SetCompFlag;	///<	Control返り値兼、駒の配置完了フラグ
	int	m_SetCount;		///<	駒の配置回数（どれだけ配置しているか）
	
	
public:
	/**
	*@brief	駒配置での初期化
	*/
	bool Init( ShipObject::_SHIP_TYPE_NUM_ _type );

	/**
	*@brief	駒配置でのサブルーチン処理
	*@return	m_SetCount	現在の選択駒が分かれば、結果を受け取ったStateManagerは、@n
				それに応じて違うステートに切り替えたりさせればいい。
	*/
	int Control();

	/**
	*@brief	駒配置でのサブルーチン描画
	*/
	void Draw();
	
	/**
	*@brief	駒配置での通信待機処理
	*/
	void ComStandby();

	
	
private:	
	/**
	*@brief	盤面総チェックのルーチン処理
	*@return	判定結果	0：クリックの判定を通らなかった。@n
				1：マスがすでに埋まっていたorそのマスだと置けない。@n
				2：クリックしたマスに駒を配置出来た。
	*/
	int CheckBoard();

	/**
	*@brief	配置回数の取得
	*/
	int GetSetCount(){ return m_SetCount; }
};

#endif