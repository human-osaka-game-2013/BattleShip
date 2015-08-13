/**
*@file	GameScene.h
*@author	亀田
*/

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include <new>
#include <vector>

#include "SceneInterface.h"
#include "StateManager.h"
#include "StageObject.h"
#include "Player.h"

/**
*@brief	戦闘シーンクラス
*@details	シーン基本クラス(CScene)を派生したクラス。@n
			Init、Control、Draw、Render関数がライブラリのサブルーチン側で呼ばれるので、宣言すること。@n
			今回は2D描画のみの予定なのでRender関数は宣言をしているが、中身はない。
*/


class GameScene : public CScene
{
private:
	StateManager*	m_stateManager;		///<	戦闘内でのステートを管理するオブジェクト
	std::vector<Player*>	m_Player;	///<	プレイヤークラス
	StageObject*	m_pStageObject;		///<	ステージオブジェクト
	int const		m_playerID;			///<	起動側のプレイヤーID

public:
	/**
	*@brief	コンストラクタ
	*@details	使わない管理ポインタがある場合NULLポインタを入れる
	*@param[in]	_id	自分自身のシーンID
	*@param[in]	_playerID	起動側のプレイヤーID
	*@param[in]	_pRenderManager	3D描画管理のポインタ
	*@param[in]	_pDrawManager	2D描画管理のポインタ
	*@param[in]	_pKey			キー管理のポインタ
	*@param[in]	m_pMouse		マウス管理のポインタ
	*/
	GameScene(int _id, int _playerID, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager, CKey* const _pKey, CMouse* const m_pMouse )
		: CScene( _id, _pRenderManager,	_pDrawManager, _pKey, m_pMouse), m_playerID( _id )
	{
		
	}
	/**
	*@brief	デストラクタ
	*/
	~GameScene();

public:
	
	/**
	*@brief	初期化
	*@param[in]	_playerID	起動側のプレイヤーID
	*/
	bool Init();

	/**
	*@brief	ルーチン処理
	*@return 0：シーンに変化無し　
	*/
	int	 Control();

	/**
	*@brief	2D描画
	*/
	void Draw();
	void Render(){};
};

#endif