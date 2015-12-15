#ifndef _REWARD_H_
#define _REWARD_H_
#include "read_file.h"
#include "DrawManager.h"

/**
*@brief	称号の種類列挙
*/
enum _REWARD_TYPE_
{
	_REWARD_MAX_ = 8,
};

/**
*@brief	称号判定クラス
*/
class Reward : public ReadFile
{
private:
	unsigned char m_getRewardFlag;
	CDrawManager* m_pDraw;

public:
	Reward()
	{
		m_getRewardFlag = 0x00;
	}

	void SetTable( char* _p, int _iColumn, int _iLine);
	
	void DrawReward();

	void GetDrawManagerPtr( CDrawManager* _pDraw ){ m_pDraw = _pDraw; }

	/**
	*@brief	称号が取得されているかのチェック
	*/
	bool CheckReward( int _shit )
	{
		unsigned char result;
		result = (m_getRewardFlag & ( 0x01<<_shit ));

		return 	result?true:false;
	}

	/**
	*@brief	称号の取得
	*/
	void GetReward( int _shit )
	{	
		m_getRewardFlag = ( m_getRewardFlag|(0x01<<_shit));
	}
};
#endif