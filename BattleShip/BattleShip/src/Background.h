/**
*@file	Background.h
*@author	�T�c
*/

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "gameObject.h"
#include "Window.h"

/**
*@brief	�w�i�I�u�W�F�N�g�N���X
*/
class Background : public CGameObject
{
private:
	float fWidth ,fHeight;

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	Background() : CGameObject()
	{

	}

	/**
	*@breif	�f�X�g���N�^
	*/
	~Background(){
	
	}

	/**
	*@brief	������
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