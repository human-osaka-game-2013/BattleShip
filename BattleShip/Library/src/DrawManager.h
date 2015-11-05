/**
*@file	DrawManage.h
*@author	�T�c
*/

#ifndef _DRAW_MANAGE_H_
#define _DRAW_MANAGE_H_

#include "lib_head.h"
#include "DrawStructList.h"
#include "DirectXFont.h"

// �e�N�X�`���̔ԍ��ƃe�N�X�`���S�̂̏c���̑傫��
struct TEXTUREINFO
{
	// �e�N�X�`���̊i�[�|�C���^
	LPDIRECT3DTEXTURE9	pTexture;

	int		width, height;
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
	_TEX_BLOCKFRAME_,
	_TEX_TABFRAME_,
	_TEX_TITLE_BACK_,
	_TEX_STARTBUTTON_,
	_TEX_TITLEMASK_,
	_TEX_GAMEMASK_,
	_TEX_GAMELOG_,
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
	DirectXFont m_dxFont;	///<DirectFont

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
	/**
	*@brief	��`�`��
	*@details	�O�������`����Ⴄ�ꍇ�̕`��
	*@parap[in] _textuerNumber �e�N�X�`���̔ԍ�
	*@param[in]	_vertex ��`���
	*/
	void VertexDraw( int _textuerNumber, CUSTOMVERTEX (&_vertex)[4] );

