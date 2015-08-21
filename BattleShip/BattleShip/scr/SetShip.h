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
	int m_SetCount;		///<	駒の配置回数（どれだけ配置しているか）
	
	
public:
	/**
	*@brief	ステートパターン内での初期化
	*/
	bool Init();

	/**
	*@brief	ステートパターン内でのサブルーチン処理
	*/
	bool Control();

	/**
	*@brief	ステートパターン内でのサブルーチン処理
	*/
	void Draw();
	
	/**
	*@brief	ステートパターン内でのサブルーチン処理
	*/
	void ComStandby();

	/**
	*@brief	配置回数の取得
	*/
	int GetSetCount(){ return m_SetCount; }
};

#endif