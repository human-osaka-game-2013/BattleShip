/**
*@file	Background.h
*@author	亀田
*/

#ifndef _SCREENMASK_H_
#define _SCREENMASK_H_

#include "gameObject.h"
#include "Window.h"

/**
*@brief	画面遷移時のフェード用クラス
*/
class ScreenMask : public CGameObject
{
private:
	float fWidth ,fHeight;
	int iA, iR, iG, iB; 

public:
	/**
	*@brief コンストラクタ
	*/
	ScreenMask() : CGameObject()
	{
		Init();
	}

	/**
	*@brief	初期化
	*/
	void Init()
	{
		SetPosition(0.f, 0.f, 0.5f);
		fHeight = HEIGHT;
		fWidth = WIDTH;
		SetColor( 0, 255, 255, 255 );
	}
	void Control(){};
	void Draw(){};
	void Free(){};
	inline float GetWidth(){ return fWidth; }
	inline float GetHeight(){ return fHeight; }

	inline int GetAlpha()	{ return iA; }
	inline int GetRed()		{ return iR; }
	inline int GetGreen()	{ return iG; }
	inline int GetBlue()	{ return iB; }

	void GetColor( int& _iA, int& _iR, int& _iG, int& _iB )
	{
		_iA = iA;
		_iR	= iR;
		_iG	= iG;
		_iB	= iB;
	}

	void SetColor( const int& _iA, const int& _iR, const int& _iG, const int& _iB )
	{
		iA = _iA;
		iR = _iR;
		iG = _iG;
		iB = _iB;
	}

	bool FadeOut( const int _subAlpha )
	{
		bool result = false;

		if( iA + _subAlpha <= 255 )
		{
			iA += _subAlpha;
		}
		else
		{
			result = true;
		}
		return result;
	}
	
};


#endif