	/**
	*@brief	��`�`��
	*@details	����̒��_��̏ꍇ�̕`��
	*@parap[in] _textuerNumber �e�N�X�`���̔ԍ�
	*@param[in]	_fXpos		��`�̍��㒸�_���WX
	*@param[in]	_fYpos		��`�̍��㒸�_���WY
	*@param[in]	_fWidth		��`�̉���
	*@param[in]	_fHeight	��`�̏c��
	*@param[in]	_fTu		��`�̍��㒸�_�e�N�X�`�����WU
	*@param[in]	_fTv		��`�̍��㒸�_�e�N�X�`�����WV
	*@param[in]	_fTu2		��`�̉E�����_�e�N�X�`�����WU
	*@param[in]	_fTv2		��`�̉E�����_�e�N�X�`�����WV
	*/
	void VertexDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
				float _fTu, float _fTv, float _fTu2, float _fTv2);
	
	/**
	*@brief	��`�`��
	*@details	����̒��_��ŃJ���[�l�̕ύX���K�v�ȏꍇ�̕`��
	*@parap[in] _textuerNumber �e�N�X�`���̔ԍ�
	*@param[in]	_fXpos		��`�̍��㒸�_���WX
	*@param[in]	_fYpos		��`�̍��㒸�_���WY
	*@param[in]	_fWidth		��`�̉���
	*@param[in]	_fHeight	��`�̏c��
	*@param[in]	_fTu		��`�̍��㒸�_�e�N�X�`�����WU
	*@param[in]	_fTv		��`�̍��㒸�_�e�N�X�`�����WV
	*@param[in]	_fTu2		��`�̉E�����_�e�N�X�`�����WU
	*@param[in]	_fTv2		��`�̉E�����_�e�N�X�`�����WV
	*@param[in]	_iA			��`�̃J���[�l�i�����x�j
	*@param[in]	_iR			��`�̃J���[�l�i�ԁj
	*@param[in]	_iG			��`�̃J���[�l�i�΁j
	*@param[in]	_iB			��`�̃J���[�l�i�j
	*/
	void VertexDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
					float _fTu, float _fTv, float _fTu2, float _fTv2, int _iA, int _iR, int _iG, int _iB );
	
	/**
	*@brief	���S��̋�`�`��
	*@details	��`�̒��S��̏ꍇ�̕`��
	*@parap[in] _textuerNumber �e�N�X�`���̔ԍ�
	*@param[in]	_fXpos		��`�̒��S���WX
	*@param[in]	_fYpos		��`�̒��S���WY
	*@param[in]	_fWidth		��`�̉���
	*@param[in]	_fHeight	��`�̏c��
	*@param[in]	_fTu1		��`�̍��㒸�_�e�N�X�`�����WU
	*@param[in]	_fTv1		��`�̍��㒸�_�e�N�X�`�����WV
	*@param[in]	_fTu2		��`�̉E�����_�e�N�X�`�����WU
	*@param[in]	_fTv2		��`�̉E�����_�e�N�X�`�����WV
	*/
	void CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fWidth, float _fHeight,
							float _fTu1, float _fTv1, float _fTu2, float _fTv2 );
	
	/**
	*@brief	���S��̋�`�`��
	*@details	��`�̒��S��ŉ�]������K�v������ꍇ�̕`��
	*@parap[in] _textuerNumber �e�N�X�`���̔ԍ�
	*@param[in]	_fXpos		��`�̒��S���WX
	*@param[in]	_fYpos		��`�̒��S���WY
	*@param[in]	_fAngle		��`�̉�]�p�x
	*@param[in]	_fWidth		��`�̉���
	*@param[in]	_fHeight	��`�̏c��
	*@param[in]	_fTu1		��`�̍��㒸�_�e�N�X�`�����WU
	*@param[in]	_fTv1		��`�̍��㒸�_�e�N�X�`�����WV
	*@param[in]	_fTu2		��`�̉E�����_�e�N�X�`�����WU
	*@param[in]	_fTv2		��`�̉E�����_�e�N�X�`�����WV
	*/
	void CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fAngle, float _fWidth, float _fHeight,
							float _fTu1, float _fTv1, float _fTu2, float _fTv2 );
	
	/**
	*@brief	���S��̋�`�`��
	*@details	��`�̒��S��ŃJ���[�l��ύX����ꍇ�̕`��
	*@parap[in] _textuerNumber �e�N�X�`���̔ԍ�
	*@param[in]	_fXpos		��`�̒��S���WX
	*@param[in]	_fYpos		��`�̒��S���WY
	*@param[in]	_fAngle		��`�̉�]�p�x
	*@param[in]	_fWidth		��`�̉���
	*@param[in]	_fHeight	��`�̏c��
	*@param[in]	_fTu1		��`�̍��㒸�_�e�N�X�`�����WU
	*@param[in]	_fTv1		��`�̍��㒸�_�e�N�X�`�����WV
	*@param[in]	_fTu2		��`�̉E�����_�e�N�X�`�����WU
	*@param[in]	_fTv2		��`�̉E�����_�e�N�X�`�����WV
	*@param[in]	_iA			��`�̃J���[�l�i�����x�j
	*@param[in]	_iR			��`�̃J���[�l�i�ԁj
	*@param[in]	_iG			��`�̃J���[�l�i�΁j
	*@param[in]	_iB			��`�̃J���[�l�i�j
	*/
	void CenterDraw ( int _textuerNumber, float _fXpos, float _fYpos, float _fAngle, float _fWidth, float _fHeight,
							float _fTu1, float _fTv1, float _fTu2, float _fTv2, int _iA, int _iR, int _iG, int _iB );

	/**
	*@brief	��`�̍��W�ϊ�
	*@details	���[�J�����W������������`������ŕϊ����s���i���݂͂��łɕ`�������j
	*@parap[in] _textuerNumber �e�N�X�`���̔ԍ�
	*@param[in]	_vertex ��`���
	*@param[in]	_fXpos	��`�̊���WX
	*@param[in]	_fYpos	��`�̊���WY
	*@param[in]	_fScaleX	��`�̊g�kX
	*@param[in]	_fScaleY	��`�̊g�kY
	*@param[in]	_fRotationY	��`�̉�]�p�x
	*/
	void VertexTransform(  int _textuerNumber, CUSTOMVERTEX (&_vertex)[4], float _fPosX, float _fPosY, 
		float _fScaleX, float _fScaleY, float _fRotationZ);

public:
	//	�g�p����S�Ẳ摜��ǂݍ���
	virtual bool AllLoadTexture ();
};

#endif