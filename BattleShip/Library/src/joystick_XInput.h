#ifndef _JS_XINPUT_H_
#define _JS_XINPUT_H_

#include "lib_head.h" 

/**
*@brief	ジョイスティック入力クラス
*/
class CXInput {
 public:

	enum eSTICK_STATE {
		PUSH,		
		ON,
		RELEASE,				
		OFF,		
		PRESS_TWICE,	//	2度押し

		STICK_STATE_MAX
	};

	enum eSTICK_TYPE {

		CROSS_UP,				//	十字キー↑
		CROSS_DOWN,				//	十字キー↓
		CROSS_LEFT,				//	十字キー←
		CROSS_RIGHT,			//	十字キー→
		BUTTON_START,			//	Start
		BUTTON_BACK,			//	Back
		BUTTON_LEFT_THUMB,		//	左スティック押し込み
		BUTTON_RIGHT_THUMB,		//	右スティック押し込み
		BUTTON_LEFT_SHOULDER,	//	ボタンLB
		BUTTON_RIGHT_SHOULDER,	//	ボタンRB
		BUTTON_A,				//	ボタンA
		BUTTON_B,				//	ボタンB
		BUTTON_X,				//	ボタンX
		BUTTON_Y,				//	ボタンY
		L_TRIGGER,				//	左トリガー
		R_TRIGGER,				//	右トリガー

		STICK_TYPE_MAX
	};

	//	xCurrentkStateの情報の一部を保存用
	struct STICK_STATE {
		//	LRトリガーも含めた左右スティック以外のボタン分の配列
		eSTICK_STATE Button[STICK_TYPE_MAX];
	};
	
	//	コンストラクタ
	CXInput();

	//	スティック情報配列の初期化
	void Initialize();

	//	全スティック情報の更新
	void UpdateStick();

	//	StickState配列内からスティックの状態をチェック
	//	@pragma _user	プレイヤー番号（0～3）
	//	@pragma	_type	ボタンの種類
	//	@pragma _state	ボタンの状態
	//	@return	true：スティックが指定した通りの状態、false：指定した状態と違った
	bool CheckStickState( int _user, eSTICK_TYPE _type, eSTICK_STATE _state );
	
 private:	
	//	ボタンのチェック
	//	トリガー以外の状態更新（トリガーは0～255で押され具合も出るので）
	//	@pragma	_user	何番目のスティックか
	void CheckButton( int _user );

	//	トリガーのチェック
	//	右左トリガーの傾き度合いからeSTICK_STATEで判断
	//	@pragma	_user	何番目のスティックか
	void CheckTrigger( int _user );

	//	左右スティックのチェック
	//	段階的に状態を設定するかは検討中
	//	@pragma	_user	何番目のスティックか
	void CheckLRStick( int _user );

	XINPUT_STATE xCurrentkState;	//	XInputGetStateからの情報を受取る用
	STICK_STATE StickState[XUSER_MAX_COUNT];	//	取得可能スティック分の配列

};

#endif