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
	LoadTexture ( "../BattleShip/texture/tab_1.png", _TEX_TABFRAME_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/Title.jpg", _TEX_TITLE_BACK_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/start.bmp", _TEX_STARTBUTTON_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/TitleMask.bmp", _TEX_TITLEMASK_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/GameMask.bmp", _TEX_GAMEMASK_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/GameLog.bmp", _TEX_GAMELOG_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/FireBB.bmp", _TEX_FIRE_EFFECT_,	0, 0, 255 , 10);
	LoadTexture ( "../BattleShip/texture/ExplosionBB.bmp", _TEX_EXPLOSION_EFFECT_,	0, 0, 255, 8 );
	LoadTexture ( "../BattleShip/texture/SearchBB.bmp", _TEX_SEARCH_EFFECT_,	0, 0, 255 );
	LoadTexture ( "../BattleShip/texture/ReconBB.bmp", _TEX_RECON_,	0, 0, 255 );
	return true;
}
