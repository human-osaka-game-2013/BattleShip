#ifndef _ACTIONREPORT_H_
#define _ACTIONREPORT_H_

#include "GameState.h"
#include "read_file.h"
#include "ReportData.h"

/**
*@brief	戦績の報告を行うクラス
*@details	戦闘中にReportDataクラスに蓄積されたデータを元に、
			戦績の判定などを行うクラス
*@todo		勲章などの取得なども出来るようにしたいです。
*/
class ActionReport : public GameState, public ReadFile
{
private:
	ReportData* const m_pReportData;
	ReportData	m_reportConditions[_REWARD_MAX_];	
	byte		m_getRewardFlag;
public:
	/**
	*@brief	コンストラクタ
	*/
	ActionReport(ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog, ReportData* _pReportData ):
	  GameState( _type, _pGameLog ), m_pReportData( _pReportData )
	{

	}
	
	bool Init();

	int Control();

	void Draw();

	void SetTable( char* _p, int _iColumn = _REWARD_MAX_, int _iLine = _SET_REPORTDATA_VAR_VOL_);

private:
	void JudgmentReward();

};

#endif