#ifndef	_GAMELOG_H_
#define _GAMELOG_H_
#include <list>
#include "StageDefineList.h"
#include "LogStream.h"

#define _LOG_HEIGHT_MAX_	_BLOCK_HEIGHT_SIZE_*5	///<���O�{�b�N�X�̏c��

/**
*@brief	�Q�[�����ɕ\�������郍�O�N���X
*/
class GameLog
{
public:
	std::list<LogStream*> m_logStream;	///< list�̃A�N�Z�X�����S���Ƃ����R�X�g���f�������̂ŁApublic�ł��B
private:
	long m_posX;	///< ���O�̊�ƂȂ�X���W
	long m_posY;	///< ���O�̊�ƂȂ�Y���W

public:
	GameLog()
	{
		SetPosition( 0, 0 );
	}
	/**
	*@breif	�f�X�g���N�^
	*/
	~GameLog()
	{
		Free();
	}


	/**
	*@brief	������̒ǉ�
	*@param[in] _str	�ǉ�������������
	*@param[in] _width	�f�t�H���g�ł͒萔�錾�����t�H���g�T�C�Y���g��	
	*@param[in] _height	�f�t�H���g�ł͒萔�錾�����t�H���g�T�C�Y���g��
	*/
	void AddStream( const char* _str, const unsigned int _width = _LOG_FONT_WIDTH_, const unsigned int _height = _LOG_FONT_HEIGHT_ );

	/**
	*@brief	�o�^���Ă��镶����̏c�����`�F�b�N
	*@details	�o�^���Ă��镶����̏c�������Z���Ă����A
				�w�肵�����l�ȏ�ɂ������ꍇ�͌�ɓo�^���Ă������̂���폜���Ă���
	*@param[in]	_height	��r�������c���T�C�Y
	*/
	bool CheckStream( const unsigned int _height );

	void GetPosition( long& _x, long& _y )
	{
		_x = m_posX;
		_y = m_posY;
	}

	void SetPosition( const long& _x, const long& _y )
	{
		m_posX = _x;
		m_posY = _y;
	}

	/**
	*@brief	�S�v�f���
	*/
	void Free()
	{
		//	�v�f����Ŗ���������
		if( !m_logStream.empty() ){
			//	�v�f�̉������э폜
			std::list<LogStream*>::const_iterator itEnd = m_logStream.end();
			for( std::list<LogStream*>::iterator it = m_logStream.begin();
				it != itEnd; ++it)
			{
				delete *it;	///< ���g�����
			}
			m_logStream.clear();	///< list�̑S�폜
		}
	}
};


#endif