#include "ActionReport.h"

bool ActionReport::Init()
{
	ReadTableData( _REWARDTABLE_PASS_, _REWARD_MAX_, _MAX_REPORT_VAR_ );

	m_reward.GetDrawManagerPtr(m_pDrawManager);

	m_reward.InitReward( m_pAudio );

	m_reward.SetDrawFlag(true);

	for( int i = 0; i < _REWARD_MAX_; i++ )
		JudgmentReward( i );

	return true;
}

int ActionReport::Control()
{
	m_tempX = static_cast<float>(m_pMouse->GetCursorPosX());
	m_tempY = static_cast<float>(m_pMouse->GetCursorPosY());

	if( !m_StateCompFlag )
	{
		char inputState = m_pMouse->GetMouseSt( MOUSE_L );
		char buttonResult = m_reward.ControlReward( m_tempX, m_tempY, inputState );
		if( buttonResult == Button::STATE_SELECT )
		{
			m_StateCompFlag = true;
		}
	}

	return ((m_StateCompFlag) ? 1 : 0);
}

void ActionReport::Draw()
{
	m_reward.DrawReward();
}

void ActionReport::SetTable( char* _p, int _iColumn, int _iLine )
{
	switch( _iLine )
	{
	case _ATT_COUNT_:
		m_reportConditions[_iColumn].SetAttackCount(atoi(_p));
		break;
	case _SRC_COUNT_:
		m_reportConditions[_iColumn].SetSearchCount(atoi(_p));
		break;
	case _SL_AVE_TIME_:
		m_reportConditions[_iColumn].SetAveTime(atoi(_p));
		break;
	case _TURN_COUNT_:
		m_reportConditions[_iColumn].SetTurnCount(atoi(_p));
		break;
	case _DMG_COUNT_:
		m_reportConditions[_iColumn].SetDamageCount(atoi(_p));
		break;
	case _KO_COUNT_:
		m_reportConditions[_iColumn].SetKOCount(atoi(_p));
		break;
	case _HIT_PROB_:
		m_reportConditions[_iColumn].SetHitProbability( static_cast<float>(atof(_p)) );
		break;
	case _SIGHT_PROB_:
		m_reportConditions[_iColumn].SetSightProbability( static_cast<float>(atof(_p)) );
		break;
	}
}

void ActionReport::JudgmentReward( int _rewardNum )
{
	bool result = false;
	for( int i = 0; i < _MAX_REPORT_VAR_; i++ )
	{
		/**
		*@details	全ての条件に合うかチェック。
		*@todo	書き方がベタ書きでもっといい方法が無いか検討中
		*/
		switch( i )
		{
		case _ATT_COUNT_:
			result = CheckJudgeItem( m_reportResult.GetAttackCount(),
				m_reportConditions[_rewardNum].GetAttackCount());
			break;
		case _SRC_COUNT_:
			result = CheckJudgeItem( m_reportResult.GetSearchCount(),
				m_reportConditions[_rewardNum].GetSearchCount());
			break;
		case _SL_AVE_TIME_:
			result = CheckJudgeItem( m_reportResult.GetAveTime(),
				m_reportConditions[_rewardNum].GetAveTime());
			break;
		case _TURN_COUNT_:
			result = CheckJudgeItem( m_reportResult.GetTurnCount(),
				m_reportConditions[_rewardNum].GetTurnCount());
			break;
		case _DMG_COUNT_:
			result = CheckJudgeItem( m_reportResult.GetDamageCount(),
				m_reportConditions[_rewardNum].GetDamageCount());
			break;
		case _KO_COUNT_:
			result = CheckJudgeItem( m_reportResult.GetKOCount(),
				m_reportConditions[_rewardNum].GetKOCount());
			break;
		case _HIT_PROB_:
			result = CheckJudgeItem( m_reportResult.GetHitProbability(),
				m_reportConditions[_rewardNum].GetHitProbability());
			break;
		case _SIGHT_PROB_:
			result = CheckJudgeItem( m_reportResult.GetSightProbability(),
				m_reportConditions[_rewardNum].GetSightProbability());
			break;
		}
		//	条件を満たさなかった
		if( !result )
		{
			break;
		}
	}
	//	全ての条件を満たしていたので報酬を取得
	if( result )
	{
		m_reward.GetReward( _rewardNum );
	}
}
