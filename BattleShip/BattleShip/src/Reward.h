#ifndef _REWARD_H_
#define _REWARD_H_
#include "read_file.h"
#include "DrawManager.h"

/**
*@brief	�̍��̎�ޗ�
*/
enum _REWARD_TYPE_
{
	_REWARD_MAX_ = 8,
};

/**
*@brief	�̍�����N���X
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
	*@brief	�̍����擾����Ă��邩�̃`�F�b�N
	*/
	bool CheckReward( int _shit )
	{
		unsigned char result;
		result = (m_getRewardFlag & ( 0x01<<_shit ));

		return 	result?true:false;
	}

	/**
	*@brief	�̍��̎擾
	*/
	void GetReward( int _shit )
	{	
		m_getRewardFlag = ( m_getRewardFlag|(0x01<<_shit));
	}
};
#endif