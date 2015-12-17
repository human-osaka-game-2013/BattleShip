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

/**
*@brief	勲章の種類列挙
*/
enum _REWARD_TYPE_
{

	_UPPER_REWARD_MAX_ = 5,

	_REWARD_MAX_ = 10,
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
	BoardOfFrame	m_rewardFrame[_REWARD_MAX_]; ///< 勲章の描画オブジェクト
	GameLog			m_rewardName[_REWARD_MAX_];	 ///< 勲章の名前
	Button			m_cancelButton;	///< 勲章の表示をやめる際のボタン

	bool	m_drawFlag;

public:
	Reward()
	{
		m_getRewardFlag = 0x00;
		m_drawFlag = false;

		ReadBinaryData( _REWARDSAVEDATA_PASS_, 
						static_cast<void*>(&m_getRewardFlag),
						sizeof(m_getRewardFlag));
		
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