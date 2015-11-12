#ifndef	_GAMELOG_H_
#define _GAMELOG_H_
#include <list>
#include "StageDefineList.h"
#include "LogStream.h"
#include "FixedPhrase.h"

#define _LOG_HEIGHT_MAX_	_BLOCK_HEIGHT_SIZE_*5 -_LOG_POS_TWEAK_-_LOG_FONT_HEIGHT_///<���O�{�b�N�X�̏c��
#define _LOG_POS_TWEAK_		8.0f	///<���O�e�L�X�g��\������ۂ̍��W�������̒萔
#define _LOG_COLOR_DEFAULT_		0xFFFFFFFF	///<���O�e�L�X�g��\������ۂ̃f�t�H���g�J���[�l	
#define _LOG_COLOR_WARNING_		0xFFFF0000	///<�Q�[�����ł̌x���n���O��\������ۂ̃J���[
#define _LOG_COLOR_SUCCESS_		0xFF00FF00	///<�Q�[�����ł̃v���C���[�ɗD�ʓI�ȃ��O��\������ۂ̃J���[
#define _LOG_COLOR_NOMAL_		0xFF0000FF	

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

//	���O�ɕ\�������镶���̒�^������
public:
	const FixedPhrase m_fixedPhrase;

public:
	/**
	*@brief	�R���X�g���N�^
	*@details	�O�̂��߃p�����[�^�Ȃǂ�0�ŏ�����
	*/
	GameLog()
	{
		SetPosition( 0, 0 );
	}

	/**
	*@breif	�f�X�g���N�^
	*/
	~GameLog()
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

	/**
	*@brief	������
	*@details	���O�̕\������Wxy�Ȃ�тɁA�ŏ��ɒǉ������������񂪂���΁A�����Œǉ����鎖���o����B
				������̓f�t�H���g��NULL�Ȃ̂ŁA�ǉ����Ȃ��Ȃ�DirectXFont�N���X��p���ĕ`�悷��ꍇ�ɕK�v�ȏ��͓n���Ȃ��̂Œ��ӁB
	*/
	void Init( const long& _x, const long& _y, const char* _firstStr = NULL );


	/**
	*@brief	������̒ǉ�
	*@param[in] _str	�ǉ�������������
	*@param[in] _color	�f�t�H���g�ł�
	*@param[in] _width	�f�t�H���g�ł͒萔�錾�����t�H���g�T�C�Y���g��	
	*@param[in] _height	�f�t�H���g�ł͒萔�錾�����t�H���g�T�C�Y���g��
	*/
	void AddStream( const char* _str, const D3DXCOLOR& _color = _LOG_COLOR_DEFAULT_ , const unsigned int _width = _LOG_FONT_WIDTH_, const unsigned int _height = _LOG_FONT_HEIGHT_ );

	/**
	*@brief	�o�^���Ă��镶����̏c�����`�F�b�N
	*@details	�o�^���Ă��镶����̏c�������Z���Ă����A
				�w�肵�����l�ȏ�ɂ������ꍇ�͌�ɓo�^���Ă������̂���폜���Ă���
	*@param[in]	_height	��r�������c���T�C�Y
	*/
	bool CheckStream( const unsigned int _height );

	/**
	*@brief	���O�̍Ĕz�u
	*@details	���O���̕����������Ă��`����W�Ȃǂ͕ς���ĂȂ��̂ŁA
				�c���ꂽ������̕`����W�̍Čv�Z�����Ă��K�v������B
	*/
	void RealignmentStream();

	/**
	*@brief	��^������𕡐��q�����킹�đ���֐�
	*@param[in]	�Ȃ����^���̗�
	*/
	const std::string GetMultiplePhrase( int _phraseVal,... );

	void SetPosition( const long& _x, const long& _y )
	{
		m_posX = _x;
		m_posY = _y;
	}

	void GetPosition( long& _x, long& _y )
	{
		_x = m_posX;
		_y = m_posY;
	}

	/**
	*@brief
	*/
	std::string GetPhrase( FixedPhrase::_PHRASE_STR_TYPE_ _phraseType )
	{
		return m_fixedPhrase.m_phrase[ _phraseType ];
	}
};


#endif