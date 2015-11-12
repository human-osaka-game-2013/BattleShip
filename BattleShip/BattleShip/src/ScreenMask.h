/**
*@file	Background.h
*@author	亀田
*/

#ifndef _SCREENMASK_H_
#define _SCREENMASK_H_

#include "gameObject.h"
#include "Window.h"

#define _FADE_OUT_TIME_	2
#define _FADE_IN_TIME_	2

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
	*@breif	デストラクタ
	*/
	~ScreenMask()
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
		SetColor( 0, 255, 255, 255 );
	}

	void Control(){};
	void Draw(){};
	
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

	/**
	*@brief	フェードアウト関数
	*@details	255を超えてしまってはいけない為、255を超えない様に増加させています。
				（255にある程度近づけば強制的に255で固定にします。）
	*@param[in] _alpha	増加させたいアルファ値
	*@return	フェードアウトの結果
	*@retval false	まだフェードアウトしきっていない（アルファ値が255未満）
	*@retval true	フェードアウトしきった（アルファ値を255に達した）
	*/
	bool FadeOut( const int _alpha = _FADE_OUT_TIME_ )
	{
		bool result = false;

		if( iA + _alpha < 255 )
		{
			iA += _alpha;
		}
		else
		{
			iA = 255;
			result = true;
		}
		return result;
	}
	
	/**
	*@brief	フェードイン関数
	*@details	0を超えてしまってはいけない為、0を下回らない様に減少させています。
				（0にある程度近づけば強制的に0で固定にします。）
	*@param[in] _alpha	減少させたいアルファ値
	*@return	フェードインの結果
	*@retval false	まだフェードインしきっていない（アルファ値が0以上）
	*@retval true	フェードアウトしきった（アルファ値が0に達した）
	*/
	bool FadeIn( const int _alpha = _FADE_IN_TIME_ )
	{
		bool result = false;

		if( iA - _alpha > 0 )
		{
			iA -= _alpha;
		}
		else
		{
			iA = 0;
			result = true;
		}
		return result;
	}

};


#endif