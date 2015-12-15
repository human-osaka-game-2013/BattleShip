#include "Reward.h"

void Reward::SetTable( char* _p, int _iColumn, int _iLine)
{

}

void Reward::DrawReward()
{
	float x=0.f, y=0.f, w=0.f, h=0.f;
	const float tweak=_BLOCK_WIDTH_SIZE_/9;
	const float blockW=_BLOCK_WIDTH_SIZE_, blockH=_BLOCK_HEIGHT_SIZE_;


	for( int i = 0; i<_REWARD_MAX_; i++ )
	{
		m_reward[i].GetPosition( &x, &y);
		w=m_reward[i].GetWidth();
		h=m_reward[i].GetHeight();

		m_pDraw->VertexDraw( _TEX_BLOCKFRAME_, 
							 x, y, w, h, 
							 0.f, 0.f, 1.f, 1.f);

		//	ïÒèVÇ™ÉQÉbÉgèoóàÇƒÇ¢ÇΩÇÁ
		if( (m_getRewardFlag&(0x01<<i)) )
		{
			m_pDraw->VertexDraw( _TEX_TORPEDO_, x, y, w, h,
								 0.f, 0.f, 1.f, 1.f);
		}
	}
}