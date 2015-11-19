
#include "Audio.h"

void Audio::LoadAllSoundFile()
{
	LoadSoundFile( "../BattleShip/sound/title.wav",		_TITLE_BGM_ );
	LoadSoundFile( "../BattleShip/sound/game.wav",		_BATTLE_BGM_ );
	LoadSoundFile( "../BattleShip/sound/bf1942.wav",	_WIN_BGM_ );
	LoadSoundFile( "../BattleShip/sound/nicohonsya_explosion.wav", _LOSE_BGM_ );

	LoadSoundFile( "../BattleShip/sound/fire_light.wav",	_FIRE_L_SE_ );
	LoadSoundFile( "../BattleShip/sound/fire_middle.wav",	_FIRE_M_SE_ );
	LoadSoundFile( "../BattleShip/sound/fire_heavy.wav",	_FIRE_H_SE_ );

	LoadSoundFile( "../BattleShip/sound/aircraft.wav",		_AIRCRAFT_SE_ );
	LoadSoundFile( "../BattleShip/sound/air_attack.wav",	_AC_ATTACK_SE_ );
	LoadSoundFile( "../BattleShip/sound/sonar.wav",			_SONAR_SE_ );
	LoadSoundFile( "../BattleShip/sound/water.wav",			_WATER_SE_ );
	LoadSoundFile( "../BattleShip/sound/explosion.wav",		_EXPLOSION_SE_ );
}
