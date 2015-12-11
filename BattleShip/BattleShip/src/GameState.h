/**
*@file	GameState.h
*@author	亀田
*/

#ifndef	_GAMESTATE_H_
#define _GAMESTATE_H_

#include "DrawManager.h"
#include "Mouse.h"
#include "Player.h"
#include "StageObject.h"
#include "GameLog.h"
#include "Audio.h"

#define __NOT_USE_COM_	///<通信を使わないテスト

class GameState
{
public:
	/**
	*@brief	ゲーム内でのステートパターンの列挙。
	*@details	主にステート切り替え時に使用
	*/
	enum	_STATE_NUM_
	{
		STATE_NONE,
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
		STATE_ACTION_REPORT
	};

	/**
	*@brief	行動タイプ
	*/
	enum _SELECT_NUM_
	{
		_SELECT_NONE_ = -1,
		_SELECT_ACTION_,
		_SELECT_SEARCH_,
		_SELECT_MOVE_,
		_SELECT_MAX_
	};

//	メンバ変数など
protected:
	_STATE_NUM_ m_stateID;		///< 自身のステートのID	
	Player* m_pPlayer[_PLAYER_NUM_];	///< 駒データ格納用
	StageObject* m_pStage;		///< ステージデータ格納用
	int		m_playerID;			///< 起動側のID
	bool	m_StateCompFlag;	///< Control返り値兼、現在のステートでのタスクを完了フラグ。基本的にはStateManagerと共有のため取り扱いに注意！
	int		&m_ShipCount;		///< 今見ている駒を見るカウンタ
	bool	m_connectFlag;		///< 通信を行うフラグ
	GameLog* const	m_pGameLog;	///< ゲームログオブジェクトのポインタ
	std::string	m_tempStr1;
	std::string	m_tempStr2;

	/*
	*@detals	あまりにもマウス座標や駒オブジェクトの取得を何度もしていたため、
				この場合だとコストが掛かると思い、メンバ変数にしてこちらに
				毎フレーム保存していれば楽になると思い作った
	*/
	float m_tempX;	///<	マウスなどの座標の仮保存変数
	float m_tempY;	///<	マウスなどの座標の仮保存変数
	ShipObject* m_tempShip;	///<	駒の仮保存変数

	unsigned int m_elapsedTimeFormStateInstance;	///<	ステートが生成されていからの経過時間

//	デバイス
protected:
	CDrawManager*	m_pDrawManager;	///< 2D描画管理クラスポインタ(constポインタ)
	CMouse*			m_pMouse;		///< マウス管理クラスポインタ(constポインタ)
	Audio*			m_pAudio;		///< 音声再生クラスポインタ(constポインタ)

public:
	/**
	*@brief	コンストラクタ
	*@param	_type	現在選択している艦の種類
	*/
	GameState( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ) : 
	  m_ShipCount( (int &)_type ), m_pGameLog( _pGameLog )
	{
		m_connectFlag = false;
		m_StateCompFlag = false;
		m_elapsedTimeFormStateInstance = 0;
	}

	virtual ~GameState(){

	}

	/**
	*@brief	ステートパターン内での初期化
	*/
	virtual bool Init() = 0;

	/**
	*@brief	ステートパターン内でのサブルーチン処理
	*/
	virtual int Control() = 0;

	/**
	*@brief	ステートパターン内での描画
	*/
	virtual void Draw() = 0;

	/**
	*@brief	ステートパターン内での通信時のサブルーチン処理
	*/
	bool ComStandby( GameLog& _log )
	{
		std::ostringstream s; 
		m_tempStr1 = "通信中．";
		for( unsigned int i=0; i<(m_elapsedTimeFormStateInstance/3)%3; i++ )
		{
			s <<"．";
		}
		
		m_tempStr2 = s.str();
		m_tempStr1 = m_tempStr1+m_tempStr2;
		//	経過時間ログが空じゃ無かったら
		if( !_log.m_logStream.empty() )
		{
			//	中身（秒数表示ログ）を消す
			LogStream* temp = _log.m_logStream.back();
			delete temp;
			_log.m_logStream.pop_back();
		}
		//	経過後の現在時点での新しい経過時間をログに追加する。
		_log.AddStream(m_tempStr1.c_str());

		return true;
	}

	/**
	*@brief	ステートのID取得
	*/
	_STATE_NUM_ GetState(){ return m_stateID; }

	/**
	*@brief	通信を行うフラグを取得
	*/
	const bool GetConnectFlag(){ return m_connectFlag; }

	/**
	@brief	ステート生成されてからの経過時間の取得
	*/
	int GetElapsedTimeFromStateInstance(){ return m_elapsedTimeFormStateInstance; }

	/**
	*@breif	通信を行うフラグを更新
	*/
	void SetConnectFlag( const bool _flag ){ m_connectFlag = _flag; }

	/**
	*@brief	プレイヤークラスポインタをセット
	*@param[in]	_pPlayer	プレイヤーオブジェクトポインタ
	*@param[in]	_playerID	何番のプレイヤーか
	*/
	void SetPlayerPtr( Player* _pPlayer, int _playerID ){ 
		m_pPlayer[_playerID] = _pPlayer;
	}

	/**
	*@brief	ステージクラスポインタをセット
	*@param[in]	_pPlayer	ステージクラスポインタを
	*@param[in]	_playerID	何番のプレイヤーか
	*/
	void SetStagePtr( StageObject* _pStage ){ 
		m_pStage = _pStage;
	}

	/**
	*@brief	描画クラスセット
	*/
	void SetDraw( CDrawManager* const _pDrawManager ){
		m_pDrawManager = _pDrawManager;
	}

	/**
	*@brief	マウスクラスセット
	*/
	void SetMouse( CMouse* const _pMouse ){
		m_pMouse = _pMouse;
	}

	/**
	*@brief	音声クラスセット
	*/
	void SetAudio( Audio* const _pAudio ){
		m_pAudio = _pAudio;
	}

	/**
	*@brief	プレイヤーIDセット
	*/
	void SetPlayerID( int _playerID ){ m_playerID = _playerID; }

	/**
	@brief	ステート生成されてからの経過時間の更新
	*/
	void SetElapsedTimeFromStateInstance( int _elapsed ){ m_elapsedTimeFormStateInstance = _elapsed; }

};

#endif