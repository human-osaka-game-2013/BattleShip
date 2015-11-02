/**
*@file	Background.h
*@author	亀田
*/

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "gameObject.h"
#include "Window.h"

/**
*@brief	背景オブジェクトクラス
*/
class Background : public CGameObject
{
private:
	float fWidth ,fHeight;

public:
	/**
	*@brief	コンストラクタ
	*/
	Background() : CGameObject()
	{

	}

	/**
	*@brief	初期化
	*/
	void Init()
	{
		SetPosition(0.f, 0.f, 0.5f);
		fHeight = HEIGHT;
		fWidth = WIDTH;
	}
	void Control(){};
	void Draw(){};
	void Free(){};
	float GetWidth(){ return fWidth; }
	float GetHeight(){ return fHeight; }
};


#endif