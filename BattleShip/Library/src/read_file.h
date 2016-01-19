/**
*@file	read_file.h
*@author	�T�c
*/

#ifndef _READ_FILE_H_
#define _READ_FILE_H_
#include <iostream>

#define _CONNECTDATA_PASS_ "table/ConnectData.csv"

/**
*@brief	�t�@�C����ǂݍ���
*@details	text��CSV�`���̃t�@�C����ǂݍ��݁A���l���e�[�u���ɃZ�b�g���邽�߂̃N���X�B@n
			�e�[�u���ɃZ�b�g����ۂ�SetTable�֐��̎��Ԃ����̃N���X���p��������ł��邱�ƁB
*/
class ReadFile {
 public:
	/**
	*@brief	�e�[�u���f�[�^�̓ǂݎ��
	*/
	bool ReadTableData( char* _pFileName, const int _ColumnMax, const int _LineMax );
	
	/**
	*@brief	�����񂩂�f�[�^�t�@�C���ɕϊ�
	*@details	��������f�[�^�t�@�C���ɃZ�b�g�o����悤�ɕϊ�����B
				SetDataFile�֐���p����ۂɂ��̊֐����e�N���X�ŃI�[�o�[���C�h���Ďg���ĉ������B
	*@retval false	�f�[�^�t�@�C���ɃZ�b�g����f�[�^�ɕs�����������B
	*@retval true	����
	*/
	virtual bool ConvertDataFileFromStr( std::string* _outStr ){ return true; }

	/**
	*@brief	�f�[�^�t�@�C���֏��Z�b�g
	*/
	bool SetDataFile( const std::string& _str );

	/**
	*@brief	�ǂݎ�����f�[�^���e�[�u���ɃZ�b�g
	*@details	�e�[�u���f�[�^�͔h���N���X��1��ނ̃t�@�C���݂̂��g�����B@n
				����Ăǂ̃e�[�u���Ƀf�[�^�����邩�̒��߂͔h����̊֐��ōs�����B
	*/
	virtual void SetTable( char* _p, int _iColumn, int _iLine)=0;

	/**
	*@brief	�����񂩂�01�̃o�C�g�f�[�^�ɏ�������
	*/
	static unsigned char StrToUChar(const char *ptr) {
	    unsigned char val = 0x00;
		int i = 0;
	    while ( *ptr != '\0' ) {
	        switch ( *ptr++ ) {
	            case '0':
	                val = val|(0x00<<i);
	                break;
	            case '1':
	                val = val|(0x01<<i);
	                break;
	        }
			i++;
	    }
	    return val;
	}

	/**
	*@brief	�o�C�i���f�[�^�`���ŕۑ�
	*/
	bool SaveToBinaryData( char* _pFileName, void* _data, int _size );

	/**
	*@brief	�o�C�i���f�[�^�`���̃t�@�C����ǂݍ���
	*/
	bool ReadBinaryData( char* _pFileName, void* _data, int _size );
		
};

#endif _READ_FILE_H_