#include "DrawManager.h"

//	égópÇ∑ÇÈëSÇƒÇÃâÊëúÇì«Ç›çûÇ›
bool CDrawManager::AllLoadTexture ()
{
	LoadTexture ( "../BattleShip/texture/sea.png", _TEX_BACKGROUND_,		0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/AirCarrier.png", _TEX_AIRCARRIER_, 0, 0, 255 );
	LoadTexture ( "../BattleShip/texture/BattleShip.png", _TEX_BATTLESHIP_, 0, 0, 255 );
	LoadTexture ( "../BattleShip/texture/Cuiser.png", _TEX_CRUISER_,		0, 0, 255 );
	LoadTexture ( "../BattleShip/texture/Destroyer.png", _TEX_DESTROYER_,	0, 0, 255 );
	LoadTexture ( "../BattleShip/texture/Submarine.png", _TEX_SUBMARINE_,	0, 0, 255 );
	LoadTexture ( "../BattleShip/texture/StageMap.png", _TEX_STAGEMAP_,		0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/Block.png", _TEX_BLOCK_,			0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/BlockFrame.png", _TEX_BLOCKFRAME_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/tab_1.png", _TEX_TABFRAME_,		0, 255, 255 );
	
	LoadTexture ( "../BattleShip/texture/Title.png", _TEX_TITLE_MAIN_,		0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/TitleBack.bmp", _TEX_TITLE_BACK_,	0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/rudderBB.bmp", _TEX_TITLE_RUDDER_,	0, 0, 255 );
	LoadTexture ( "../BattleShip/texture/TitleMask.bmp", _TEX_TITLEMASK_,	0, 255, 255 );

	LoadTexture ( "../BattleShip/texture/GameMask.bmp", _TEX_GAMEMASK_,		0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/GameLog.bmp", _TEX_GAMELOG_,		0, 255, 255 );
	LoadTexture ( "../BattleShip/texture/RewardFrame.bmp", _TEX_REWARDFRAME_,	0, 0, 255 );
	LoadTexture ( "../BattleShip/texture/RewardMap.bmp", _TEX_REWARDMAP_,	0, 0, 255, 4, 4);
	
	LoadTexture ( "../BattleShip/texture/ButtonMap.bmp", _TEX_BUTTONMAP_,	0, 0, 255, 2, 4);
	LoadTexture ( "../BattleShip/texture/EffectMap1.bmp", _TEX_EFFECTMAP1_,	0, 0, 255, 10, 2);
	LoadTexture ( "../BattleShip/texture/EffectMap2.bmp", _TEX_EFFECTMAP2_,	0, 0, 255, 1, 4);
	
	return true;
}
