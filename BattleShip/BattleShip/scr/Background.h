/**
*@file	Background.h
*@author	�T�c
*/

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "gameObject.h"

/**
*@brief	�Ֆʂ̃t���[���I�u�W�F�N�g�N���X
*/
class Background : public CGameObject
{
private:
	float fWidth ,fHeight;

public:
	/**
	*@brief	������
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