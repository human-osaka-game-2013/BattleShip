/**
*@file	BoardOfFrame.h
*@author	亀田
*/

#ifndef _BOARDOFFRAME_H_
#define _BOARDOFFRAME_H_

#include "gameObject.h"

/**
*@brief	盤面のフレームオブジェクトクラス（描画用）
*@details	ステージのUI要素などを別のクラスとして持たせる。@n
			ステージやプレイヤー情報は必要に応じてメンバからもらう。
*/
class BoardOfFrame : public CGameObject
{
private:
	float fWidth ,fHeight;
	int iA, iR, iG, iB; 
	
public:
	/**
	*@brief	コンストラクタ
	*/
	BoardOfFrame() : CGameObject()
	{

	}

	/**
	*@breif	デストラクタ
	*/
	~BoardOfFrame()
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
	}
	void Control(){};
	void Draw(){};
	
	inline float GetWidth(){ return fWidth; }
	inline float GetHeight(){ return fHeight; }

	inline int GetAlpha()	{ return iA; }
	inline int GetRed()		{ return iR; }
	inline int GetGreen()	{ return iG; }
	inline int GetBlue()	{ return iB; }

	void SetColor( int _iA, int _iR, int _iG, int _iB )
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