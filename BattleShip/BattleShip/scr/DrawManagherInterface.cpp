#include "DrawManager.h"

//	�g�p����S�Ẳ摜��ǂݍ���
bool CDrawManagher::AllLoadTexture ()
{
	LoadTexture ( "resource/texture/Logo.png", TEX_TEAM_LOGO, 0, 0, 255 );
	LoadTexture ( "resource/texture/stage1.png", TEX_BACKGROUND, 0, 0, 255 );

	return true;
}
