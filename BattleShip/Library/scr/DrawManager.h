/**
*@file	DrawManage.h
*@author	�T�c
*/

#ifndef _DRAW_MANAGE_H_
#define _DRAW_MANAGE_H_

#include "lib_head.h"

// �e�N�X�`���̔ԍ��ƃe�N�X�`���S�̂̏c���̑傫��
struct TEXTUREINFO
{
	// �e�N�X�`���̊i�[�|�C���^
	LPDIRECT3DTEXTURE9	pTexture;

	int		width, height;
};

// �摜�̒��_���W�Ȃǂ̍\����
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;

	DWORD	color;

	FLOAT	tu, tv;
};


// �g�p����e�N�X�`��
// �g�������e�N�X�`��������Η񋓎q���ɒǉ����Ă���
enum TEXTURES
{

	_TEX_BACKGROUND_,
	_TEX_AIRCARRIER_,
	_TEX_BATTLESHIP_,
	_TEX_CRUISER_,
	_TEX_DESTROYER_,
	_TEX_SUBMARINE_,
	_TEX_STAGEMAP_,
	_TEX_BLOCK_,

	_TEXTURE_MAX_
};

/**
*@brief	2D�`��N���X
*@details	�V�[���Ǘ��N���X�Ɏ��̂��������A�e�V�[���N���X�Ƀ|�C���^��n���B	
*@todo	�A�h���X��const�ɂ���̂͏��߂ĂȂ̂ŁA�C������\��������B
*/
class CDrawManager
{
private:
	TEXTUREINFO m_TextureInfo [_TEXTURE_MAX_];	///<�e�N�X�`�����i�[�z��
	IDirect3DDevice9* const m_pD3Device;		///<D3D�f�o�C�X�|�C���^


public:
	/**
	*@brief	�R���X�g���N�^
	*/
	CDrawManager( IDirect3DDevice9* const _pD3Device);
	/**
	*@brief	�f�X�g���N�^
	*/
	~CDrawManager();

public:
	/**
	*@brief �`��O����
	*param[in] _b3dView�F3D�`��Ȃǂ�����ꍇ�ȂǁA@n
						�`��ݒ�̍Đݒ������ꍇ��true��n���B
	*/
	void BeginDraw ( bool _b3dView = false );

	// �e�N�X�`���̓ǂݍ���
	// ��1�����F("�摜�̖��O.�g���q"), ��2�����F�e�N�X�`���̔ԍ�, ���ߐFRGB 
	bool LoadTexture ( LPCSTR _lpFileName, int _textuerNumber, int _iColorRed, int _iColorGreen, int _iColorBlue );

	// �e�N�X�`���̉��
	// ��1�����F�e�N�X�`���̔ԍ�
	void ReleaseTexture ( int _textuerNumber );
	
	void ReleaseAllTexture ();

public:

	//	(������)�`��
	//	����>1�F�e�N�X�`���̔ԍ� 2,3�F�`��̊�ƂȂ鍶��̓_xy, 4,5�F���_�̏c���� 
	//	6,7�F����uv���W 8,9�F�E��uv���W 
	void VertexDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
				float fTu, float fTv, float fTu2, float fTv2);
	
	//	�F����ς���(������)�`��
	//	����>1�F�e�N�X�`���̔ԍ� 2,3�F�`��̊�ƂȂ鍶��̓_xy, 4,5�F���_�̏c���� 
	//	6,7�F����uv���W 8,9�F�E��uv���W 
	//	������11�`14�F�FARGB�l
	void CustomCorolDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
					float fTu, float fTv, float fTu2, float fTv2, int iA, int iR, int iG, int iB );
	
	//	���S�_����`��
	//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4,5�F�摜�̏c����
	//	������6,7�F�摜�̍����UV���W 8,9:�摜�̉E����UV���W
	void CenterDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
							float fTu1, float fTv1, float fTu2, float fTv2 );
	
	//	���S�_����`�� (��])
	//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4�F�X�������p�x(�X���Ȃ��Ȃ�0��OK) 5,6�F�摜�̏c����
	//	������7,8�F�摜�̍����UV���W 9,10:�摜�̉E����UV���W
	void SpinerDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
							float fTu1, float fTv1, float fTu2, float fTv2 );
	
	//	���S�_����`�� (�F���ω�)
	//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4�F�X�������p�x(�X���Ȃ��Ȃ�0��OK) 5,6�F���_�̏c����
	//	������7,8�F�����UV���W 9,10:�E����UV���W 11�`14�FARGB�l
	void ColorKeyDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
							float fTu1, float fTv1, float fTu2, float fTv2, int iA, int iR, int iG, int iB );
	
	//	���S�_����`�� (�L�k)
	//	������1�F�e�N�X�`���̔ԍ� 2,3�F�L�k�������_X,Y 4�F�p�x 5,6�F�摜�̏c����
	//	������7,8�F�����UV���W 9,10:�E����UV���W 11�`14�FARGB�l
	void ElasticityDraw ( int TextuerNumber, float fXpos, float fYpos, float& fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2, int& iA, int& iR, int& iG, int& iB );


public:
	//	�g�p����S�Ẳ摜��ǂݍ���
	virtual bool AllLoadTexture ();
};

#endif