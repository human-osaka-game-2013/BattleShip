/**
*@file	SceneInterface.h
*@author	亀田
*/

#ifndef _SCENE_H_
#define _SCENE_H_
#include "RenderManager.h"
#include "DrawManager.h"
#include "Key.h"
#include "Mouse.h"
#include "gameObject.h"
#include <list>

#define _PLAYER_ID_	1

class CScene
{
protected:
	CRenderManager* const m_pRenderManager;	///<	3D描画管理クラスポインタ(constポインタ)
	CDrawManager*	const m_pDrawManager;	///<	2D描画管理クラスポインタ(constポインタ)
	CKey*			const m_pKey;			///<	キー管理クラスポインタ	(constポインタ)
	CMouse*			const m_pMouse;			///<	マウス管理クラスポインタ(constポインタ)
	
protected:
	int m_sceneID;	//	シーンID保存変数(コンストラクタの時にシーンIDが入る)
	int m_count;	//	シーン内でのカウント

public:
	/**
	*@brief	コンストラクタ
	*@details	使わない管理ポインタがある場合NULLポインタを入れる
	*@param[in]	_id	自分自身のシーンID
	*@param[in]	_pRenderManager	3D描画管理のポインタ
	*@param[in]	_pDrawManager	2D描画管理のポインタ
	*@param[in]	_pKey			キー管理のポインタ
	*@param[in]	_pMouse		マウス管理のポインタ
	*/
	CScene( int _id, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager,
		CKey* const _pKey, CMouse* const _pMouse);
	/**
	*@briefデストラクタ
	*/
	virtual ~CScene()
	{
		
	}

public:
	/**
	*@brief	初期化の純粋仮想関数
	*@return	初期化の結果
	*@retval true	成功
	*@retval false	初期化に何らかの失敗があった場合
	*/
	virtual bool Init() = 0;

	/**
	*@brief	シーンの基本処理の純粋仮想関数
	*@return	シーン変更をする判断の値
	*@retval 0	シーン変更無し
	*@retval 1	シーン変更有り
	*/
	virtual int	 Control()	= 0;	

	virtual void Draw()	= 0;		///< 2D描画の仮想関数
	virtual void Render() = 0;		///< 3D描画の仮想関数

public:
	/**
	*@brief	シーンIDを取得
	*@return	m_sceneID	自分のシーンIDを取得
	*/
	int GetSceneID()	{ return m_sceneID; }	

	/**
	*@brief	シーンIDを更新
	*/
	void SetSceneID( int _scene ){ m_sceneID = _scene; }
};

#endif