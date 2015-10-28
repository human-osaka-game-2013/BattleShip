/**
*@file	GameScene.h
*@author	亀田
*/

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "Connect.h"
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
public:
	/**
	*@brief	盤面のフレームオブジェクトクラス
	*/
	class Background : public CGameObject
	{
	private:
		float fWidth ,fHeight;

	public:
		/**
		*@brief	初期化
		*/
		void Init()
		{
			SetPosition(0.f, 0.f, 0.5f);
			fHeight = HEIGHT;
			fWidth = WIDTH;
		}
		void Control(){};
		void Draw(){};
		void Free(){};
		float GetWidth(){ return fWidth; }
		float GetHeight(){ return fHeight; }
	};

private:
	StateManager*	m_stateManager;		///<	戦闘内でのステートを管理するオブジェクト
	std::vector<Player*>	m_Player;	///<	プレイヤークラス
	StageObject*	m_pStageObject;		///<	ステージオブジェクト
	int				m_playerID;			///<	起動側のプレイヤーID
	Background		m_background;		///<	背景オブジェクト
	Connect			m_Connect;			///<	通信デバイスクラス

public:
	/**
	*@brief	コンストラクタ
	*@details	使わない管理ポインタがある場合NULLポインタを入れる
	*@param[in]	_id	自分自身のシーンID
	*@param[in]	_pRenderManager	3D描画管理のポインタ
	*@param[in]	_pDrawManager	2D描画管理のポインタ
	*@param[in]	_pKey			キー管理のポインタ
	*@param[in]	m_pMouse		マウス管理のポインタ
	*/
	GameScene(int _id, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager, CKey* const _pKey, CMouse* const m_pMouse)
		: CScene( _id, _pRenderManager,	_pDrawManager, _pKey, m_pMouse)
	{
		
	}
	
	/**	
	*@brief 解放処理
	*/
	bool Free();

public:
	
	/**
	*@brief	ゲームメインの初期化関数
	*@return	初期化の結果
	*@retval true	成功
	*@retval false	初期化に何らかの失敗があった場合
	*/
	bool Init();

	/**
	*@brief	ゲームメインの基本処理の関数
	*@return	シーン変更をする判断の値
	*@retval 0	シーン変更無し
	*@retval 1	シーン変更有り
	*/
	int	 Control();

	/**
	*@brief	2D描画
	*/
	void Draw();
	void Render(){};

private:
	/**
	*@brief	通信処理
	*@details	Connectクラスメンバを使用して、相手側のデータとのやり取りをここで行う
	*@retval true	正常にデータのやり取りが行われた
	*@retval false	データのやり取りが失敗した
	*/
	bool CommunicationProcessing();
};

#endif