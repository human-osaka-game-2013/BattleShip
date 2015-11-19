/**
*@file	SceneInterface.h
*@author	亀田
*/

#ifndef _SCENE_H_
#define _SCENE_H_
#include "Audio.h"
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
	CRenderManager* const m_pRenderManager;	///< 3D描画管理クラスポインタ(constポインタ)
	CDrawManager*	const m_pDrawManager;	///< 2D描画管理クラスポインタ(constポインタ)
	CKey*			const m_pKey;			///< キー管理クラスポインタ	(constポインタ)
	CMouse*			const m_pMouse;			///< マウス管理クラスポインタ(constポインタ)
	Audio*			const m_pAudio;			///< 音声再生クラスポインタ(constポインタ)

protected:
	int m_sceneID;	//	シーンID保存変数(コンストラクタの時にシーンIDが入る)
	int m_count;	//	シーン内でのカウント

private:
	bool			m_sceneEndFlag;		///<	シーンの終了or遷移をさせるフラグ（フェードイン＆アウトの開始に使う）
	unsigned int	m_sceneTime;		///<	シーン内での秒数カウント(0.1秒分までカウントしています

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
		CKey* const _pKey, CMouse* const _pMouse, Audio* const _pAudio);
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
	*@brief	各シーン内での経過時間のカウント
	*@details	60FPSで回っていて、この関数は1フレームのループで1度のみ呼ばれている前提である
	*/
	void CountTimeInScene(){
		static DWORD SyncOld = 0;
		static DWORD SyncNow = 0;

		SyncNow = timeGetTime();

		if (SyncNow - SyncOld >= 1000 / 10)
		{
			m_sceneTime++;

			SyncOld = SyncNow;
		}
	}
	
	/**
	*@brief	各シーン内の経過時間の取得
	*@details	CountTimeInSceneが60FPS間に1度のみ呼ばれている時のみ有効
	*/
	int GetTimeInScene(){ return m_sceneTime; }

	/**
	*@brief	シーンIDを取得
	*@return	m_sceneID	自分のシーンIDを取得
	*/
	int GetSceneID()	{ return m_sceneID; }	

	/**
	*@brief	シーン終了フラグの取得
	*/
	bool GetSceneEndFlag(){ return m_sceneEndFlag; }

	/**
	*@brief	シーンIDを更新
	*/
	void SetSceneID( int _scene ){ m_sceneID = _scene; }

	/**
	*@brief	シーン終了フラグの更新
	*/
	void SetSceneEndFlag( bool _flag ){ m_sceneEndFlag = _flag; }
};

#endif