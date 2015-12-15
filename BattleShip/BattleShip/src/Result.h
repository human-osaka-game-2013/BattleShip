/**
*@file	Result.h
*@author	亀田
*/

#ifndef _RESULT_H_
#define _RESULT_H_

#include "GameState.h"

#define _ANNIHILATION_NUM_ 16

/**
*@brief	艦種別の戦闘結果フラグのビット情報
*@details 索敵されたフラグを多量に作りたくなかった為、
		　どの艦が見つかったかをビットで取る事にしました。
*/
#define _BIT_A_ 0x01
#define _BIT_B_ 0x02
#define _BIT_C_ 0x04
#define _BIT_D_ 0x08
#define _BIT_S_ 0x10

class Result : public GameState
{
public:
	/**
	*@brief	行動選択によるの戦闘結果
	*/	
	enum _ACTION_RESULT_
	{
		RESULT_NONE,
		RESULT_SEARCH,
		RESULT_ATTACK,
	};

	/**
	*@brief	戦況の種類
	*/
	enum _PROGRESS_OF_BATTLE_TYPE_
	{
		TYPE_DEFEAT,		///<	敗北
		TYPE_INFERIORITY,	///<	劣勢
		TYPE_DRAW,			///<	引き分け
		TYPE_SUPERIORITY,	///<	優勢
		TYPE_VICTORY,		///<	勝利
		TYPE_STALEMATE		///<	手詰まり
	};

private:
	int m_resultPlayer;	///<	プレイヤー側に起きている戦闘結果
	int m_resultEnemy;	///<	敵側に起きている戦闘結果
	int m_resultBattle;	///<	両者の戦況結果
	unsigned char m_seachFlag;	///< 索敵で発見された艦種
	unsigned char m_bitFlag[ShipObject::TYPE_MAX];

public:
	/**
	*@brief	コンストラクタ
	*@param	_type	現在選択している艦の種類
	*/
	Result( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ): GameState( _type, _pGameLog ){
		m_resultPlayer	= 0;
		m_resultEnemy	= 0;
		m_resultBattle	= 0;
		m_seachFlag = 0x00;
		m_bitFlag[0] = _BIT_A_;
		m_bitFlag[1] = _BIT_B_;
		m_bitFlag[2] = _BIT_C_;
		m_bitFlag[3] = _BIT_D_;
		m_bitFlag[4] = _BIT_S_;
	}

	~Result(){};

	/**
	*@brief	戦闘結果での初期化
	*/
	bool Init();

	/**
	*@brief	戦闘結果でのサブルーチン処理

	*/
	int Control();
	
	/**
	*@brief	戦闘結果での描画
	*/
	void Draw();

	/**
	*@brief	戦闘結果の取得
	*@param[in] _resultPlayer
	*@param[in] _resultEnemy
	*/
	inline void GetResultPlayerAndEnemy( int& _resultPlayer, int& _resultEnemy )
	{
		_resultPlayer = m_resultPlayer;
		_resultEnemy = m_resultEnemy;
	}

	/**
	*@brief	戦況の取得
	*/
	void GetResultOfBattle( int& _resultBattle ){ _resultBattle = m_resultBattle; }

private:
	/**
	*@brief	行動選択による結果
	*@details	戦闘結果は、各駒１つの行動選択の結果なので、判定としては下記の３種類になる。
	*@param[in]	_playerIndex	プレイヤーの配列での指数
	*@return 戦闘結果
	*@retval 0	特に無し
	*@retval 1	相手の攻撃が当たった
	*@retval 2	相手に索敵された
	*/
	int ResultOfAction( const int _playerIndex );

	/**
	*@brief	戦闘処理の判定
	*@details	戦闘処理の判定をした際のステージや駒に情報の更新をしてやる
	*@param[out] _iReturn
	*@param[in]	_plIndex
	*@param[in]	_column
	*@param[in]	_line
	*@param[in]	_selectNum
	*@param[in]	_shipNum
	*/
	void JudgmentOfActionProcess( int& _iReturn, const int _plIndex, int& _column, int& _line,
									const int _selectNum, const int _shipNum );

	/**
	*@brief	戦闘結果の判定
	*@details	プレイヤー各々の駒の損害率をProgressOfBattle関数に渡し、
				_PROGRESS_OF_BATTLE_TYPE_に応じた値を返す。
	*@param[in]	_playerIndex プレイヤー側の指数
	*@param[in]	_enemyIndex 敵側の指数
	*@return	_PROGRESS_OF_BATTLE_TYPE_に合わせた値
	*/
	int ResultOfBattle( const int _playerIndex, const int _enemyIndex );

	/**
	*@brief	戦況判定
	*@details	プレイヤー各々の駒の損害率から、_PROGRESS_OF_BATTLE_TYPE_に応じた値を返す
	*@param[in]	_playerIndex プレイヤー側の指数
	*@param[in]	_enemyIndex 敵側の指数
	*@return	_PROGRESS_OF_BATTLE_TYPE_に合わせた値
	*/
	int ProgressOfBattle( int& _plHitCount, int& _enHitCount );
};

#endif