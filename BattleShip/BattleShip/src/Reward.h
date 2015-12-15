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
	BoardOfFrame	m_reward[_REWARD_MAX_];

public:
	Reward()
	{
		m_getRewardFlag = 0x00;
		m_frame.Init(_REWARD_FRAME_X_,
					 _REWARD_FRAME_Y_,
					 _REWARD_FRAME_WIDTH_,
					 _REWARD_FRAME_HEIGHT_ );
		
		/*
			��V�̕\����_�Ȃǂ������
		*/
		float x, y;
		float w, h, tweak;
		const float blockW = _BLOCK_WIDTH_SIZE_, blockH = _BLOCK_HEIGHT_SIZE_;
		m_frame.GetPosition( &x, &y);
		w = blockW*2;
		h = blockH*2;
		tweak = m_frame.GetWidth()/10.f;
		x += tweak;
		/**/
		for( int i = 0; i < _REWARD_MAX_; i++ )
		{
			if( i == _UPPER_REWARD_MAX_  )
				y += tweak*2;

			m_reward[i].Init( x+(i*tweak),
							  y,
							  w,
							  h);
		}
	}

	void SetTable( char* _p, int _iColumn, int _iLine);
	
	void DrawReward();

	void GetDrawManagerPtr( CDrawManager* _pDraw ){ m_pDraw = _pDraw; }

	/**
	*@brief	��V���擾����Ă��邩�̃`�F�b�N
	*/
	bool CheckReward( int _shit )
	{
		unsigned char result;
		result = (m_getRewardFlag & ( 0x01<<_shit ));

		return 	result?true:false;
	}

	/**
	*@brief	��V�̎擾
	*/
	void GetReward( int _shit )
	{	
		m_getRewardFlag = ( m_getRewardFlag|(0x01<<_shit));
	}
};
#endif