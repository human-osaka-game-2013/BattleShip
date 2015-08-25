#include "DrawManager.h"

//	égópÇ∑ÇÈëSÇƒÇÃâÊëúÇì«Ç›çûÇ›
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
	return true;
}
