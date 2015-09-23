/**
*@file	SceneManager.h
*@author	亀田
*@brief	シーン管理
*/


#ifndef _SCENEMANAGE_H_
#define _SCENEMANAGE_H_

#include "RenderManager.h"
#include "DrawManager.h"
#include "device.h"
#include "../../BattleShip/scr/SceneInterface.h"
#include "Key.h"
#include "Mouse.h"
#include "joystick_XInput.h"


/**
*@brief	シーン管理クラス
*@details	管理クラスを一つ作り、そこから各シーンクラスを生成→破棄を繰り返す。
*/
class CSceneManager
{
public:
	/**
	*@brief	シーン番号
	*/
	enum SCENE_NUM
	{
		SCENE_NONE = -1,
		//SCENE_LOGO,
		SCENE_TITLE,
		//SCENE_SELECT,
		SCENE_BATTLE,
		//SCENE_RESULT,
		SCENE_MAX
	};

private:
	CScene*			m_sceneObj;			///<	シーンオブジェクトポインタ
	CDevice* const	m_pDevice;			///<	デバイスクラスポインタ
	CRenderManager* m_pRenderManager;	///<	3D描画オブジェクトポインタ
	CDrawManager*	m_pDrawManager;		///<	2D描画オブジェクトポインタ
	CKey*			m_pKey;				///<	キー管理クラスオブジェクトポインタ
	CMouse*			m_pMouse;			///<	マウス管理クラスオブジェクトポインタ
	CXInput*		m_pXInput;		///<ジョイスティック管理クラス

	int		iCurrentScene;		///<	今のシーン
	bool	bChangeSceneFlag;	///<	シーン変更フラグ
	bool	m_bRenderType;		///<	描画タイプの判定

public:	
	/**
	*@brief	 コンストラクタ
	*/
	CSceneManager( int _scene , CDevice* const _pDevice, bool _bRenderType );	//	コンストラクタ

public:
	/**
	*@brief	 ゲームメイン関数
	*/
	int GameMain ();
		
	/**
	*@brief	 シーンクラスのルーチンの制御
	*/
	void SceneRoutingManage ();
	
	/**
	*@brief	描画の管理
	*@param[in]	b3dView	3Dモデルを扱う時はtrueに。
	*/
	void ViewManage ( bool b3dView = false );
	
	/**
	*@brief	 レンダリング管理(3D)
	*/
	void RenderManage ();
	
	/**
	*@brief	 描画管理(2D)
	*@param[in]	_b3dView　3D描画も同時にするか判断する
	*/
	void DrawManage ( bool _b3dView );

	/**
	*@brief	 描画後処理
	*/
	void EndRender ();

public:
	/**
	*@brief	今のシーン状態を取得
	*@return	iCurrentScene	現在のシーン
	*/
	int	CSceneManager::GetCurrentScene() { return iCurrentScene; }
	/**
	*@brief	シーン変更フラグを取得
	*@return	bChangeSceneFlag	シーン変更フラグ
	*/
	bool CSceneManager::GetChangeSceneFlag() { return  bChangeSceneFlag; }
	
	/**
	*@brief	シーン変更フラグの更新
	*@param[in]	_bTemp	シーン変更フラグを立てる
	*/
	void CSceneManager::UpdateChangeFlag( bool _bTemp ) { bChangeSceneFlag = _bTemp; }


public:
	/**
	*@brief	 シーン管理
	*@todo	この関数はゲーム側で設定してやるべき
	*/
	virtual void Manage ();

	/**
	*@brief	シーンオブジェクトの解放
	*@todo	SceneManager側に解放しないといけないメンバを追加した場合は、@n
			そのたびに追加してやる。
	*/
	virtual bool DeleteSceneObj();
};

#endif
