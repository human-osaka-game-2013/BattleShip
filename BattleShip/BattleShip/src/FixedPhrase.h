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
		AC_STR=0,	///<���
		BS_STR=1,	///<���
		CR_STR=2,	///<���m��
		DS_STR=3,	///<�쒀��
		SB_STR=4,	///<������

		/*
			��z�u
		*/
		STATE_SET_SHIP_STR,		///<��z�u�̌��o��
		SET_PHRASE_STR,			///<�z�u�𑣂��t���[�Y
		

		/*
			�s���I��
		*/	
		STATE_SELECTION_STR,	///<�s���I���̌��o��
		SELECTION_TAB,			///<�^�u�̑I��
		SELECTION_TYPE_MOVE,	///<�ړ�
		SELECTION_TYPE_ACTION,	///<�U��
		SELECTION_TYPE_SEARCH,	///<���G
		SELECTION_PHRASE_STR,	///<�I���𑣂��t���[�Y
		SELECTION_KO_STR,		///<�s���s�\
		SELECTION_DISABLED,		///<�I��s��
		SELECTION_COMP,			///<�I������

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
		m_phrase[AC_STR]="�w���x";
		m_phrase[BS_STR]="�w��́x";
		m_phrase[CR_STR]="�w���m�́x";
		m_phrase[DS_STR]="�w�쒀�́x";
		m_phrase[SB_STR]="�w�����́x";
		
		m_phrase[STATE_SET_SHIP_STR]	="����̔z�u��";
		m_phrase[SET_PHRASE_STR]		="��z�u���ĉ������B";

		m_phrase[STATE_SELECTION_STR]	="���s���̑I����";
		m_phrase[SELECTION_TAB]			="�̍s�����^�u����";
		m_phrase[SELECTION_TYPE_MOVE]	="�̈ړ��͈͂����w�n����";
		m_phrase[SELECTION_TYPE_ACTION]	="�̍U����G�w�n����";
		m_phrase[SELECTION_TYPE_SEARCH]	="�̍��G��G�w�n����";

		m_phrase[SELECTION_PHRASE_STR]	="�I�����ĉ������B";
		m_phrase[SELECTION_KO_STR]		="���̊͂͐퓬�s�\���ł��B�ΐ푊��̑I���܂ł��҂��������B";
		m_phrase[SELECTION_DISABLED]	="���̍s���͌��݂̊͂ł͏o���܂���B";
		m_phrase[SELECTION_COMP]		="��I�������B";

		m_phrase[STATE_RESULT_STR]		="���퓬���ʁ�";
		m_phrase[RESULT_IMPACT_STR]		="�G�͑D�ɒ��e�I";
		m_phrase[RESULT_HIT_STR]		="�G�ɍU�����ꂽ�I";
		m_phrase[RESULT_SIGHT_STR]		="�𔭌��I";
		m_phrase[RESULT_DISCOVERED_STR]	="�G�ɔ������ꂽ�I";
		m_phrase[RESULT_DEFEAT_STR]		="�䂪�R�̔s�k�ł��E�E�E�B";
		m_phrase[RESULT_INFERIORITY_STR]="�䂪�R�͌��ݗ򐨂ł��B";
		m_phrase[RESULT_DRAW_STR]		="��͂͌��ݝh�R���Ă��܂��B";
		m_phrase[RESULT_SUPERIORITY_STR]="�䂪�R�͌��ݗD���ł��I";
		m_phrase[RESULT_VICTORY_STR]	="�䂪�R�̏����ł��I";	
		m_phrase[RESULT_END]			="���퓬�I���I��";	

		m_phrase[START_BATTLE]			="���퓬�J�n�I��";
	}

	~FixedPhrase()
	{

	}

};

#endif