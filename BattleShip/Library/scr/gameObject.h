/**
*@file	gameObject.h
*@author	亀田
*/
//	多重インクルード防止
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

/**
*@brief	ゲームオブジェクトクラス
*@details	ゲーム内で使うオブジェクトの
*/
class CGameObject
{
public:	
	/**
	*@brief	オブジェクトの向き
	*/
	enum CHARADIRECTION {
		CH_NONE = -1,
		CH_LEFT,
		CH_UP,
		CH_RIGHT,
		CH_DOWN,
		CH_DIRECTION_MAX,
		
	};

	/**
	*@brief	オブジェクトの状態
	*/
	enum CHARASTATE {
		STATE_NONE = -1,
		STATE_WAIT,		
		STATE_WALK,
		STATE_JUMP,	
		STATE_DOWN,
		STATE_DAMAGE,	
		STATE_ATTACK,
		CH_STATE_MAX,
	};

private:	//	メンバ変数
	CHARADIRECTION	m_Dir;		///<	向き
	CHARASTATE		m_State;	///<	状態

	float m_posX;		///<	X座標
	float m_posY;		///<	Y座標
	float m_posZ;		///<	Z座標

	int	m_id;	///<	識別番号（オブジェクト固有のID)

	bool m_deadFlag;	///<	表示などオブジェクトが存在出来るかの判断に使う

public:
	/**
	*@brief	コンストラクタ
	*/
	CGameObject();	

	/**
	*@brief	解放処理
	*/
	virtual void  Free() = 0;

public:	
	/**
	*@brief	移動の仮想関数
	*/
	virtual void Control () = 0;

	/**
	*@brief	描画の仮想関数
	*/
	virtual void Draw() = 0;
	
	/**
	*@brief	gameObjectオブジェクトの基準点が範囲内に入っているかの当たり判定
	*@details	
	*@param[in]	_left	当たり範囲の最左値
	*@param[in]	_top	当たり範囲の最上値
	*@param[in]	_right	当たり範囲の最右値
	*@param[in]	_bottom	当たり範囲の最下値
	*/
	bool HitCheck( float _left, float _top, float _right, float _bottom );

public:	// アクセッサ
	/*
	*@brief	向きをセット
	*@param[in]	_dir	向き（右or左）
	*/
	void SetDirection ( CHARADIRECTION _dir ){ m_Dir = _dir; }
	/*
	*@brief	状態をセット
	*@param[in]	_state	状態（待機、攻撃など）
	*/
	void SetState ( CHARASTATE _state ){ m_State = _state; }
	/*
	*@brief	座標（X,Y,Z）をセット
	*@param[in]	_x
	*@param[in]	_y
	*@param[in]	_z
	*/
	void SetPosition ( float _x, float _y, float _z );

	/*
	*@brief	座標（X）をセット
	*@param[in]	_x
	*/
	void SetPositionX ( float _x ){	m_posX = _x;	}
	/*
	*@brief	座標（Y）をセット
	*@param[in]	_y
	*/
	void SetPositionY ( float _y ){	m_posY = _y;	}
	/*
	*@brief	座標（Z）をセット
	*@param[in]	_z
	*/
	void SetPositionZ ( float _z ){	m_posZ = _z;	}
	/*
	*@brief	識別番号をセット
	*@param	_id	ID（int型）
	*/
	void SetID( int _id ){	m_id = _id;	}
	/*
	*@brief	DeadFlagをセット
	*@param	_dFlag	ID（bool型）
	*/
	void SetDeadFlag( bool _dFlag ){	m_deadFlag = _dFlag;	}
	/*
	*@brief	向きの取得
	*@return	m_Dir	向き（右or左）
	*/
	CHARADIRECTION GetDirection (){	return m_Dir;	}
	/*
	*@brief	状態の取得
	*@return	m_State	状態（待機、攻撃など）
	*/
	CHARASTATE GetState (){	return m_State;	}
	/*
	*@brief	座標情報（X,Y）の取得
	*@param[in]	p_x	座標X
	*@param[in]	p_y	座標Y
	*/
	void GetPosition ( float* p_x, float* p_y );
	/*
	*@brief	座標情報（X）の取得
	*@return	m_posX	座標情報（X）
	*/
	float GetPositionX (){ return m_posX; }
	/*
	*@brief	座標情報（Y）の取得
	*@return	m_posY	座標情報（Y）
	*/
	float GetPositionY (){ return m_posY; }
	/*
	*@brief	座標情報（Z）の取得
	*@return	m_posZ	座標情報（Z）
	*/
	float GetPositionZ (){ return m_posZ; }
	/*
	*@brief	識別番号を取得
	*@return	識別番号（int型）
	*/
	int GetID(){ return m_id; }
	/*
	*@brief	識別番号を取得
	*@return	識別番号（bool型）
	*/
	bool GetDeadFlag(){	return m_deadFlag;	}
};

#endif