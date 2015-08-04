#include "DrawManager.h"

//	g—p‚·‚é‘S‚Ä‚Ì‰æ‘œ‚ğ“Ç‚İ‚İ
bool CDrawManager::AllLoadTexture ()
{
	LoadTexture ( "../texture/sea.png", _TEX_BACKGROUND_, 0, 0, 255 );
	LoadTexture ( "../texture/AirCarrier.png", _TEX_AIRCARRIER_, 0, 0, 255 );
	LoadTexture ( "../texture/BattleShip.png", _TEX_BATTLESHIP_, 0, 0, 255 );
	LoadTexture ( "../texture/Cuiser.png", _TEX_CRUISER_, 0, 0, 255 );
	
	return true;
}
