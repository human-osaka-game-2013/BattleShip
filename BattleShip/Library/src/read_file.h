/**
*@file	read_file.h
*@author	�T�c
*/

#ifndef _READ_FILE_H_
#define _READ_FILE_H_
#include <iostream>

#define _READ_FILE_PASS_1_ "table/ConnectData.txt"

/**
*@brief	�t�@�C����ǂݍ���
*@details	text��CSV�`���̃t�@�C����ǂݍ��݁A���l���e�[�u���ɃZ�b�g���邽�߂̃N���X�B@n
			�e�[�u���ɃZ�b�g����ۂ�SetTable�֐��̎��Ԃ����̃N���X���p��������ł��邱�ƁB
*/
class ReadFile
{
public:
	/**
	*@brief	�e�[�u���f�[�^�̓ǂݎ��
	*/
	bool ReadTableData( char* _pFileName, const int _ColumnMax, const int _LineMax );
	
	/**
	*@brief	�ǂݎ�����f�[�^���e�[�u���ɃZ�b�g
	*@details	�e�[�u���f�[�^�͔h���N���X��1��ނ̃t�@�C���݂̂��g�����B@n
				����Ăǂ̃e�[�u���Ƀf�[�^�����邩�̒��߂͔h����̊֐��ōs�����B
	*/
	virtual void SetTable( char* _p, int _iColumn, int _iLine)=0;

};

#endif _READ_FILE_H_