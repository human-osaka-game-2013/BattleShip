#ifndef _REWARD_H_
#define _REWARD_H_
#include "read_file.h"
#include "DrawManager.h"
#include "StageDefineList.h"
#include "BoardOfFrame.h"
#include "Button.h"
#include "GameLog.h"

#define _REWARD_FRAME_X_	_BLOCK_WIDTH_SIZE_*3
#define _REWARD_FRAME_Y_	_BLOCK_HEIGHT_SIZE_*2
#define _REWARD_FRAME_WIDTH_	_BLOCK_WIDTH_SIZE_*16
#define _REWARD_FRAME_HEIGHT_	_BLOCK_HEIGHT_SIZE_*10

#define _REWARDTABLE_PASS_ "table/RewardTable.csv"
#define _REWARDSAVEDATA_PASS_ "table/savedata.BS"

#define _REWARD_PAGE_MAX_	2
#define _ARROW_MAX_ 2

/**
*@brief	�M�̗͂�
*/
enum _REWARD_TYPE_
{
	_REWARD_HEIGHT_LIMIT_ = 2,
	_REWARD_WIDTH_LIMIT_ = 4,

	_PAGE_LIMIT_REWARD_ = 8, 

	_REWARD_MAX_ = 10,

	_REWARD_FRAME_MAX_ = _PAGE_LIMIT_REWARD_*_REWARD_PAGE_MAX_,
};

/**
*@brief	�M�͊Ǘ��N���X
*@details	�M�͂̊l���L���̃Z�[�u�f�[�^�B\n
			����Í����Ȃǂ͖������ȈׁA�x�^�����ł��B
*@todo	�Í����Ȃǂ̎����\�肠��
*/
class Reward : public ReadFile
{
private:
	unsigned char m_getRewardFlag;
	CDrawManager* m_pDraw;		///< Reward�N���X�P�̂ł̕`�悪�o�����Title�ł��ėp�������Ǝv���A�`��Ǘ��N���X���������܂����B
	BoardOfFrame	m_frame;	///< �M�͕\���̍ۂ̔w�i
	BoardOfFrame	m_rewardFrame[_REWARD_PAGE_MAX_][_PAGE_LIMIT_REWARD_];	///< �M�͂̕`��I�u�W�F�N�g
	GameLog			m_rewardName[_REWARD_PAGE_MAX_][_PAGE_LIMIT_REWARD_];	///< �M�̖͂��O
	Button			m_cancelButton;	///< �M�͂̕\������߂�ۂ̃{�^��
	Button			m_arrowButton[_ARROW_MAX_];	

	int		m_selectRewardPage;
	bool	m_drawFlag;

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	Reward()
	{
		m_getRewardFlag = 0x00;
		m_selectRewardPage = 0;
		m_drawFlag = false;

		bool readResult = ReadBinaryData( _REWARDSAVEDATA_PASS_, 
						static_cast<void*>(&m_getRewardFlag),
						sizeof(m_getRewardFlag));
		
		/**
		*@details	�ǂݍ��݂����s�����ꍇ�́A���s�����ۂɍ쐬���ꂽ�t�@�C����
					�S��0����������
		*/
		if( !readResult )
		{
			SaveToBinaryData( _REWARDSAVEDATA_PASS_, 
						static_cast<void*>(&m_getRewardFlag),
						sizeof(m_getRewardFlag));
		}
	}

	/**
	*@brief	�M�̓I�u�W�F�N�g�̏�����
	*/
	void InitReward( Audio* _pAudio );

	/**
	*@brief	�M�̓I�u�W�F�N�g�̏���
	*/
	const char ControlReward( float _x, float _y, const char _inputState )
	{
		m_cancelButton.SetState( Button::STATE_OFF_CURSOR );
		
		for( int i = 0; i < _ARROW_MAX_; i++ )
		{
			m_arrowButton[i].SetState( Button::STATE_OFF_CURSOR );
			char arrowResult = m_arrowButton[i].Contorl( _x, _y, _inputState );
			if( arrowResult == 2 )
				RewardPageControl(i);
		}
		const char result = m_cancelButton.Contorl( _x, _y, _inputState );
		return result;
	}

	/**
	*@brief	�t�@�C���ǂݍ���
	*/
	void SetTable( char* _p, int _iColumn, int _iLine);
	
	/**
	*@brief	�M�̓I�u�W�F�N�g�̕`��
	*/
	void DrawReward();

	/**
	*@brief	�`��Ǘ��I�u�W�F�N�g�̃|�C���^���擾
	*/
	void GetDrawManagerPtr( CDrawManager* _pDraw ){ m_pDraw = _pDraw; }

	/**
	*@brief	�M�͂��擾����Ă��邩�̃`�F�b�N
	*/
	bool CheckReward( int _shift )
	{
		unsigned char result;
		result = (m_getRewardFlag & ( 0x01<<_shift ));

		return 	result?true:false;
	}

	/**
	*@brief	�M�͂̎擾
	*@param[in]	_shift	���ʃr�b�g���牽�Ԗڂ̃f�[�^�̃t���O�𗧂Ă邩
	*/
	void GetReward( int _shift )
	{	
		m_getRewardFlag = ( m_getRewardFlag|(0x01<<_shift));
	}

	/**
	*@brief	�M�̓f�[�^�̕ۑ�
	*/
	bool SaveReward()
	{
		bool result;
		result = SaveToBinaryData( _REWARDSAVEDATA_PASS_,
								static_cast<void*>(&m_getRewardFlag),
								sizeof(m_getRewardFlag));

		return result;
	}

	void SetDrawFlag( bool _flag ){ m_drawFlag = _flag; }
	bool GetDrawFlag(){ return m_drawFlag; }

private:
	/**
	*@brief	�M�̖͂��O�`��
	*/
	void RewardNameDraw( int _rewardNum );

	void RewardPageControl( int _arrowNum )
	{
		m_selectRewardPage += _arrowNum/_ARROW_MAX_ ? 1:-1;
		if( m_selectRewardPage < 0 )
			m_selectRewardPage = _REWARD_PAGE_MAX_-1;

		if( m_selectRewardPage >= _REWARD_PAGE_MAX_ )
			m_selectRewardPage = 0;
	}

};
#endif