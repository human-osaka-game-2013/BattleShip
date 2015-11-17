/**
*@file	GameScene.h
*@author	亀田
*/

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "Connect.h"
#include <vector>

#include "SceneInterface.h"
#include "Background.h"
#include "StateManager.h"
#include "StageObject.h"
#include "Player.h"
#include "ScreenMask.h"

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
	int				m_playerID;			///<	起動側のプレイヤーID
	Background		m_background;		///<	背景オブジェクト
	Connect			m_Connect;			///<	通信デバイスクラス
	ScreenMask		m_screenMask;		///<	画面遷移時のフェード用
	
	bool	m_fadeInFlag;		///<ゲーム開始時はフェードインさせる。
	bool	m_fadeOutFlag;		///<ゲーム終了時にフェードアウトさせる。
	bool	m_sendFlagOfStage;	///<ステージ情報送信フラグ
	bool	m_sendFlagOfShips;	///<駒情報送信フラグ
	bool	m_recvFlagOfStage;	///<ステージ情報受信フラグ
	bool	m_recvFlagOfShips;	///<駒情報受信フラグ
	int		m_sendShipCount;	///<駒の情報を送っていた回数

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
		m_playerID = 0;
		m_sendFlagOfStage = false;
		m_sendFlagOfShips = false;
		m_recvFlagOfStage = false;
		m_recvFlagOfShips = false;
		m_sendShipCount = 0;
	}
	
	/**
	*@brief	デストラクタ
	*/
	~GameScene(){
		for( unsigned int iCount = 0; iCount < m_Player.size(); iCount++ ){
			delete m_Player[iCount];
		}
		m_Player.clear();
		
		delete m_pStageObject;
		delete m_stateManager;
	};

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

	/**
	*@brief	ステージ情報通信処理
	*/
	bool ComStageData();

	/**
	*@brief	駒情報通信処理
	*/
	bool ComShipsData();

};

#endif