/**
*@file	TitleScene.h
*@author	亀田
*/

#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "SceneInterface.h"
#include "Background.h"
#include "ScreenMask.h"
#include "ConnectSetting.h"
#include "Reward.h"

#define _BUTTON_POS_X_  150.0f
#define _BUTTON_POS_Y_	500.0f
#define _BUTTON_WIDTH_	226.0f
#define _BUTTON_HEIGHT_	50.0f
#define _CHANGE_TIME_	3.0f*60.f
#define _REWARD_BUTTON_X_	50.f
#define _REWARD_BUTTON_Y_	650.f

/**
*@brief	タイトルシーンクラス
*/
class TitleScene : public CScene {
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
	TitleScene(int _id,
			   CRenderManager* const _pRenderManager,
			   CDrawManager* const _pDrawManager,
			   CKey* const _pKey,
			   CMouse* const m_pMouse,
			   Audio* const _pAudio )
			   : CScene( _id, _pRenderManager, _pDrawManager, _pKey, m_pMouse, _pAudio) {}

	/**
	*@breif	デストラクタ
	*/
	~TitleScene() {

	}

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
	Background	m_background;	///<背景オブジェクト
	Background	m_title;		///<タイトルオブジェクト
	Background	m_rudder;		///<舵のオブジェクト（ゲームの雰囲気作りの為

	ScreenMask	m_screenMask;	///<画面遷移時のフェード用
	Button		m_button;		///<ボタンオブジェクト（現時点ではゲームをスタートする時に使用）
	Button		m_rewardButton;
	ConnectSetting	m_connectSetting;
	Reward		m_reward;
	
	bool		m_changeSceneFlag;
	bool		m_stopFadeFlag;	///<フェード停止（終了）フラグ

};

#endif