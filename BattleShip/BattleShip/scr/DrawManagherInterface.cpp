#include "DrawManager.h"

//	�g�p����S�Ẳ摜��ǂݍ���
bool CDrawManager::AllLoadTexture ()
{
	LoadTexture ( "../BattleShip/texture/sea.png", _TEX_BACKGROUND_, 0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/AirCarrier.png", _TEX_AIRCARRIER_, 0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/BattleShip.png", _TEX_BATTLESHIP_, 0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/Cuiser.png", _TEX_CRUISER_, 0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/Destroyer.png", _TEX_DESTROYER_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/Submarine.png", _TEX_SUBMARINE_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/StageMap2.png", _TEX_STAGEMAP_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/Block.png", _TEX_BLOCK_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/BlockFrame.png", _TEX_BLOCKFRAME_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/tab_1.png", _TEX_TABFRAME_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/Title.jpg", _TEX_TITLE_BACK_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/start.bmp", _TEX_STARTBUTTON_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/TitleMask.bmp", _TEX_TITLEMASK_,	0, 255, 255 );
	
	return true;
}
