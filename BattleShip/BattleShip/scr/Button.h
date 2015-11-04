#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "gameObject.h"

/**
*@brief	簡易なボタンオブジェクト用クラス
*/
class Button: public CGameObject
{
private:
	float fWidth ,fHeight;
	int iA, iR, iG, iB; 
	
public:
	/**
	*@brief コンストラクタ
	*/
	Button() : CGameObject()
	{

	}

	/**
	*@brief	初期化
	*/
	void Init( float _fx, float _fy, float _fWidth, float _fHeight )
	{
		SetPosition(_fx, _fy, 0.5f);
		fHeight = _fHeight;
		fWidth = _fWidth;
		SetColor( 255, 255, 255, 255 );
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

	void SetWidth( const float& _width  ){ fWidth = _width; }
	void SetHeight( const float& _height ){ fHeight = _height; }

	void SetColor( const int& _iA, const int& _iR, const int& _iG, const int& _iB )
	{
		iA = _iA;
		iR = _iR;
		iG = _iG;
		iB = _iB;
	}
	
	/**
	*@brief	当たり判定処理
	*@details	引数内のxy座標が、自身のオブジェクト内に入っているかを判定
	*@param[in]	_x	x座標
	*@param[in]	_y	y座標
	*/
	bool HitBlockCheck( float _x, float _y )
	{
		float tempX = GetPositionX(), tempY = GetPositionY();
		if( tempX < _x && tempX + fWidth > _x )
		{
			if(	tempY < _y && tempY + fHeight > _y )
			{
				return true;
			}
		}
		return false;
	}
};


#endif