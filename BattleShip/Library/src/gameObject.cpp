/*
	gameObject.cpp
	CGameObjectクラスのメンバ関数

*/

#include "gameObject.h"

/*
	コンストラクタ
	@param	CTextureクラスオブジェクト
	@return	なし
*/
CGameObject::CGameObject()	
	: m_posX( 0.f ), m_posY( 0.f ), m_posZ( 0.f ),
	  m_Dir( CH_NONE ), m_State( STATE_NONE ), m_deadFlag( true ), m_id(0)
{

}

/**
*@breif	デストラクタ
*/
CGameObject::~CGameObject()
{

}


//--------------------------------------------------------
//	アクセッサ
//--------------------------------------------------------
/*
	座標（X,Y）をセット
	@param	座標情報
	@return	なし
*/
void CGameObject::SetPosition ( float _x, float _y, float _z )
{
	m_posX = _x;
	m_posY = _y;
	m_posZ = _z;
}


/*
	座標情報（X,Y）の取得
	@param	座標X,座標Y
	@return	なし
*/
void CGameObject::GetPosition ( float* p_x, float* p_y )
{
	*p_x = m_posX;
	*p_y = m_posY;
}

/*
	当たり判定
	@param	左,上,右,下
	@return	結果：当たった（true）,当たってない（false）
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
