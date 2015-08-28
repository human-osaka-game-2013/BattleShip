

#ifndef _BOARDOFFRAME_H_
#define _BOARDOFFRAME_H_

#include "gameObject.h"
#include "DrawManager.h"
/**
*@brief	�Ֆʂ̃t���[���I�u�W�F�N�g�N���X�i�`��p�j
*@details	�X�e�[�W��UI�v�f�Ȃǂ�ʂ̃N���X�Ƃ��Ď�������B@n
			�X�e�[�W��v���C���[���͕K�v�ɉ����ă����o������炤�B
*/
class BoardOfFrame : public CGameObject
{
private:
	float fWidth ,fHeight;

public:
	/**
	*@brief	������
	*/
	void Init( float _fx, float _fy, float _fWidth, float _fHeight )
	{
		SetPosition(_fx, _fy, 0.5f);
		fHeight = _fHeight;
		fWidth = _fWidth;
	}
	void Control(){};
	void Draw(){};
	void Free(){};
	float GetWidth(){ return fWidth; }
	float GetHeight(){ return fHeight; }

	/**
	*@brief	�����蔻�菈��
	*@details	��������xy���W���A���g�̃I�u�W�F�N�g���ɓ����Ă��邩�𔻒�
	*@param[in]	_x	x���W
	*@param[in]	_y	y���W
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