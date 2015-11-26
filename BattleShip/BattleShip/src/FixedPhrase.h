#ifndef _FIXEDPHRASE_H_
#define _FIXEDPHRASE_H_
#include <string>

/**
*@brief	ゲーム内で使う定型文字列の列挙をするクラス
*/
class FixedPhrase
{
//	定型文字列の種類
public:
	/**
	*@brief	使用する定型文字列の列挙
	*@details	使う文字列があればここに列挙していき、m_phraseに代入していくこと	
	*/
	enum _PHRASE_STR_TYPE_
	{
		/*
			艦種
		*/
		AC_STR=0,	///<空母
		BS_STR=1,	///<戦艦
		CR_STR=2,	///<巡洋艦
		DS_STR=3,	///<駆逐艦
		SB_STR=4,	///<潜水艦

		/*
			駒配置
		*/
		STATE_SET_SHIP_STR,		///<駒配置の見出し
		SET_PHRASE_STR,			///<配置を促すフレーズ
		

		/*
			行動選択
		*/	
		STATE_SELECTION_STR,	///<行動選択の見出し
		SELECTION_TAB,			///<タブの選択
		SELECTION_TYPE_MOVE,	///<移動
		SELECTION_TYPE_ACTION,	///<攻撃
		SELECTION_TYPE_SEARCH,	///<索敵
		SELECTION_PHRASE_STR,	///<選択を促すフレーズ
		SELECTION_KO_STR,		///<行動不能
		SELECTION_DISABLED,		///<選択不可
		SELECTION_COMP,			///<選択完了

		/*
			戦闘結果
		*/
		STATE_RESULT_STR,		///<戦闘結果の見出し
		RESULT_IMPACT_STR,		///<着弾
		RESULT_HIT_STR,			///<被弾
		RESULT_SIGHT_STR,		///<発見した
		RESULT_DISCOVERED_STR,	///<発見された
		RESULT_DEFEAT_STR,		///<敗北
		RESULT_INFERIORITY_STR,	///<劣勢
		RESULT_DRAW_STR,		///<引き分け
		RESULT_SUPERIORITY_STR,	///<優勢
		RESULT_VICTORY_STR,		///<勝利
		RESULT_END,				///<戦闘終了


		/*
			その他
		*/
		START_BATTLE,

		STR_MAX
	};

public:
	std::string m_phrase[STR_MAX];

public:
	/**
	*@brief	コンストラクタ
	*/
	FixedPhrase()
	{
		m_phrase[AC_STR]="『空母』";
		m_phrase[BS_STR]="『戦艦』";
		m_phrase[CR_STR]="『巡洋艦』";
		m_phrase[DS_STR]="『駆逐艦』";
		m_phrase[SB_STR]="『潜水艦』";
		
		m_phrase[STATE_SET_SHIP_STR]	="＜駒の配置＞";
		m_phrase[SET_PHRASE_STR]		="を配置して下さい。";

		m_phrase[STATE_SELECTION_STR]	="＜行動の選択＞";
		m_phrase[SELECTION_TAB]			="の行動をタブから";
		m_phrase[SELECTION_TYPE_MOVE]	="の移動範囲を自陣地から";
		m_phrase[SELECTION_TYPE_ACTION]	="の攻撃を敵陣地から";
		m_phrase[SELECTION_TYPE_SEARCH]	="の索敵を敵陣地から";

		m_phrase[SELECTION_PHRASE_STR]	="選択して下さい。";
		m_phrase[SELECTION_KO_STR]		="この艦は戦闘不能中です。対戦相手の選択までお待ち下さい。";
		m_phrase[SELECTION_DISABLED]	="その行動は現在の艦では出来ません。";
		m_phrase[SELECTION_COMP]		="を選択完了。";

		m_phrase[STATE_RESULT_STR]		="＜戦闘結果＞";
		m_phrase[RESULT_IMPACT_STR]		="敵艦船に着弾！";
		m_phrase[RESULT_HIT_STR]		="敵に攻撃された！";
		m_phrase[RESULT_SIGHT_STR]		="を発見！";
		m_phrase[RESULT_DISCOVERED_STR]	="敵に発見された！";
		m_phrase[RESULT_DEFEAT_STR]		="我が軍の敗北です・・・。";
		m_phrase[RESULT_INFERIORITY_STR]="我が軍は現在劣勢です。";
		m_phrase[RESULT_DRAW_STR]		="戦力は現在拮抗しています。";
		m_phrase[RESULT_SUPERIORITY_STR]="我が軍は現在優勢です！";
		m_phrase[RESULT_VICTORY_STR]	="我が軍の勝利です！";	
		m_phrase[RESULT_END]			="＜戦闘終了！＞";	

		m_phrase[START_BATTLE]			="＜戦闘開始！＞";
	}

	~FixedPhrase()
	{

	}

};

#endif