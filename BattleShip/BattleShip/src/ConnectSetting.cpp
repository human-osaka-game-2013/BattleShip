#include "ConnectSetting.h"
#include "DebugInterface.h"

void ConnectSetting::Init( CMouse* const _pMouse, CKey* const _pKey, Audio* const _pAudio )
{
	m_serverButton.Init( _COM_SET_POS_X_,
						 _COM_TYPE_BUTTON_POS_Y_,
						 _COM_TYPE_BUTTON_WIDTH_, 
						 _COM_TYPE_BUTTON_HEIGTH_,
						 _pAudio );

	m_clientButton.Init( _COM_SET_POS_X_+_COM_TYPE_BUTTON_WIDTH_+_COM_TYPE_BUTTON_HEIGTH_,
						 _COM_TYPE_BUTTON_POS_Y_,
						 _COM_TYPE_BUTTON_WIDTH_, 
						 _COM_TYPE_BUTTON_HEIGTH_,
						 _pAudio );

	m_updateButton.Init( m_clientButton.GetPositionX(),
						 _UPDATE_BUTTON_POS_Y_,
						 _COM_TYPE_BUTTON_WIDTH_,
						 _COM_TYPE_BUTTON_HEIGTH_,
						 _pAudio );

	SetMousePtr( _pMouse );
	SetKeyPtr( _pKey );
	SetAudioPtr( _pAudio );

	if ( sockType ) {
		m_clientButton.SetState( Button::STATE_SELECT );
	}else {
		m_serverButton.SetState( Button::STATE_SELECT );
	}
}

//	�O���t�@�C���̏����Z�b�g
void ConnectSetting::SetTable( char* _p, int _iColumn, int _iLine )
{
	
	switch ( _iColumn )
	{
	case 0:
		if ( memcmp( _p, "Server", 6) == 0 ){
			sockType = false;
		}else if ( memcmp( _p, "Client",6) == 0 ){
			sockType = true;
		}
		break;
	case 1:
		if ( sockType ) {	///<	�h���C�������K�v�Ȃ̂̓N���C�A���g�������Ȃ̂�
			if ( memcmp( _p, "localhost", 9) == 0 ) {
				strAddr = "127.0.0.1";
			}else {
				strAddr.append(_p);
				strAddr.pop_back();
			}
		}else {
			if ( memcmp( _p, "localhost", 9) == 0 ) {
				strAddr = "127.0.0.1";
			}else {
				strAddr.append(_p);
				strAddr.pop_back();
			}
		}
		break;
	case 2:
		strPort.append(_p);

		break;
	}
}


bool ConnectSetting::ConvertDataFileFromStr( std::string* _outStr )
{
	//	�O�̂��ߕ���������Z�b�g
	_outStr->erase();
	std::string* pTempStr;

	//	�T�[�o�[or�N���C�A���g
	if ( sockType ){
		_outStr->append("Client\n");
	}else{
		_outStr->append("Server\n");
	}

	//	�A�h���X
	pTempStr = m_ipAddr.m_str.GetStringPtr();
	if ( pTempStr->size() < _IP_STR_MIN_ || pTempStr->size() > _IP_STR_MAX_ ){
		//	�A�h���X�����́ior���l������Ȃ��j����Ă��Ȃ�������A�_�~�[�Ƃ��ă��[�J���z�X�g������
		DebugMsgBox("IP�����͂���Ă��܂���B�܂���IP�A�h���X�Ƃ��ĔF���o���܂���ł����B�m�F���Ă��������B");
		_outStr->append("localhost\n");
		strAddr = "127.0.0.1";
	}else{
		_outStr->append( pTempStr->c_str() );
		_outStr->append("\n");
		strAddr = pTempStr->c_str();
	}

	m_ipAddr.ResetStr();
	m_ipAddr.AddStr(strAddr.c_str());

	//	�|�[�g
	pTempStr = m_port.m_str.GetStringPtr();
	if ( pTempStr->size() <= 2 ){
		//	�|�[�g�ԍ������́ior���l������Ȃ��j����Ă��Ȃ�������A���s�Ƃ݂Ȃ��B
		DebugMsgBox("�|�[�g�ԍ������͂���Ă��܂���B�m�F���Ă��������B");
		return false;
	}else{
		_outStr->append( pTempStr->c_str() );
		strPort = pTempStr->c_str();
	}

	m_port.ResetStr();
	m_port.AddStr(strPort.c_str());

	return true;
}

