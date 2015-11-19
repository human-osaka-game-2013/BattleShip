#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <Windows.h>
#include <XAudio2.h>	//mp3,wma�Đ�

/**
*@brief	���y�t�@�C���N���X�i����wav�t�@�C���̂݁j
*@details	���g�p�@\n
	�A�v���J�n����Win_Main�Ōďo
	InitXAudio2
	
	��ɃV�[�����������Ōďo
		LoadSoundFile
			->	OpenWaveFile	(�����Ōďo�E�E�E�K�v�ȃt�@�C�����������Ń��[�h)

		//�T�E���h�̎g�p��������ʂŌďo
		SoundPlay, SoundStop, SoundAllStop

	//��ɃV�[���ڍs���Ōďo
		ReleaseSoundFile, ReleaseAllSoundFile

	�A�v���I�����Ƀ����[�X�����Ōďo
			ReleaseXAudio2
*/
class Audio
{

public:
	enum SOUND_ID
	{
		//�@BGM�̋Ȑ���p��
		_TITLE_BGM_,
		_BATTLE_BGM_,
		_WIN_BGM_,
		_LOSE_BGM_,
		
		//�@SE�̋Ȑ���p��
		_FIRE_L_SE_,
		_FIRE_M_SE_,
		_FIRE_H_SE_,

		_AIRCRAFT_SE_,
		_AC_ATTACK_SE_,
		_SONAR_SE_,
		_WATER_SE_,
		_EXPLOSION_SE_,

		//�z��O�␳
		SOUND_MAX

	};
	
private:
	//�f�o�C�X�̏���
	IXAudio2*				pXAudio2;
	IXAudio2MasteringVoice*	pMasteringVo;
	IXAudio2SourceVoice*	pSourceVo[SOUND_MAX];
	XAUDIO2_BUFFER			buffer[SOUND_MAX];
	
public:
	/**
	*@brief	�R���X�g���N�^
	*/
	Audio()
	{
		InitXAudio2();

		LoadAllSoundFile();
	}
	
	/**
	*@brief	�f�X�g���N�^
	*/
	~Audio()
	{
		SoundAllStop();
		
		ReleaseAllSoundFile();
		
		ReleaseXAudio2();
	}
	
public:
	//XAudio�̏�����
	HRESULT InitXAudio2(void);

	//�T�E���h�S�ǂݍ���
	void LoadAllSoundFile();

	//�T�E���h�Đ�
	void SoundPlay(int ID, bool LOOP = false);

	//�T�E���h��~
	void SoundStop(int ID);

	//�T�E���h�S��~
	void SoundAllStop(void);
	
	//�t�@�C��->�S���
	void ReleaseAllSoundFile(void);

private:	
	
	//�����t�@�C���̓ǂݍ���	->	��͂ł�����g�p��������
	void LoadSoundFile(LPSTR FileName, int IN_ID);
	
	//�Ǎ���.wav�t�@�C�����J���ĉ��
	bool OpenWaveFile(LPSTR FileName, WAVEFORMATEX &waveFormatEx, BYTE **ppData, DWORD &dataSize);

	//�t�@�C��->���
	void ReleaseSoundFile(int ID);
	
	//XAudio�̉��
	HRESULT ReleaseXAudio2(void);

}

#endif