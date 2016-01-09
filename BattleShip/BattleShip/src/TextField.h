#ifndef _TEXTFIELD_H_
#define _TEXTFIELD_H_

#include "LogStream.h"
#include <cstdio>
/**
*@brief	�e�L�X�g�t�B�[���h�N���X
*@details	���݂�0�`9+,�ɑΉ�
*/
class TextField {
 public:
	/**
	*@brief	�R���X�g���N�^

	*/
	TextField(  const char* _str,
				const long _x,const long _y,
				const float _width,const float _height,
				const unsigned int& _text_w = _LOG_FONT_WIDTH_,
				const unsigned int& _text_h = _LOG_FONT_HEIGHT_ ) 
				: m_str( _str, _x, _y, _text_w, _text_h),  fWidth(_width), fHeight(_height) {
	
		m_settingFlag = false;
	}

	/**
	*@brief	������̒ǉ��i�����j
	*/
	void AddStr( const char* _str ) {
		m_str.AppendStr(_str);
	}
	/**
	*@brief	������̒ǉ�
	*details	���l�𕶎���ɕϊ����Ă���ǉ�Ver
	*/
	void AddStr( int _num ) {
		const unsigned char _word = ConvertNumFromWord(_num);
		char temp[2];
		sprintf_s( temp, "%c", _word );
		AddStr( temp );
	}

	/**
	*@brief	������̃��Z�b�g�i�S�����j
	*/
	void ResetStr() {
		m_str.DeleteStr();
	}
	
	/**
	*@brief	�e�L�X�g�t�B�[���h�̑I���`�F�b�N
	*details	�C�x���g���N�����ہi�}�E�X�������ꂽ���Ȃǁj�Ɏw����W�ƁA
				���g�̃e�L�X�g�t�B�[���h���Ɏw����W���ڐG���Ă��邩�𔻒�B\n
				���݂͑I�����ꂽ���_�ň�x�o�^����Ă��镶�����������

	*/
	bool SelectCheck( float _x, float _y ) {
		long tempX, tempY;
		bool result = false;
		m_str.GetPosition( tempX, tempY );

		if (tempX < static_cast<long>(_x) && tempX + fWidth > static_cast<long>(_x)) {
			if (tempY < static_cast<long>(_y) && tempY + fHeight > static_cast<long>(_y)) {
				m_settingFlag = true;
				ResetStr();	///< �I�𒆂ɂȂ������x
				return m_settingFlag;
			}
		}
		m_settingFlag = false;
		return m_settingFlag;
	}

	bool	m_settingFlag;	///<	���͎�t���t���O
	LogStream m_str;		///<	���͏��i�[������N���X
	float fWidth ,fHeight;	///<	�e�L�X�g�t�B�[���h���̂̕�����

 private:
	/**
	*@brief	���l�𕶎��֕ϊ�
	*details	�ǂ̂悤�ȕ����R�[�h�֕ϊ����邩�͓Ǝ��ɕK�v�ɉ����Ēǉ����Ă��������B\n
				��{�I��AddStr�֐��ƕ��p����`�ɂ��Ă��������B
	*@return	�ϊ�����������1�o�C�g�f�[�^
	*/
	const unsigned char ConvertNumFromWord( int _num );

};

#endif