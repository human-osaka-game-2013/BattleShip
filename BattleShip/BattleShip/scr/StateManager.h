#ifndef _STATEMANAGHER_H_
#define _STATEMANAGHER_H_

#include "Window.h"
#include "GameState.h"
#include "Player.h"
#include "StageObject.h"
#include "DrawManager.h"

#define _BLOCK_WIDTH_MAX_	23	///<盤面の横幅の最大ブロック数
#define _BLOCK_HEIGHT_MAX_	(float)16	///<盤面の縦幅の最大ブロック数
#define _STAGE_HEIGHT_MAX_	(float)11	///<ステージ部分の縦幅の最大ブロック数

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

public:
	/**
	*@brief	盤面のフレームオブジェクトクラス（描画用）
	*@details	ステージのUI要素などを別のクラスとして持たせる。@n
				ステージやプレイヤー情報は必要に応じてメンバからもらう。
	*/
	class BoardOfFrame : public CGameObject
	{
	private:
		float fWidth ,fHeight;

	public:
		/**
		*@brief	初期化
		*/
		void Init( float _fx, float _fy, float _fWidth, float _fHeight )
		{
			SetPosition(_fx, _fy, 0.5f);
			fHeight = _fHeight;
			fWidth = _fWidth;
		}
		void Control(){};
		void Draw(){};
		void Free(){};
		float GetWidth(){ return fWidth; }
		float GetHeight(){ return fHeight; }
	};

private:
	GameState*		m_pGameState;	///<	戦闘ステートパターンオブジェクトのポインタ
	_STATE_NUM_		m_beforeState;	///<	以前のステートパターン
	_STATE_NUM_		m_currentState;	///<	現在のステートパターン
	Player* const 	m_pPlayer1;		///<	プレイヤー1情報格納ポインタ
	Player* const 	m_pPlayer2;		///<	プレイヤー2情報格納ポインタ
	StageObject* const	m_pStageObject;	///<	ステージ情報格納ポインタ
	BoardOfFrame	m_StageFrame;	///<	ステージ部分のフレームオブジェクト
	BoardOfFrame*	m_pPlayerFrame;	///<	

public:
	/**
	*@brief	コンストラクタ
	*/
	StateManager( Player* const _pPlayer1, Player* const _pPlayer2,
		StageObject* const	_pStageObject);
	/**
	*@brief	解放処理
	*/
	void Free();

	/**
	*@brief	ステートパターンの切り替え
	*param[in]	_stateType	
	*@return true：ステートパターンの変更完了。*n
			false：変更失敗
	*/
	bool ChangeState( _STATE_NUM_ _stateType );
	
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
};


#endif