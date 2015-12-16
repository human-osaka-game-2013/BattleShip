#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "gameObject.h"
#include "Audio.h"

/**
*@brief	簡易なボタンオブジェクト用クラス
*/
class Button: public CGameObject
{
public:
	enum BUTTON_STATE
	{
		STATE_OFF_CURSOR,
		STATE_ON_CURSOR,		
		STATE_SELECT
	};

private:
	float defaultPosX, defaultPosY;		///< ボタンの初期基準位置
	float selectVol;					///< ボタンの（選択時の）拡大率
	float defaultWidth, defaultHeight;	///< ボタンの初期基準幅高さ
	float fWidth ,fHeight;
	int iA, iR, iG, iB;
	BUTTON_STATE m_state;
	Audio*	m_pAudio;

public:
	/**
	*@brief コンストラクタ
	*/
	Button() : CGameObject()
	{
		m_state = STATE_OFF_CURSOR;
	}

	/**
	*@breif	デストラクタ
	*/
	~Button()
	{

	}

	/**
	*@brief	初期化
	*/
	void Init( float _fx, float _fy, float _fWidth, float _fHeight,  Audio* const _pAudio, float _selectVol = 2.f )
	{
		SetPosition(_fx, _fy, 0.5f);
		selectVol = _selectVol;
		defaultPosX = _fx;
		defaultPosY = _fy;
		
		defaultWidth = _fWidth;
		defaultHeight= _fHeight;
		
		fWidth = _fWidth;
		fHeight = _fHeight;
		
		SetColor( 255, 255, 255, 255 );
		SetAudioPtr( _pAudio );
	}

	void Control(){};
	/**
	*@brief	ボタンのルーチン処理
	*@param[in] _x	カーソル位置X
	*@param[in] _y	カーソル位置Y
	*@param[in] _state	カーソル（orキー）の状態
	*/
	char Contorl( const float _x, const float _y, const char _inputState );

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

	inline char GetState(){ return static_cast<char>(m_state); }

	inline void SetWidth( const float& _width  ){ fWidth = _width; }
	inline void SetHeight( const float& _height ){ fHeight = _height; }

	void SetColor( const int& _iA, const int& _iR, const int& _iG, const int& _iB )
	{
		iA = _iA;
		iR = _iR;
		iG = _iG;
		iB = _iB;
	}

	void SetState( const BUTTON_STATE _state ){ m_state = _state; }

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

	void SetAudioPtr( Audio* const _pAudio ){ m_pAudio = _pAudio; }
};


#endif