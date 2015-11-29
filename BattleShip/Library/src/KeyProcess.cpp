#include "device.h"
#include "Key.h"

//	�R���X�g���N�^
CKey::CKey( IDirectInputDevice8* const _pKeyDevice ): m_pKeyDevice(_pKeyDevice)
{
	for( int iCount = 0; iCount < KEYMAX; iCount++)
	{
		m_key[iCount] = OFF;
		m_preKey[iCount] = false;
	}
	
}

//	�L�[��ԃ`�F�b�N
void CKey::KeyCheck ( int _dik, int _st )
{
	HRESULT hr = m_pKeyDevice->Acquire();		//�f�o�C�X�ւ̃A�N�Z�X���̍Ď擾
	
	//	�f�o�C�X�ւ̃A�N�Z�X���͂��邩
	if( (hr==DI_OK) || (hr==S_FALSE) )	
	{
		BYTE diks[256];
		//	�f�o�C�X�����擾
		m_pKeyDevice->GetDeviceState(sizeof (diks), &diks);

		if ( diks[_dik] & 0x80 )
		{
			if ( !m_preKey[_st] )
			{
				m_key[_st] = PUSH;
			}
			else
			{
				m_key[_st] = ON;
			}
			m_preKey[_st] = true;
		}
		else
		{
			if ( !m_preKey[_st] )
			{
				m_key[_st] = OFF;
			}
			else
			{
				m_key[_st] = RELEASE;
			}
			m_preKey[_st] = false;
		}
	}
}

//	�L�[�ʏ�Ԕ���
bool CKey::StCheck(int _st, int _keySt)
{
	return ( m_key[_st] == _keySt );
}

//	�S�ẴL�[�̏�ԃ`�F�b�N
void CKey::AllKeyCheck ()
{
	KeyCheck ( DIK_0, KEY_0 );
	KeyCheck ( DIK_1, KEY_1 );
	KeyCheck ( DIK_2, KEY_2 );
	KeyCheck ( DIK_3, KEY_3 );
	KeyCheck ( DIK_4, KEY_4 );
	KeyCheck ( DIK_5, KEY_5 );
	KeyCheck ( DIK_6, KEY_6 );
	KeyCheck ( DIK_7, KEY_7 );
	KeyCheck ( DIK_8, KEY_8 );
	KeyCheck ( DIK_9, KEY_9 );
	KeyCheck ( DIK_COMMA, COMMA );
	
}
