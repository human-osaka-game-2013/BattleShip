#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "GameState.h"
#include "Player.h"
#include "StageObject.h"
#include "DrawStructList.h"
#include "BoardOfFrame.h"


class StateManager
{
public:
	/**
	*@brief	戦闘ステートパターンの列挙
	*/
	enum _STATE_NUM_
	{
		STATE_NONE = -1,
		STATE_SET_SHIP,
		STATE_SELECTION,
		STATE_RESULT,
		STATE_STAGE_EFFECT,
	};

	
//	通常のメンバ変数
private:
	GameState*		m_pGameState;	///<	戦闘ステートパターンオブジェクトのポインタ
	_STATE_NUM_		m_beforeState;	///<	以前のステートパターン
	_STATE_NUM_		m_currentState;	///<	現在のステートパターン
	StageObject* const	m_pStageObject;	///<	ステージ情報格納ポインタ
	ShipObject::_SHIP_TYPE_NUM_	m_currentShip;	///<	現在選択対象の駒。GameStateと共有するため取り扱いに注意！
	
//	他のオブジェクトと値のやり取りする可能性のある変数
private:
	
	Player* const 	m_pPlayer1;		///<	プレイヤー1情報格納ポインタ
	Player* const 	m_pPlayer2;		///<	プレイヤー2情報格納ポインタ
	const int		m_playerID;		///<	起動側のプレイヤーID。GameScene側からもらってくる。

	bool			m_connectFlag;	///<	通信を行うフラグ

	int m_selectType;	///< 選択した行動の種類

	int m_resultPlayer;	///<	プレイヤー側に起きている戦闘結果
	int m_resultEnemy;	///<	敵側に起きている戦闘結果
	int m_resultBattle;	///<	両者の戦況結果

//	ステート共通の描画オブジェクトの情報
private:
	BoardOfFrame	m_StageFrame;	///<	ステージ部分のフレームオブジェクト
	BoardOfFrame	m_PlayerFrame[_PLAYER_NUM_];	///<	プレイヤー情報のフレームオブジェクト	
//	BoardOfFrame	m_ShipFrame[_PLAYER_NUM_][ShipObject::TYPE_MAX];

//	デバイス
private:
	CDrawManager*	m_pDrawManager;	///<	2D描画管理クラスポインタ(constポインタ)
	CMouse*			m_pMouse;		///<	マウス管理クラスポインタ(constポインタ)

public:
	/**
	*@brief	コンストラクタ
	*/
	StateManager( Player* const _pPlayer1, Player* const _pPlayer2,
		StageObject* const	_pStageObject, const int _playerID );

	/**
	*@brief	ステートの初期化
	*/
	void StateInit();
	
	/**
	*@brief	ステートの基本ルーチン処理
	*/
	void StateCotrol();

	/**
	*@brief	ステートの基本描画
	*/
	void StateDraw( CDrawManager* _drawManager);

	/**
	*@brief	ステートオブジェクトの消去
	*/
	void StateDelete();

	/**
	*@brief	解放処理
	*/
	void Free();

	/**
	*@brief	ステート状態の取得
	*/
	_STATE_NUM_ GetState(){ return m_currentState; }

private:
	/**
	*@brief	ステートパターンの切り替え
	*@details	各ステートのControlを呼んで、その結果などから、
				パターン変更の必要があるか管理。
	*@return true：ステートパターンの変更の必要あり。*n
			false：変更の必要無し
	*/
	bool CheckState();

	/**
	*@brief	ステートパターンの切り替え
	*param[in]	_stateType	
	*@return true：ステートパターンの変更完了。*n
			false：変更失敗
	*/
	bool ChangeState( _STATE_NUM_ _stateType );

public:
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
	*@brief	通信を行うフラグを取得
	*/
	const bool GetConnectFlag(){ return m_connectFlag; }

	/**
	*@breif	通信を行うフラグを更新
	*/
	void SetConnectFlag( const bool _flag ){ m_connectFlag = _flag; }

};


#endif