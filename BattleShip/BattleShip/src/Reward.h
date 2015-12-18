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
*@brief	勲章の列挙
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
*@brief	勲章管理クラス
*@details	勲章の獲得有無のセーブデータ。\n
			現状暗号化などは未実装な為、ベタ書きです。
*@todo	暗号化などの実装予定あり
*/
class Reward : public ReadFile
{
private:
	unsigned char m_getRewardFlag;
	CDrawManager* m_pDraw;		///< Rewardクラス単体での描画が出来るとTitleでも汎用が効くと思い、描画管理クラスももたせました。
	BoardOfFrame	m_frame;	///< 勲章表示の際の背景
	BoardOfFrame	m_rewardFrame[_REWARD_PAGE_MAX_][_PAGE_LIMIT_REWARD_];	///< 勲章の描画オブジェクト
	GameLog			m_rewardName[_REWARD_PAGE_MAX_][_PAGE_LIMIT_REWARD_];	///< 勲章の名前
	Button			m_cancelButton;	///< 勲章の表示をやめる際のボタン
	Button			m_arrowButton[_ARROW_MAX_];	

	int		m_selectRewardPage;
	bool	m_drawFlag;

public:
	/**
	*@brief	コンストラクタ
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
		*@details	読み込みが失敗した場合は、失敗した際に作成されたファイルに
					全て0を書き込む
		*/
		if( !readResult )
		{
			SaveToBinaryData( _REWARDSAVEDATA_PASS_, 
						static_cast<void*>(&m_getRewardFlag),
						sizeof(m_getRewardFlag));
		}
	}

	/**
	*@brief	勲章オブジェクトの初期化
	*/
	void InitReward( Audio* _pAudio );

	/**
	*@brief	勲章オブジェクトの処理
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
	*@brief	ファイル読み込み
	*/
	void SetTable( char* _p, int _iColumn, int _iLine);
	
	/**
	*@brief	勲章オブジェクトの描画
	*/
	void DrawReward();

	/**
	*@brief	描画管理オブジェクトのポインタを取得
	*/
	void GetDrawManagerPtr( CDrawManager* _pDraw ){ m_pDraw = _pDraw; }

	/**
	*@brief	勲章が取得されているかのチェック
	*/
	bool CheckReward( int _shift )
	{
		unsigned char result;
		result = (m_getRewardFlag & ( 0x01<<_shift ));

		return 	result?true:false;
	}

	/**
	*@brief	勲章の取得
	*@param[in]	_shift	下位ビットから何番目のデータのフラグを立てるか
	*/
	void GetReward( int _shift )
	{	
		m_getRewardFlag = ( m_getRewardFlag|(0x01<<_shift));
	}

	/**
	*@brief	勲章データの保存
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
	*@brief	勲章の名前描画
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