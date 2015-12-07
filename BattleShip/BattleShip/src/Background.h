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
	*@breif	デストラクタ
	*/
	~Background(){
	
	}

	/**
	*@brief	初期化
	*/
	void Init( float _x = 0.f, float _y = 0.f, float _w =WIDTH, float _h = HEIGHT )
	{
		SetPosition(_x, _y, 0.5f);
		fWidth = _w;
		fHeight = _h;
	}
	void Control(){};
	void Draw(){};
	float GetWidth(){ return fWidth; }
	float GetHeight(){ return fHeight; }
};


#endif