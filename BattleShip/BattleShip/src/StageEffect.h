/**
*@file	StageEffect.h
*@author	亀田
*/

#ifndef _STAGEEFFECT_H_
#define _STAGEEFFECT_H_

#include "GameState.h"

#define _END_COUNT_OF_EFFECT_	60*10

class StageEffect : public GameState
{
public:
	enum _STAGE_EFFECT_TIME_
	{
		TIME_END_ACTION_EFFECT =20,

		TIME_CHANGE_EFFECT = 10+TIME_END_ACTION_EFFECT,

		TIME_END_RUSULT_EFFECT = 20+TIME_CHANGE_EFFECT,
	};

private:
	_SELECT_NUM_ m_selectType;	///< 選択した行動の種類
	_SELECT_NUM_ m_enemyType;	///< 相手の選択した行動
	int m_actionShipPosColumn;	///< 行動する自駒の行座標
	int m_actionShipPosLine;	///< 行動する自駒の列座標
	std::vector<BoardOfFrame> m_playerSelect;///< 自分が敵に対して指定したマスのコピー用
	std::vector<BoardOfFrame> m_enemySelect; ///< 敵が自分に対して指定したマスのコピー用
	BoardOfFrame m_myShipBlock;

public:
	/**
	*@brief	コンストラクタ
	*@param	_type	現在選択している艦の種類
	*/
	StageEffect( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ): GameState( _type, _pGameLog ){
		
	}

	~StageEffect()
	{
		m_playerSelect.clear();
		m_enemySelect.clear();
	};

	/**
	*@brief	戦闘エフェクトでの初期化
	*/
	bool Init();

	/**
	*@brief	戦闘エフェクトでのサブルーチン処理
	*/
	int Control();
	
	/**
	*@brief	戦闘エフェクトでの描画
	*/
	void Draw();
	
	/**
	*@brief	戦闘エフェクトでの通信待機処理
	*/
	bool ComStandby();

	/**
	*@brief	選択した行動の種類を更新
	*@details	SelectionステートからStateManagerが行動の選択情報をもらっているので、
				StageEffectステートがどの行動のエフェクトをすればいいか判断するために、必要だと考えました。
	*/
	void SetSelectionType( int _selectType )
	{ 
		m_selectType = static_cast<_SELECT_NUM_>(_selectType); 
	}

private:
	/**
	@brief	発射エフェクト処理
	*/
	bool FireEffect();

	/**
	*@brief	索敵開始エフェクト処理
	*/
	bool SearchStratEffect();

	/**
	*@brief	着弾エフェクト処理
	*@param[in]	_playerIndex	どちらのプレイヤーが索敵をするのかを判断するため
	*/
	bool HitEffect( const int _playerID );

	/**
	*@brief	索敵結果エフェクト処理
	*@param[in]	_playerID	どちらのプレイヤーが索敵をするのかを判断するため
	*/
	bool SearchResultEffect( const int _playerID );

private:

	/**
	*@brief	ステージの選択状況のチェック
	*/
	void CheckSelectOfStage();

	/**
	*@brief	自駒の座標チェック
	*/
	void CheckOfMyShipPos();

private:
	/**
	*@brief	ソナーエフェクト
	*/
	void SonarEffect();

};

#endif