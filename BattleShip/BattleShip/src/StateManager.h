#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "GameState.h"
#include "Player.h"
#include "StageObject.h"
#include "DrawStructList.h"
#include "BoardOfFrame.h"
#include "GameLog.h"

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
	std::string		m_tempStr1;
	std::string		m_tempStr2;
	int				m_beforeShip;	///<前フレームで選択（対象）されている駒を保持しておく。最初に入ってきた場合は初期値として-1を入れている。
//	他のオブジェクトと値のやり取りする可能性のある変数
private:
	
	Player* const 	m_pPlayer1;		///<	プレイヤー1情報格納ポインタ
	Player* const 	m_pPlayer2;		///<	プレイヤー2情報格納ポインタ
	const int		m_playerID;		///<	起動側のプレイヤーID。GameScene側からもらってくる。

	bool			m_connectFlag;	///<	通信を行うフラグ

	int m_plyaerSelectType;	///< 選択した行動の種類

	int m_resultPlayer;	///<	プレイヤー側に起きている戦闘結果
	int m_resultEnemy;	///<	敵側に起きている戦闘結果
	int m_resultBattle;	///<	両者の戦況結果
	int m_stateTime;	///<	各ステート内で秒数をカウントさせたい時に、シーン側で計測した秒数を渡す為のメンバ

//	ステート共通の描画オブジェクトの情報
private:
	BoardOfFrame	m_StageFrame;	///<	ステージ部分のフレームオブジェクト
	BoardOfFrame	m_PlayerFrame[_PLAYER_NUM_];	///<	プレイヤー情報のフレームオブジェクト	
	GameLog			m_gameLog;		///<	ゲームログオブジェクト
	GameLog			m_gameElapsed;	///<	経過時間出力ログ
	GameLog			m_gameConnectState;	///<	通信状態のログ

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
	*@brief	デストラクタ
	*/
	~StateManager() {
		CLASS_DELETE(m_pGameState);
	}

	/**
	*@brief	ステートの初期化
	*/
	void StateInit();
	
	/**
	*@brief	ステートの基本ルーチン処理
	*/
	int StateCotrol();

	/**
	*@brief	ステートの基本描画
	*/
	void StateDraw();

	/**
	*@brief	ステート状態の取得
	*/
	_STATE_NUM_ GetState(){ return m_currentState; }

	/**
	*@brief	各ステート内の経過時間の取得
	*@details	CSceneクラス内のm_sceneTimeを元に取得
	*/
	int GetStateInTime(){ return m_stateTime; }

	/**
	*@brief	各ステート内の経過時間の更新
	*@details	CSceneクラス内のm_sceneTimeを元に更新
	*/
	void UpdateStatInTime( int _elapsed )
	{
		if( m_stateTime != _elapsed )
		{
			//	経過時間が現在の時間と違っていれば、ステート側をインクリメント
			m_pGameState->SetElapsedTimeFromStateInstance( 
				m_pGameState->GetElapsedTimeFromStateInstance()+1);

#ifdef _DEBUG
			std::ostringstream s; 
			m_tempStr1 = "経過時間：";
			s << (m_pGameState->GetElapsedTimeFromStateInstance()/10) <<"."<< (m_pGameState->GetElapsedTimeFromStateInstance()%10) ;
			m_tempStr2 = s.str();
			m_tempStr1 = m_tempStr1+m_tempStr2;
			//	経過時間ログが空じゃ無かったら
			if( !m_gameElapsed.m_logStream.empty() )
			{
				//	中身（秒数表示ログ）を消す
				LogStream* temp = m_gameElapsed.m_logStream.back();
				delete temp;
				m_gameElapsed.m_logStream.pop_back();
			}
			//	経過後の現在時点での新しい経過時間をログに追加する。
			m_gameElapsed.AddStream(m_tempStr1.c_str());
#endif
		}
		m_stateTime=_elapsed;
	}

private:
	/**
	*@brief	各ステートのチェック
	*@details	各ステートのControlを呼んで、その結果などから、
				パターン変更の必要があるか管理。
	*@return	ステート	
	*@retval 1	ステートパターンの変更の必要あり。*n
	*@retval 0	変更の必要無し
	*@retval -1	ゲーム終了の場合
	*/
	int CheckState();

	/**
	*@brief	ステートパターンの切り替え
	*param[in]	_stateType	
	*@return true：ステートパターンの変更完了。*n
			false：変更失敗
	*/
	bool ChangeState( _STATE_NUM_ _stateType );

	/**
	*@brief	盤面の枠の表示
	*/
	void DrawStageFrame();

	/**
	*@brief	盤面上の駒（船）の表示
	*/
	void DrawShipObject( const int _playerIndex );

	/**
	*@brief	盤面のマス目（ブロック）の表示
	*/
	void DrawStageBlock( const int _playerIndex );

	/**
	*@brief	ゲームログの描画
	*/
	void DrawLog();

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