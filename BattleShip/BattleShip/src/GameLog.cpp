#include "GameLog.h"

void GameLog::Init( const long& _x, const long& _y, const char* _firstStr )
{
	SetPosition( _x, _y );
	if( _firstStr != NULL )
	{
		AddStream( _firstStr );
	}
}

void GameLog::AddStream( const char* _str, const D3DXCOLOR& _color, const unsigned int _width, const unsigned int _height )
{
	long tempX = m_posX, tempY = m_posY;

	if( !m_logStream.empty() ){
		//	�ŏI�ɒǉ�����������̍��W����ɁA���̕����̉��ɔz�u�o����悤�ɂ���
		LogStream* const logBack = m_logStream.back();
		logBack->GetPosition( tempX, tempY );
		tempY += logBack->GetHeight();	///< ��{���������ς��Ȃ��̂�Y���W���������̏c�������Z
	}
	m_logStream.push_back( new LogStream( _str, tempX, tempY, _width, _height, _color ) );
	CheckStream( _LOG_HEIGHT_MAX_ );
}


bool GameLog::CheckStream( const unsigned int _height )
{
	bool result = false;

	unsigned int allStreamHeight = 0;	///< �o�^����Ă���S�ĕ�����̏c�������Z
	//	�v�f����Ŗ���������
	if( !m_logStream.empty() ){
		//	�S���̗v�f�̊m�F������
		std::list<LogStream*>::const_iterator itEnd = m_logStream.end();
		for( std::list<LogStream*>::iterator it = m_logStream.begin(); it != itEnd; ++it)
		{
			allStreamHeight += (*it)->GetHeight();	///< �c���̉��Z
		}
	}
	else{
		result = false;	///< ���ׂ�ȑO�ɒ��g����Ȃ̂�false
	}
	
	//	�o�^����Ă���S�Ă̕�����̕����w�肵���l��葽��������
	if( allStreamHeight > _height )
	{
		int tempHeight = 0;	///< �폜����Ώۂ̕�����̍�����ێ����Ă���

		//	��Ԑ擪�i�Â��j�f�[�^��������폜
		std::list<LogStream*>::iterator it = m_logStream.begin();
		tempHeight = (*it)->GetHeight();
		delete *it;
		m_logStream.pop_front();

		RealignmentStream();

		//	�폜���������̍������������čēx�v�Z���āA�܂��͂ݏo�Ă����������x�폜������B
		if( allStreamHeight-tempHeight > _height )
			CheckStream( _height );
		result = true;	///< ���g���폜��������`����ׂ�true
	}
	return result;
}

void GameLog::RealignmentStream()
{
	long tempX = m_posX, tempY = m_posY;	///<���WXY�Z�b�g�p(�擪�Ȃ�GameLog�̕��ɐݒ肵�Ă�����W��n��)
	long beforeHeight = 0;	///<��O�̕�����̍�����������΁AY���W�����炷�����o����

	std::list<LogStream*>::const_iterator itEnd = m_logStream.end();
	for( std::list<LogStream*>::iterator it = m_logStream.begin();
		it != itEnd; ++it)
	{
		tempY += beforeHeight;
		beforeHeight = (*it)->GetHeight();
		(*it)->SetPosition( tempX, tempY );
		(*it)->GetPosition( tempX, tempY );
	}
}