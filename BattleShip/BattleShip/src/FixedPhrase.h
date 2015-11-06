#ifndef _FIXEDPHRASE_H_
#define _FIXEDPHRASE_H_
#include <string>

/**
*@brief	�Q�[�����Ŏg����^������̗񋓂�����N���X
*/
class FixedPhrase
{
//	��^������̎��
public:
	/**
	*@brief	�g�p�����^������̗�
	*@details	�g�������񂪂���΂����ɗ񋓂��Ă����Am_phrase�ɑ�����Ă�������	
	*/
	enum _PHRASE_STR_TYPE_
	{
		/*
			�͎�
		*/
		AC_STR,	///<���
		BS_STR,	///<���
		CR_STR,	///<���m��
		DS_STR,	///<�쒀��
		SB_STR,	///<������

		/*
			��z�u
		*/
		STATE_SET_SHIP_STR,		///<��z�u�̌��o��
		SET_PHRASE_STR,			///<�z�u�𑣂��t���[�Y
		

		/*
			�s���I��
		*/	
		STATE_SELECTION_STR,	///<�s���I���̌��o��
		SELECTION_PHRASE_STR,	///<�I���𑣂��t���[�Y
		SELECTION_KO_STR,		///<�s���s�\
		SELECTION_DISABLED,		///<�I��s��

		/*
			�퓬����
		*/
		STATE_RESULT_STR,		///<�퓬���ʂ̌��o��
		RESULT_IMPACT_STR,		///<���e
		RESULT_HIT_STR,			///<��e
		RESULT_SIGHT_STR,		///<��������
		RESULT_DISCOVERED_STR,	///<�������ꂽ
		RESULT_DEFEAT_STR,		///<�s�k
		RESULT_INFERIORITY_STR,	///<��
		RESULT_DRAW_STR,		///<��������
		RESULT_SUPERIORITY_STR,	///<�D��
		RESULT_VICTORY_STR,		///<����
		RESULT_END,				///<�퓬�I��


		/*
			���̑�
		*/
		START_BATTLE,

		STR_MAX
	};

public:
	std::string m_phrase[STR_MAX];

public:
	/**
	*@brief	�R���X�g���N�^
	*/
	FixedPhrase()
	{
		m_phrase[AC_STR]="���";
		m_phrase[BS_STR]="���";
		m_phrase[CR_STR]="���m��";
		m_phrase[DS_STR]="�쒀��";
		m_phrase[SB_STR]="������";
		
		m_phrase[STATE_SET_SHIP_STR]	="�@�@�@����̔z�u��";
		m_phrase[SET_PHRASE_STR]		="��z�u���ĉ������B";

		m_phrase[STATE_SELECTION_STR]	="�@�@�@���s���̑I����";
		m_phrase[SELECTION_PHRASE_STR]	="�̍s����I�����ĉ������B";
		m_phrase[SELECTION_KO_STR]		="�퓬�s�\";
		m_phrase[SELECTION_DISABLED]	="���̍s���͌��݂̊͂ł͏o���܂���B";
		
		m_phrase[STATE_RESULT_STR]		="�@�@�@���퓬���ʁ�";
		m_phrase[RESULT_IMPACT_STR]		="�G�ɒ��e�I";
		m_phrase[RESULT_HIT_STR]		="�G�ɍU�����ꂽ�I";
		m_phrase[RESULT_SIGHT_STR]		="���G�͈͓��ɓG�𔭌��I";
		m_phrase[RESULT_DISCOVERED_STR]	="�G�ɔ������ꂽ�I";
		m_phrase[RESULT_DEFEAT_STR]		="�䂪�R�̔s�k�ł��E�E�E�B";
		m_phrase[RESULT_INFERIORITY_STR]="�䂪�R�͌��ݗ򐨂ł��B";
		m_phrase[RESULT_DRAW_STR]		="��͂͌��ݝh�R���Ă��܂��B";
		m_phrase[RESULT_SUPERIORITY_STR]="�䂪�R�͌��ݗD���ł��I";
		m_phrase[RESULT_VICTORY_STR]	="�䂪�R�̏����ł��I";	
		m_phrase[RESULT_END]			="�@�@�@���퓬�I���I��";	

		m_phrase[START_BATTLE]			="�@�@�@���퓬�J�n�I��";
	}

	~FixedPhrase()
	{

	}

};

#endif