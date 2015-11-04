#ifndef _LOGSTREAM_H_
#define _LOGSTREAM_H_

#include <string>
#define _LOG_FONT_WIDTH_	160
#define _LOG_FONT_HEIGHT_	160

/**
*@brief	�Q�[�����ł̃��O�̕�������N���X
*@details	GameLog�N���X��vector�Ȃǂł��̃I�u�W�F�N�g��ǉ����Ă����\��
*/
class LogStream
{
private:
	std::string		m_logStr;	///<	���O�ŕ\����������1�s��������
	
	long			m_x;		///<	������̊�_X
	long			m_y;		///<	������̊�_Y
	unsigned int	m_width;	///<	�ꕶ�����̉���
	unsigned int	m_height;	///<	�ꕶ�����̏c��

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	LogStream( const char* _str, const long _x, const long _y,
		const unsigned int& _width, const unsigned int& _height )
	{
		SetString( _str );
		SetPosition( _x, _y );
		SetSize( _width, _height );
	}

	/**
	*@brief	������Z�b�g
	*@param[in] _str�@�Z�b�g������������
	*/
	void SetString( const char* _str )
	{
		m_logStr = _str;
	}

	/**
	*@brief	������̈ꕶ���̃T�C�Y�Z�b�g
	*@param[in] _width	1�����̉���
	*@param[in] _height	1�����̏c��
	*/
	void SetSize( const unsigned int& _width, const unsigned int& _height )
	{
		m_width	= _width;
		m_height= _height;
	}

	/**
	*@brief	������̊�_�Z�b�g
	*@param[in] _x
	*@param[in] _y
	*/
	void SetPosition( const long& _x, const long& _y )
	{
		m_x = _x;
		m_y = _y;
	}

	/**
	*@brief	������|�C���^�擾
	*/
	std::string* GetStringPtr(){ return &m_logStr; }

	/**
	*@brief	������̈ꕶ���̃T�C�Y�擾
	*@param[out] _width		1�����̉���
	*@param[out] _height	1�����̏c��
	*/
	void GetSize( unsigned int& _width, unsigned int& _height)
	{
		_width	= m_width;
		_height	= m_height;
	}

	/**
	*@brief	������̊�_�擾
	*@param[out] _x
	*@param[out] _y
	*/
	void GetPosition( long& _x, long& _y)
	{
		_x = m_x;
		_y = m_y;
	}

	unsigned int GetHeight(){ return m_height; }

};

#endif