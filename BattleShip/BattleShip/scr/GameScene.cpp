/**
*@file	GameScene.cpp
*@author	‹T“c
*/

#include "GameScene.h"

GameScene::GameScene( int _id, int _playerID, CRenderManager* const _pRenderManager,
	CDrawManagher*	const _pDrawManager, CKey* const _pKey, CMouse* const m_pMouse )
	: CScene( _id, _pRenderManager,	_pDrawManager, _pKey, m_pMouse), m_playerID( _playerID )
{
	Init();
}

bool GameScene::Init()
{
	m_stateManagher.Init();
}


int GameScene::Control()
{

}

void GameScene::Draw()
{

}