void ConnectSetting::Control()
{
	
	const float tempX = static_cast<float>(m_pMouse->GetCursorPosX());
	const float tempY = static_cast<float>(m_pMouse->GetCursorPosY());

	char inputState = 0;
	int pushKey = -1;
	inputState = m_pMouse->GetMouseSt( MOUSE_L );


	//	---�T�[�o�[�ƃN���C�A���g�̐؂�ւ��{�^���̏���---
	if ( m_serverButton.Contorl( tempX, tempY, inputState ) == 2 )
	{
		m_clientButton.SetState( Button::STATE_OFF_CURSOR );
		sockType = false;
	}
	if ( m_clientButton.Contorl( tempX, tempY, inputState ) == 2 )
	{
		m_serverButton.SetState( Button::STATE_OFF_CURSOR );
		sockType = true;
	}

	//	�ʐM�ݒ���̍X�V�{�^���̏���
	//	���łɃN���b�N����Ă������x��Ԃ����Z�b�g
	if ( m_updateButton.GetState() == Button::STATE_SELECT )
	{
		m_updateButton.SetState( Button::STATE_OFF_CURSOR );
	}

	//	������Ă�����
	if ( m_updateButton.Contorl( tempX, tempY, inputState ) == 2 )
	{
		//	�t�@�C���f�[�^���X�V����B
		std::string tempStr;
		if ( !ConvertDataFileFromStr( &tempStr ))
			m_serverButton.SetState( Button::STATE_OFF_CURSOR );
		SetDataFile( tempStr );
	}
	
	//	IP���|�[�g�ԍ��̃e�L�X�g�t�B�[���h����
	if ( m_pMouse->MouseStCheck( MOUSE_L, PUSH ))
	{
		bool ipSetting = false, portSetting = false;
		ipSetting = m_ipAddr.SelectCheck( tempX, tempY );
		portSetting = m_port.SelectCheck( tempX, tempY );

		if (ipSetting || portSetting)
		{
			m_pAudio->SoundPlay( Audio::_FAILED_SE_ );
		}
	}
	//	IP�A�h���X�̃e�L�X�g�t�B�[���h���I��
	if ( m_ipAddr.m_settingFlag )
	{
		pushKey = m_pKey->CheckStateToAllKey( PUSH );
		if ( pushKey != -1 ){
			m_ipAddr.AddStr( pushKey );
		}
	}
	//	�|�[�g�ԍ��̃e�L�X�g�t�B�[���h���I��
	if ( m_port.m_settingFlag )
	{
		pushKey = m_pKey->CheckStateToAllKey( PUSH );
		if ( pushKey != -1 ){
			m_port.AddStr( pushKey );
		}
	}
	
}

