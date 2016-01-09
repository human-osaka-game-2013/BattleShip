#include "Reward.h"
#include "ReportResult.h"

void Reward::SetTable( char* _p, int _iColumn, int _iLine)
{
	if ( _iLine == _REWARD_NAME_ )
	{
		int page = _iColumn/_PAGE_LIMIT_REWARD_;
		int rewardNum = _iColumn%_PAGE_LIMIT_REWARD_;
		float x, y;
		const float blockW = _BLOCK_WIDTH_SIZE_, blockH = _BLOCK_HEIGHT_SIZE_;
		m_rewardFrame[page][rewardNum].GetPosition( &x, &y );
		y += blockH*2;

		m_rewardName[page][rewardNum].DeleteStream();
		m_rewardName[page][rewardNum].Init( static_cast<long>(x), static_cast<long>(y), _p, 0xff000000 );
	}
}

void Reward::InitReward( Audio* _pAudio )
{
	

	m_frame.Init(_REWARD_FRAME_X_,
				 _REWARD_FRAME_Y_,
				 _REWARD_FRAME_WIDTH_,
				 _REWARD_FRAME_HEIGHT_ );
	
	/*
		勲章の表示基準点などを微調整
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
	
	for ( int i = 0; i < _REWARD_FRAME_MAX_; i++ )
	{
		const int page = i/_PAGE_LIMIT_REWARD_;
		
		if ( i%_REWARD_WIDTH_LIMIT_ == 0 )
		{
			m_frame.GetPositionX();
			y += (tweak)+h;
		}
		if ( i%_PAGE_LIMIT_REWARD_ == 0 )
		{
			m_frame.GetPosition( &x, &y);
			w = blockW*2;
			h = blockH*2;
			tweak = m_frame.GetWidth()/10.f;
			y += blockH+tweak;
			x += tweak;
		}
		
		m_rewardFrame[page][i%_PAGE_LIMIT_REWARD_].Init( x+((i%_REWARD_WIDTH_LIMIT_)*tweak)+((i%_REWARD_WIDTH_LIMIT_)*w),
														y, w, h);

		m_rewardName[page][i%_PAGE_LIMIT_REWARD_].Init( static_cast<long>(x), static_cast<long>(y) );
	
	}
	/*
		キャンセルボタンの初期化
	*/
	m_frame.GetPosition( &x, &y);
	x += m_frame.GetWidth();
	m_cancelButton.Init( x, y, blockW, blockH, _pAudio );
	
	/*
		勲章ページ送りの矢印ボタンの初期化
	*/
	m_rewardFrame[0][5].GetPosition( &x, &y );
	y += (blockH*2)+(tweak*2);
	m_arrowButton[0].Init( x, y, blockW*2, tweak/2.f, _pAudio );
	x = m_rewardFrame[0][6].GetPositionX();
	m_arrowButton[1].Init( x, y, blockW*2, tweak/2.f, _pAudio );

	/**
	*@brief 勲章の名前を勲章獲得条件のデータから引っ張る。
	*@details	別ファイルorRewardのセーブデータに登録する手もありましたが、
				ファイル数の増加かバイナリ形式で登録のコストと比べた場合に、
				勲章獲得条件のデータから引っ張ったほうが良いと判断しました。
	*/
	ReadTableData( _REWARDTABLE_PASS_, _REWARD_MAX_, _MAX_REPORT_VAR_); 
}

void Reward::DrawReward()
{
	if ( m_drawFlag )
	{
		float x=0.f, y=0.f, w=0.f, h=0.f;
		const float tweak=_BLOCK_WIDTH_SIZE_/9;
		const float blockW=_BLOCK_WIDTH_SIZE_, blockH=_BLOCK_HEIGHT_SIZE_;
		int tempA, tempR, tempG, tempB;

		m_frame.GetPosition( &x, &y);
		m_pDraw->VertexDraw( _TEX_REWARDFRAME_, x, y, 
							 m_frame.GetWidth(),  m_frame.GetHeight(),
							 0.f,0.f,1.f,1.f);

		for ( int i = 0; i<_PAGE_LIMIT_REWARD_; i++ )
		{
			m_rewardFrame[m_selectRewardPage][i].GetPosition( &x, &y);
			w=m_rewardFrame[m_selectRewardPage][i].GetWidth();
			h=m_rewardFrame[m_selectRewardPage][i].GetHeight();

			m_pDraw->VertexDraw( _TEX_BLOCKFRAME_, 
								 x,y,w,h, 
								 0.f,0.f,1.f,1.f);

			//	勲章がゲット出来ていたら
			bool rewardGetCheck = CheckReward(i+(m_selectRewardPage*_PAGE_LIMIT_REWARD_));
			if ( rewardGetCheck )
			{
				int wDiv = i%_REWARD_WIDTH_LIMIT_;
				int hDiv = (m_selectRewardPage*_REWARD_PAGE_MAX_)+i/_REWARD_WIDTH_LIMIT_;


				m_pDraw->AnimationDraw( _TEX_REWARDMAP_, 
										x,y,w,h,
										false,false,
										wDiv,hDiv);

				
			}
			RewardNameDraw( i );
		}
		
		//	cancelボタン描画
		m_cancelButton.GetPosition( &x, &y);
		m_cancelButton.GetColor( tempA, tempR, tempG, tempB );
		m_pDraw->AnimationDraw( _TEX_BUTTONMAP_,x,y, 
								m_cancelButton.GetWidth(),
								m_cancelButton.GetHeight(),
								false,false,1,1,
								D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

		//	矢印ボタン描画
		for ( int i = 0; i < _ARROW_MAX_; i++ )
		{
			bool flipFlag = i%_ARROW_MAX_ ? true:false;
			m_arrowButton[i].GetPosition( &x, &y);
			m_arrowButton[i].GetColor( tempA, tempR, tempG, tempB );
			m_pDraw->AnimationDraw( _TEX_BUTTONMAP_,x,y, 
									m_arrowButton[i].GetWidth(),
									m_arrowButton[i].GetHeight(),
									flipFlag,false,1,2,
									D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));
		}
	}
}

void Reward::RewardNameDraw( int _rewardNum )
{
	DirectXFont* const pDxFont =  &m_pDraw->m_dxFont;
	int logValue = 0;
	unsigned int iTempW = 0, iTempH = 0;
	long lTempX = 0, lTempY = 0;

	logValue = m_rewardName[m_selectRewardPage][_rewardNum].m_logStream.size();
	lTempX = 0; 
	lTempY = 0;
	iTempW = 0; 
	iTempH = 0;
	std::string* pStr;
	LPCSTR lpTempStr;
	std::list<LogStream*>::iterator it = m_rewardName[m_selectRewardPage][_rewardNum].m_logStream.begin();
	(*it)->GetPosition( lTempX, lTempY );
	(*it)->GetSize( iTempW, iTempH );
	pStr = (*it)->GetStringPtr();
	lpTempStr = const_cast<char *>(pStr->c_str());
	if (pDxFont->DrawA( lTempX, lTempY, iTempW, iTempH, lpTempStr, (*it)->GetColor(), (*it)->GetFormat() ))
	{

	}
}