#include "GameLog.h"

void GameLog::AddStream( const char* _str, const unsigned int _width, const unsigned int _height )
{
	long tempX = m_posX, tempY = m_posY;

	if( !m_logStream.empty() ){
		//	�ŏI�ɒǉ�����������̍��W����ɁA���̕����̉��ɔz�u�o����悤�ɂ���
		LogStream* const logBack = m_logStream.back();
		logBack->GetPosition( tempX, tempY );
		tempY += logBack->GetHeight();	///< ��{���������ς��Ȃ��̂�Y���W���������̏c�������Z
	}
	m_logStream.push_back( new LogStream( _str, tempX, tempY, _width, _height ) );
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
		//	��Ԑ擪�i�Â��j�f�[�^��������폜
		std::list<LogStream*>::iterator it = m_logStream.begin();
		delete *it;
		m_logStream.pop_front();

		result = true;	///< ���g���폜��������`����ׂ�true
	}
	return result;
}