void ConnectSetting::Draw( CDrawManager* const _pDraw )
{
	float fTempX, fTempY, fTempW, fTempH;
	int tempA, tempR, tempG, tempB;
	long lTempX, lTempY;
	std::string* pStr;
	LPCSTR lpTempStr;

	//	�ʐM�ݒ�{�b�N�X��
	m_port.m_str.GetPosition( lTempX, lTempY );
	_pDraw->VertexDraw( _TEX_GAMELOG_, 
		static_cast<float>(_COM_SET_POS_X_-_COM_TYPE_BUTTON_HEIGTH_),
		static_cast<float>(_COM_TYPE_BUTTON_POS_Y_-_COM_TYPE_BUTTON_HEIGTH_), 
		static_cast<float>((_COM_TYPE_BUTTON_WIDTH_*2)+(_COM_TYPE_BUTTON_HEIGTH_*3)), 
		static_cast<float>((_UPDATE_BUTTON_POS_Y_-_COM_TYPE_BUTTON_POS_Y_)+(_COM_TYPE_BUTTON_HEIGTH_*3)), 
		0.f, 0.f, 1.f, 1.f, 200, 150, 150, 150);

	//	�T�[�o�[�{�^���`��
	m_serverButton.GetPosition( &fTempX, &fTempY );
	fTempW = m_serverButton.GetWidth();
	fTempH = m_serverButton.GetHeight();
	m_serverButton.GetColor( tempA, tempR, tempG, tempB );
	_pDraw->AnimationDraw( _TEX_BUTTONMAP_,fTempX,fTempY,
						   fTempW,fTempH,false,false,0,0,
						   D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

	//	�N���C�A���g�{�^���`��
	m_clientButton.GetPosition( &fTempX, &fTempY );
	fTempW = m_clientButton.GetWidth();
	fTempH = m_clientButton.GetHeight();
	m_clientButton.GetColor( tempA, tempR, tempG, tempB );
	_pDraw->AnimationDraw( _TEX_BUTTONMAP_,fTempX,fTempY,
						   fTempW,fTempH,false,false,0,1,
						   D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

	//	���ݒ�X�V�{�^���`��
	m_updateButton.GetPosition( &fTempX, &fTempY );
	fTempW = m_updateButton.GetWidth();
	fTempH = m_updateButton.GetHeight();
	m_updateButton.GetColor( tempA, tempR, tempG, tempB );
	_pDraw->AnimationDraw( _TEX_BUTTONMAP_,fTempX,fTempY,
						   fTempW,fTempH,false,false,0,2,
						   D3DCOLOR_ARGB(tempA,tempR,tempG,tempB));

	//	IP�e�L�X�g�t�B�[���h�`��
	m_ipAddr.m_str.GetPosition( lTempX, lTempY );
	fTempW = m_ipAddr.fWidth;
	fTempH = m_ipAddr.fHeight;
	_pDraw->VertexDraw( _TEX_GAMELOG_, 
		static_cast<float>(lTempX), static_cast<float>(lTempY), 
		fTempW, fTempH, 0.f, 0.f, 1.f, 1.f);

	//	IP������`��
	pStr = m_ipAddr.m_str.GetStringPtr();
	lpTempStr = const_cast<char *>(pStr->c_str());
	_pDraw->m_dxFont.DrawA( lTempX, lTempY, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), lpTempStr);
	_pDraw->m_dxFont.DrawA( lTempX-_LOG_FONT_BIGSIZE_, lTempY-_LOG_FONT_BIGSIZE_, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), "IP�A�h���X");

	//	�|�[�g�e�L�X�g�t�B�[���h�`��
	m_port.m_str.GetPosition( lTempX, lTempY );
	fTempW = m_port.fWidth;
	fTempH = m_port.fHeight;
	_pDraw->VertexDraw( _TEX_GAMELOG_, 
		static_cast<float>(lTempX), static_cast<float>(lTempY), 
		fTempW, fTempH, 0.f, 0.f, 1.f, 1.f);

	//	�|�[�g������`��
	pStr = m_port.m_str.GetStringPtr();
	lpTempStr = const_cast<char *>(pStr->c_str());
	_pDraw->m_dxFont.DrawA( lTempX, lTempY, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), lpTempStr);
	_pDraw->m_dxFont.DrawA( lTempX-_LOG_FONT_BIGSIZE_, lTempY-_LOG_FONT_BIGSIZE_, 
		static_cast<long>(fTempW), static_cast<long>(fTempH), "�|�[�g�ԍ�");
}

