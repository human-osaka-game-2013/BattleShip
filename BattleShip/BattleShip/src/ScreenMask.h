/**
*@file	Background.h
*@author	�T�c
*/

#ifndef _SCREENMASK_H_
#define _SCREENMASK_H_

#include "gameObject.h"
#include "Window.h"

#define _FADE_OUT_TIME_	2
#define _FADE_IN_TIME_	2

/**
*@brief	��ʑJ�ڎ��̃t�F�[�h�p�N���X
*/
class ScreenMask : public CGameObject
{
private:
	float fWidth ,fHeight;
	int iA, iR, iG, iB; 

public:
	/**
	*@brief �R���X�g���N�^
	*/
	ScreenMask() : CGameObject()
	{
		Init();
	}

	/**
	*@breif	�f�X�g���N�^
	*/
	~ScreenMask()
	{

	}

	/**
	*@brief	������
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
	*@brief	�t�F�[�h�A�E�g�֐�
	*@details	255�𒴂��Ă��܂��Ă͂����Ȃ��ׁA255�𒴂��Ȃ��l�ɑ��������Ă��܂��B
				�i255�ɂ�����x�߂Â��΋����I��255�ŌŒ�ɂ��܂��B�j
	*@param[in] _alpha	�������������A���t�@�l
	*@return	�t�F�[�h�A�E�g�̌���
	*@retval false	�܂��t�F�[�h�A�E�g�������Ă��Ȃ��i�A���t�@�l��255�����j
	*@retval true	�t�F�[�h�A�E�g���������i�A���t�@�l��255�ɒB�����j
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
	*@brief	�t�F�[�h�C���֐�
	*@details	0�𒴂��Ă��܂��Ă͂����Ȃ��ׁA0�������Ȃ��l�Ɍ��������Ă��܂��B
				�i0�ɂ�����x�߂Â��΋����I��0�ŌŒ�ɂ��܂��B�j
	*@param[in] _alpha	�������������A���t�@�l
	*@return	�t�F�[�h�C���̌���
	*@retval false	�܂��t�F�[�h�C���������Ă��Ȃ��i�A���t�@�l��0�ȏ�j
	*@retval true	�t�F�[�h�A�E�g���������i�A���t�@�l��0�ɒB�����j
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