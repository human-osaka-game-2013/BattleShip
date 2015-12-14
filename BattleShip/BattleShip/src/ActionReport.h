#ifndef _ACTIONREPORT_H_
#define _ACTIONREPORT_H_

#include "GameState.h"
#include "read_file.h"
#include "ReportData.h"

/**
*@brief	��т̕񍐂��s���N���X
*@details	�퓬����ReportData�N���X�ɒ~�ς��ꂽ�f�[�^�����ɁA
			��т̔���Ȃǂ��s���N���X
*@todo		�M�͂Ȃǂ̎擾�Ȃǂ��o����悤�ɂ������ł��B
*/
class ActionReport : public GameState, public ReadFile
{
private:
	ReportData* const m_pReportData;
	ReportData	m_reportConditions[_REWARD_MAX_];	
	byte		m_getRewardFlag;
public:
	/**
	*@brief	�R���X�g���N�^
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