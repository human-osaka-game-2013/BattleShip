#include "Reward.h"

void Reward::SetTable( char* _p, int _iColumn, int _iLine)
{
	unsigned char readData = StrToUChar( _p );

	if( readData )
	{
		GetReward(_iLine);
	}
}

void Reward::InitReward( Audio* _pAudio )
{
	m_frame.Init(_REWARD_FRAME_X_,
				 _REWARD_FRAME_Y_,
				 _REWARD_FRAME_WIDTH_,
				 _REWARD_FRAME_HEIGHT_ );
	
	/*
		報酬の表示基準点などを微調整
	*/
	float x, y;
	float w, h, tweak;
	const float blockW = _BLOCK_WIDTH_SIZE_, blockH = _BLOCK_HEIGHT_SIZE_;
	m_frame.GetPosition( &x, &y);
	w = blockW*2;
	h = blockH*2;
	tweak = m_frame.GetWidth()/10.f;
	y += blockH+tweak;
	x += tweak;
	/**/
	for( int i = 0; i < _REWARD_MAX_; i++ )
	{
		if( i == _UPPER_REWARD_MAX_  )
		{
			m_frame.GetPositionX();
			y += (tweak)+h;
		}
		m_rewardFrame[i].Init( x+((i%_UPPER_REWARD_MAX_)*tweak)+((i%_UPPER_REWARD_MAX_)*w),
								y, w, h);

	}
	m_frame.GetPosition( &x, &y);
	x += m_frame.GetWidth();
	m_cancelButton.Init( x, y, blockW, blockH, _pAudio );
}

void Reward::DrawReward()
{
	if( m_drawFlag )
	{
		float x=0.f, y=0.f, w=0.f, h=0.f;
		const float tweak=_BLOCK_WIDTH_SIZE_/9;
		const float blockW=_BLOCK_WIDTH_SIZE_, blockH=_BLOCK_HEIGHT_SIZE_;
		int tempA, tempR, tempG, tempB;

		m_frame.GetPosition( &x, &y);
		m_pDraw->VertexDraw( _TEX_REWARDFRAME_, x, y, 
			m_frame.GetWidth(),  m_frame.GetHeight(),
			0.f, 0.f, 1.f, 1.f);

		for( int i = 0; i<_REWARD_MAX_; i++ )
		{
			m_rewardFrame[i].GetPosition( &x, &y);
			w=m_rewardFrame[i].GetWidth();
			h=m_rewardFrame[i].GetHeight();

			m_pDraw->VertexDraw( _TEX_BLOCKFRAME_, 
								 x, y, w, h, 
								 0.f, 0.f, 1.f, 1.f);

			//	報酬がゲット出来ていたら
			bool rewardGetCheck = CheckReward(i);
			if( rewardGetCheck )
			{
				m_pDraw->VertexDraw( _TEX_TORPEDO_, x, y, w, h,
									 0.f, 0.f, 1.f, 1.f);
			}
		}

		//	cancelボタン描画
		m_cancelButton.GetPosition( &x, &y);
		m_cancelButton.GetColor( tempA, tempR, tempG, tempB );
		m_pDraw->VertexDraw( _TEX_CANCELBUTTON_, x, y, 
			m_cancelButton.GetWidth(),  m_cancelButton.GetHeight(),
			0.f, 0.f, 1.f, 1.f, tempA, tempR, tempG, tempB);
	}
}