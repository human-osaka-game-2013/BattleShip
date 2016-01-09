#ifndef _ACTIONREPORT_H_
#define _ACTIONREPORT_H_

#include "GameState.h"
#include "read_file.h"
#include "ReportResult.h"
#include "Reward.h"

/**
*@brief	��т̕񍐂��s���N���X
*@details	�퓬����ReportResult�N���X�ɒ~�ς��ꂽ�f�[�^�����ɁA
			��т̔���Ȃǂ��s���N���X
*/
class ActionReport : public GameState, public ReadFile {
 public:
	/**
	*@brief	�R���X�g���N�^
	*/
	ActionReport(ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog, ReportData& _pReportData )
				 : GameState( _type, _pGameLog ) {
		//	�퓬���̃f�[�^�����ʕ����ɐ���
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
	*@brief	�S�Ă̏̍��̔���
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
	*@brief	�M�͂̎擾����
	*/
	void JudgmentReward( int _rewardNum );

	template <class T>
	/**
	*@brief	�M�͂̏����v�f�̃`�F�b�N
	*/
	bool CheckJudgeItem( T _item, T _val ) {
		//	0�͏����ɓ��Ă͂܂�Ȃ�
		if (_val == 0) {
			return true;
		}
		//	�}�C�i�X�l��������_val�̐�Βl>_item�Ŕ���
		if (_val < 0) {
			if (abs(_val) >= _item) {
				return true;
			}
		}
		//	�v���X�l��������_val<_item�Ŕ���
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