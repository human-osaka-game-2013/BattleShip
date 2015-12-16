#ifndef _REWARD_H_
#define _REWARD_H_
#include "read_file.h"
#include "DrawManager.h"
#include "StageDefineList.h"
#include "BoardOfFrame.h"
#include "Button.h"

#define _REWARD_FRAME_X_	_BLOCK_WIDTH_SIZE_*3
#define _REWARD_FRAME_Y_	_BLOCK_HEIGHT_SIZE_*2
#define _REWARD_FRAME_WIDTH_	_BLOCK_WIDTH_SIZE_*16
#define _REWARD_FRAME_HEIGHT_	_BLOCK_HEIGHT_SIZE_*10

/**
*@brief	��V�̊l���L���̃Z�[�u�f�[�^
*@details	����Í����Ȃǂ͖������ȈׁA�x�^�����ł��B
*@todo	�Í����Ȃǂ̎����\�肠��
*/
#define _REWARDSAVEDATA_PASS_ "table/savedata.BS"

/**
*@brief	��V�̎�ޗ�
*/
enum _REWARD_TYPE_
{

	_UPPER_REWARD_MAX_ = 4,

	_REWARD_MAX_ = 8,
};

/**
*@brief	��V����N���X
*/
class Reward : public ReadFile
{
private:
	unsigned char m_getRewardFlag;
	CDrawManager* m_pDraw;
	BoardOfFrame	m_frame;
	BoardOfFrame	m_rewardFrame[_REWARD_MAX_];
	Button			m_cancelButton;

	bool	m_drawFlag;

public:
	Reward()
	{
		m_getRewardFlag = 0x00;
		m_drawFlag = false;

		ReadBinaryData( _REWARDSAVEDATA_PASS_, 
						static_cast<void*>(&m_getRewardFlag),
						sizeof(m_getRewardFlag));
		//ReadTableData( _REWARDSAVEDATA_PASS_, 1, _REWARD_MAX_);
	}

	void InitReward( Audio* _pAudio );

	const char ControlReward( float _x, float _y, const char _inputState )
	{
		m_cancelButton.SetState( Button::STATE_OFF_CURSOR );
		const char result = m_cancelButton.Contorl( _x, _y, _inputState);
		return result;
	}

	void SetTable( char* _p, int _iColumn, int _iLine);
	
	void DrawReward();

	void GetDrawManagerPtr( CDrawManager* _pDraw ){ m_pDraw = _pDraw; }

	/**
	*@brief	��V���擾����Ă��邩�̃`�F�b�N
	*/
	bool CheckReward( int _shift )
	{
		unsigned char result;
		result = (m_getRewardFlag & ( 0x01<<_shift ));

		return 	result?true:false;
	}

	/**
	*@brief	��V�̎擾
	*@param[in]	_shift	���ʃr�b�g���牽�Ԗڂ̃f�[�^�̃t���O�𗧂Ă邩
	*/
	void GetReward( int _shift )
	{	
		m_getRewardFlag = ( m_getRewardFlag|(0x01<<_shift));
	}

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
};
#endif