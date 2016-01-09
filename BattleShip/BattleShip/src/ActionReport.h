#ifndef _ACTIONREPORT_H_
#define _ACTIONREPORT_H_

#include "GameState.h"
#include "read_file.h"
#include "ReportResult.h"
#include "Reward.h"

/**
*@brief	戦績の報告を行うクラス
*@details	戦闘中にReportResultクラスに蓄積されたデータを元に、
			戦績の判定などを行うクラス
*/
class ActionReport : public GameState, public ReadFile {
 public:
	/**
	*@brief	コンストラクタ
	*/
	ActionReport(ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog, ReportData& _pReportData )
				 : GameState( _type, _pGameLog ) {
		//	戦闘中のデータを結果方式に整理
		m_reportResult.ArrangementReport( _pReportData );
	}
	
	bool Init();

	int Control();

	void Draw();

	void SetTable( char* _p, int _iColumn = _REWARD_MAX_, int _iLine = _MAX_REPORT_VAR_);

	~ActionReport() {
		m_reward.SaveReward();
	}

 private:
	/**
	*@brief	全ての称号の判定
	*/
	void AllCheckReward() {
		for ( int i = 0; i < _REWARD_MAX_; i++ ) {
			bool result = false;
			result = m_reward.CheckReward( i );
			if (result) {
				JudgmentReward( i );
			}
		}
	}

	/**
	*@brief	勲章の取得判定
	*/
	void JudgmentReward( int _rewardNum );

	template <class T>
	/**
	*@brief	勲章の条件要素のチェック
	*/
	bool CheckJudgeItem( T _item, T _val ) {
		//	0は条件に当てはまらない
		if (_val == 0) {
			return true;
		}
		//	マイナス値だったら_valの絶対値>_itemで判定
		if (_val < 0) {
			if (abs(_val) >= _item) {
				return true;
			}
		}
		//	プラス値だったら_val<_itemで判定
		else if (_val > 0) {
			if (abs(_val) <= _item) {
				return true;
			}
		}
		return false;
	}

	ReportResult	m_reportResult;
	ReportResult	m_reportConditions[_REWARD_MAX_];	
	Reward			m_reward;

};

#endif