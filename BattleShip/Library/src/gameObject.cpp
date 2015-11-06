/*
	gameObject.cpp
	CGameObject�N���X�̃����o�֐�

*/

#include "gameObject.h"

/*
	�R���X�g���N�^
	@param	CTexture�N���X�I�u�W�F�N�g
	@return	�Ȃ�
*/
CGameObject::CGameObject()	
	: m_posX( 0.f ), m_posY( 0.f ), m_posZ( 0.f ),
	  m_Dir( CH_NONE ), m_State( STATE_NONE ), m_deadFlag( true ), m_id(0)
{

}

/**
*@breif	�f�X�g���N�^
*/
CGameObject::~CGameObject()
{

}


//--------------------------------------------------------
//	�A�N�Z�b�T
//--------------------------------------------------------
/*
	���W�iX,Y�j���Z�b�g
	@param	���W���
	@return	�Ȃ�
*/
void CGameObject::SetPosition ( float _x, float _y, float _z )
{
	m_posX = _x;
	m_posY = _y;
	m_posZ = _z;
}


/*
	���W���iX,Y�j�̎擾
	@param	���WX,���WY
	@return	�Ȃ�
*/
void CGameObject::GetPosition ( float* p_x, float* p_y )
{
	*p_x = m_posX;
	*p_y = m_posY;
}

/*
	�����蔻��
	@param	��,��,�E,��
	@return	���ʁF���������itrue�j,�������ĂȂ��ifalse�j
*/
bool CGameObject::HitCheck( float _left, float _top, float _right, float _bottom )	
{
	if( _left < m_posX && _right > m_posX )
	{
		if( _top > m_posY && _bottom < m_posY )
		{
			return true;
		}
	}
	return false;
}
