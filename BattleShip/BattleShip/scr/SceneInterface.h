#ifndef _SCENE_H_
#define _SCENE_H_
#include "RenderManager.h"
#include "DrawManager.h"
#include "Key.h"
#include "Mouse.h"
#include "gameObject.h"
#include <list>

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
	*@param[in]	m_pMouse		マウス管理のポインタ
	*/
	CScene( int _id, CRenderManager* const _pRenderManager,
		CDrawManager*	const _pDrawManager,
		CKey* const _pKey, CMouse* const m_pMouse );
	/**
	*@briefデストラクタ
	*/
	~CScene();
public:
	virtual bool Init() = 0;		///< 初期化の仮想関数
	virtual int	 Control()	= 0;	///< 処理の仮想関数。@n
									///	GetSceneID()でシーンIDを返して、マネージャーの方でシーン変更に使わせる
	virtual void Draw()	= 0;		///< 2D描画の仮想関数
	virtual void Render() = 0;		///< 3D描画の仮想関数

public:
	/**
	*@brief	シーンIDを取得
	*@return	m_sceneID	自分のシーンIDを取得
	*/
	int GetSceneID()	{ return m_sceneID; }	

};

#endif