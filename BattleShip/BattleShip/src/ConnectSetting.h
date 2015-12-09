#ifndef _CONNECTSETTING_H_
#define _CONNECTSETTING_H_

#include "DrawManager.h"
#include "Button.h"
#include "Mouse.h"
#include "Key.h"
#include "Audio.h"
#include "read_file.h"
#include "TextField.h"

#define _COM_SET_POS_X_	static_cast<long>(WIDTH*0.7)
#define	_COM_TYPE_BUTTON_POS_Y_		static_cast<long>(HEIGHT*0.6)
#define	_COM_TYPE_BUTTON_WIDTH_		80
#define	_COM_TYPE_BUTTON_HEIGTH_	30
#define _COM_SET_WIDTH_	200

#define _IP_TEXT_POS_Y_	_COM_TYPE_BUTTON_POS_Y_+_COM_TYPE_BUTTON_HEIGTH_+(_COM_TYPE_BUTTON_HEIGTH_*2)
#define _PORT_TEXT_POS_Y_	_IP_TEXT_POS_Y_+_LOG_FONT_BIGSIZE_+_COM_TYPE_BUTTON_HEIGTH_

#define _UPDATE_BUTTON_POS_Y_	_PORT_TEXT_POS_Y_+_COM_TYPE_BUTTON_WIDTH_

#define _IP_STR_MIN_ 9	///< IP�A�h���X�̓��͕�����̉���
#define _IP_STR_MAX_ 17	///< IP�A�h���X�̓��͕�����̏��

/**
*@brief	�ʐM�ݒ�N���X
*/
class ConnectSetting : public ReadFile
{
private:
	bool		sockType;	///< ���X�̒ʐݒ�t�@�C���̃f�[�^�����ۑ��p
	std::string strAddr;	///< ���X�̒ʐݒ�t�@�C���̃f�[�^�����ۑ��p
	std::string strPort;	///< ���X�̒ʐݒ�t�@�C���̃f�[�^�����ۑ��p

private:
	CMouse*		m_pMouse;	///< �}�E�X�|�C���^
	CKey*		m_pKey;		///< �L�[�|�C���^
	Audio*		m_pAudio;	
	TextField	m_ipAddr;	///< IP�A�h���X�e�L�X�g�t�B�[���h
	TextField	m_port;		///< �|�[�g�ԍ��e�L�X�g�t�B�[���h
	Button		m_serverButton;	///< �T�[�o�[�{�^�� 
	Button		m_clientButton;	///< �N���C�A���g�{�^��
	Button		m_updateButton;	

public:
	ConnectSetting():
		strAddr(""), strPort(""), 
		m_ipAddr( "", _COM_SET_POS_X_, _IP_TEXT_POS_Y_, _COM_SET_WIDTH_, _LOG_FONT_BIGSIZE_),
		m_port( "", _COM_SET_POS_X_, _PORT_TEXT_POS_Y_, _COM_SET_WIDTH_, _LOG_FONT_BIGSIZE_)
	{
		ReadTableData( _READ_FILE_PASS_1_, 3, 1 );
		m_ipAddr.ResetStr();
		m_ipAddr.AddStr(strAddr.c_str());
		m_port.ResetStr();
		m_port.AddStr(strPort.c_str());
	}

	void Init( CMouse* const _pMouse, CKey* const _pKey, Audio* const _pAudio );

	void Control();

	void Draw( CDrawManager* const _pDraw );

	/**
	*@brief	�ǂݎ�����f�[�^���e�[�u���ɃZ�b�g
	*@details	�ʐM�ݒ�̃f�[�^���O���t�@�C������ǂݎ��A����ɍ��������o�ϐ��ɃZ�b�g����B
	*/
	void SetTable( char* _p, int _iColumn, int _iLine );

	/**
	*@brief	�����񂩂�f�[�^�t�@�C���ɕϊ�
	*/
	bool ConvertDataFileFromStr( std::string* _outStr );

	void SetMousePtr( CMouse* const _pMouse ){ m_pMouse = _pMouse; }
	void SetKeyPtr( CKey* const _pKey ){ m_pKey = _pKey; }
	void SetAudioPtr( Audio* const _pAudio ){ m_pAudio = _pAudio; }
};

#endif