/**
*@file	Selection.cpp
*@author	亀田
*/

#include "Selection.h"

bool Selection::Init()
{
	/*
		基本的なメンバの初期化
		プレイヤー別でタブの表示位置をずらす必要がある。
	*/
	m_arrayCheckResult = 0;
	m_plyaerSelectType = _SELECT_NONE_;
	
	m_tempShip = m_pPlayer[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)(m_ShipCount) );
		
	m_actionFrame.Init( m_tempShip->GetPositionX()-(m_playerID/2*_TAB_WIDTH_), m_tempShip->GetPositionY()+_TAB_HEIGHT_*2, 
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_actionFrame.SetColor( 255, 255, 255, 255 );
	
	m_searchFrame.Init( m_tempShip->GetPositionX()-(m_playerID/2*_TAB_WIDTH_), m_tempShip->GetPositionY()+_TAB_HEIGHT_,
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_searchFrame.SetColor( 255, 255, 255, 255 );

	m_moveFrame.Init( m_tempShip->GetPositionX()-(m_playerID/2*_TAB_WIDTH_), m_tempShip->GetPositionY(),
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_moveFrame.SetColor( 255, 255, 255, 255 );

	return false;
	
}

//	
int Selection::Control()
{
	m_tempX = static_cast<float>(m_pMouse->GetCursorPosX());
	m_tempY = static_cast<float>(m_pMouse->GetCursorPosY());

	if ( !m_StateCompFlag )
	{
		if ( !m_selectionFlag )
		{
			bool deadFlag = m_pPlayer[m_playerID-1]->CheckDestroy( static_cast<ShipObject::_SHIP_TYPE_NUM_>( m_ShipCount) );
			if ( deadFlag )
			{
				m_tempStr1 = m_pGameLog->GetPhrase( FixedPhrase::SELECTION_KO_STR );
				m_pGameLog->AddStream( m_tempStr1.c_str(), D3DXCOLOR( _LOG_COLOR_WARNING_ ) );
				m_connectFlag = true;	///<	通信フラグを立てて通信の準備に移る
				m_StateCompFlag = true;	///<	行動選択自体は完了したので、フラグを立てる
			}
			else
			{
				m_tempStr1 = m_pGameLog->GetMultiplePhrase( 3, m_ShipCount,
					static_cast<int>(FixedPhrase::SELECTION_TAB), 
					static_cast<int>(FixedPhrase::SELECTION_PHRASE_STR));
				m_pGameLog->AddStream( m_tempStr1.c_str(), D3DXCOLOR( _LOG_COLOR_NOMAL_ ) );
				m_selectionFlag = _SELECT_LOG_BIT_;
			}
		}
		else if ( !(m_selectionFlag>>1) )	///<	タブがまだ選ばれていない場合
		{
			
			m_selectionFlag = TabCheck()? (m_selectionFlag+_TAB_SELECT_BIT_): m_selectionFlag;
		}
		else if ( !(m_selectionFlag>>2) )	///<	対象エリアなどの選択が終わっていない場合
		{
			m_selectionFlag = SetTypeArray()?(m_selectionFlag+_AREA_SELECT_BIT_): m_selectionFlag>>1;
			if ( !m_selectionFlag>>2 )	///< 選択した範囲にデータが無い（orその行動は出来ない）場合、タブの選択も解除する。
				m_selectionFlag = m_selectionFlag>>1;
		}
		else if ( m_arrayCheckResult != 2 )	///<	選択した範囲は有効で無い場合
		{
			m_pStage->ResetSelect();
			m_arrayCheckResult = SelectArrayCheck();
			
		}
		else{	///<	行動選択も範囲選択完了した場合
			m_connectFlag = true;	///<	通信フラグを立てて通信の準備に移る
			m_StateCompFlag = true;	///<	行動選択自体は完了したので、フラグを立てる
			m_pAudio->SoundPlay( Audio::_CLICK_SE_ );
		}
		
	}

	return ((m_StateCompFlag) ? 1 : 0);
}


bool Selection::TabCheck()
{
	ResetTabFrame();
	bool tempFlag = false;

	//	選択タブごとのマウスとの接触判定
	if ( m_actionFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		//	攻撃のタブ
		m_actionFrame.SetColor( 255, 150, 150, 150 );
		if ( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			
			m_plyaerSelectType = _SELECT_ACTION_;
			tempFlag = true;
		}
	}
	if ( m_searchFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		//	索敵のタブ
		m_searchFrame.SetColor( 255, 150, 150, 150 );
		if ( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			
			m_plyaerSelectType = _SELECT_SEARCH_;
			tempFlag = true;
		}
	}
	if ( m_moveFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		//	移動のタブ
		m_moveFrame.SetColor( 255, 150, 150, 150 );
		if ( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			
			m_plyaerSelectType = _SELECT_MOVE_;
			tempFlag = true;
		}
	}
	//	選択されたので
	if ( tempFlag )
	{
		m_pAudio->SoundPlay( Audio::_CLICK_SE_ );
	}
	return tempFlag;
}


bool Selection::SetTypeArray()
{
	bool result = false;
	switch( m_plyaerSelectType )
	{
	case _SELECT_ACTION_:
		m_tempArray = m_tempShip->m_actionArray;
		m_tempStr1 = m_pGameLog->GetMultiplePhrase( 3, m_ShipCount,
				static_cast<int>( FixedPhrase::SELECTION_TYPE_ACTION ),
				static_cast<int>( FixedPhrase::SELECTION_PHRASE_STR ));
			m_pGameLog->AddStream( m_tempStr1.c_str() );	
		break;
	case _SELECT_SEARCH_:
		m_tempArray = m_tempShip->m_searchArray;
		m_tempStr1 = m_pGameLog->GetMultiplePhrase( 3, m_ShipCount,
				static_cast<int>( FixedPhrase::SELECTION_TYPE_SEARCH ), 
				static_cast<int>( FixedPhrase::SELECTION_PHRASE_STR ));
			m_pGameLog->AddStream( m_tempStr1.c_str() );
		break;
	case _SELECT_MOVE_:
		m_tempArray = m_tempShip->m_moveArray;
		m_tempStr1 = m_pGameLog->GetMultiplePhrase( 3, m_ShipCount,
				static_cast<int>( FixedPhrase::SELECTION_TYPE_MOVE ), 
				static_cast<int>( FixedPhrase::SELECTION_PHRASE_STR ));
			m_pGameLog->AddStream( m_tempStr1.c_str() );
		
		break;
	}
	//	選択した行動は使えるのかチェック
	for ( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++ ){
		for ( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++ ){
			if ( m_tempArray[iColumn][iLine] != StageObject::_CONDITION_NONE_)
				result = true;
		}
	}

	//	選択した行動は使えなかった
	if ( !result ){
		m_pGameLog->DeleteStream( false );
		m_tempStr1 = m_pGameLog->GetPhrase( FixedPhrase::SELECTION_DISABLED );
		m_pGameLog->AddStream( m_tempStr1.c_str(), _LOG_COLOR_WARNING_ );
	}

	return result;
}



int Selection::SelectArrayCheck( )
{
	int tempID;	///<どちらのプレイヤーのステージ配列を示すかの判定用にコピー
	int (*tempArray)[_SHIP_ARRAY_INDEX_];
	int iCheckResult = 0;
	int iColumn;	
	int iLine;

	//	攻撃と索敵なら相手側ID、移動なら自分側のIDをtempIDに入れる
	switch( m_plyaerSelectType )
	{
	case _SELECT_ACTION_:
	case _SELECT_SEARCH_:
		tempID = m_playerID/_PLAYER_NUM_? 1:2;	//相手側のIDを入れる
		//	行
		for ( iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
			//	列
			for ( iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
				bool resultBlockHit = m_pStage->m_stageBlock[tempID-1][iColumn][iLine].HitBlockCheck( m_tempX, m_tempY );
				if ( resultBlockHit )
				{
					//	ステージブロックのチェック
					switch( m_plyaerSelectType )
					{
					case _SELECT_ACTION_:
						iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, 
																	ShipObject::ARRAY_TYPE_ACTION, m_ShipCount );
						tempArray = m_tempShip->m_actionArray;
						break;
					case _SELECT_SEARCH_:
						iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, 
																	ShipObject::ARRAY_TYPE_SEARCH, m_ShipCount );
						tempArray = m_tempShip->m_searchArray;
						break;
					}

					if ( iCheckResult == -1 )	///<駒を置けるマスじゃなかった。
					{	
						return -1;
					}
					else ///<置けるマス。
					{
						m_pStage->SetRange( tempID, iColumn, iLine, tempArray, StageObject::_SELECT_TRUE_ );
						//	駒が置けるマスであり、左クリックを押した時
						if ( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) 
						{
							m_pStage->SetRange( tempID, iColumn, iLine, tempArray, m_plyaerSelectType );
							/*
								選択した箇所をログに出力
							*/
							char tempC1[2]	= "";
							char tempC2[2]	= "";
							char tempL1[2]	= "";
							int temp;
							if ( iColumn == 9 )
							{
								sprintf_s( tempC1, "%c",0x31 );
								sprintf_s( tempC2, "%c",0x30 );
							}
							else
							{
								temp = 0x30+(iColumn+1);
								sprintf_s( tempC2, "%c",temp );
							}
							temp = 0x40+(iLine+1);
							sprintf_s( tempL1, "%c",temp );
					
							m_tempStr1 = "【";
							m_tempStr1.append(tempL1);
							m_tempStr1.append(tempC1);
							m_tempStr1.append(tempC2);
							m_tempStr1 += "】を選択しました。";
							m_pGameLog->AddStream( m_tempStr1.c_str(), _LOG_COLOR_PHASE_ );
							return 2;
						}
					}
				}
			}
		}
		//	タブ選択の取り消しをする
		if ( m_pMouse->MouseStCheck( MOUSE_R, PUSH ) )
		{
			ResetTabSelect();
			m_pAudio->SoundPlay( Audio::_FAILED_SE_ );
		}
		break;

	case _SELECT_MOVE_:
		tempID = m_playerID;		//自分自身のIDを入れる
		int tempColumn, tempLine;	//	移動前の座標
		m_tempShip->GetArrayPos( tempColumn, tempLine );
		tempArray = m_tempShip->m_moveArray;
		m_pStage->SetStageToRange( tempID, m_tempShip, tempArray, m_ShipCount );
		
		iCheckResult =  m_pStage->CheckRangeOnStage( iColumn, iLine, tempID, m_tempX, m_tempY, m_tempShip, ShipObject::ARRAY_TYPE_SHIP );

		float tempW = _BLOCK_WIDTH_SIZE_;		///<	ステージ上の1コマのサイズの入力を簡略化
		float tempH = _BLOCK_HEIGHT_SIZE_;		///<	ステージ上の1コマのサイズの入力を簡略化

		//	タブ選択の取り消しをする時も、ちゃんと駒を元の場所に戻す
		if ( m_pMouse->MouseStCheck( MOUSE_R, PUSH ) )
		{
			m_tempShip->GetArrayPos( tempColumn, tempLine );
			if (tempID == 1)	//プレイヤーIDが1（=配列の指数だと0）だったら
			{
				m_tempX = tempLine*tempW + tempW*1.5f ;		
				m_tempY = tempColumn*tempH + tempH*1.5f;
			}
			else if (tempID == 2)
			{
				m_tempX = (tempLine+_STAGE_HEIGHT_MAX_)*tempW + tempW*1.5f ;
				m_tempY = tempColumn*tempH + tempH*1.5f;
			}
			m_tempShip->SetPosition( m_tempX, m_tempY, 0.5f );
			ResetTabSelect();
			m_pAudio->SoundPlay( Audio::_FAILED_SE_ );

			return 0;
		}

		if ( iCheckResult == -1 )	///<駒を置けるマスじゃなかった。
		{	
			return -1;
		}
		else if ( iCheckResult == 1  )	///<置けるマス。
		{
			if (tempID == 1)	//プレイヤーIDが1（=配列の指数だと0）だったら
			{
				m_tempX = iLine*tempW + tempW*1.5f ;		
				m_tempY = iColumn*tempH + tempH*1.5f;
			}
			else if (tempID == 2)
			{
				m_tempX = (iLine+_STAGE_HEIGHT_MAX_)*tempW + tempW*1.5f ;
				m_tempY = iColumn*tempH + tempH*1.5f;
			}
			//	移動可能マスだから移動先に駒を仮配置
			m_tempShip->SetPosition( m_tempX, m_tempY, 0.5f );
			if ( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) 
			{
				m_pStage->RelocationShip( tempID, iColumn, iLine, m_tempShip, m_ShipCount );
				return 2;
			}
			return 1;
		}
		else
		{
			//	移動可能マスにカーソルが無いので、駒の位置を元に戻す
			m_tempShip->GetArrayPos( iColumn, iLine );

			if (tempID == 1)	//プレイヤーIDが1（=配列の指数だと0）だったら
			{
				m_tempX = iLine*tempW + tempW*1.5f ;		
				m_tempY = iColumn*tempH + tempH*1.5f;
			}
			else if (tempID == 2)
			{
				m_tempX = (iLine+_STAGE_HEIGHT_MAX_)*tempW + tempW*1.5f ;
				m_tempY = iColumn*tempH + tempH*1.5f;
			}
			m_tempShip->SetPosition( m_tempX, m_tempY, 0.5f );
		}
		
		break;
	}

	return 0;
}


void Selection::ResetTabFrame()
{
	m_actionFrame.SetColor( 255, 255, 255, 255 );
	m_searchFrame.SetColor( 255, 255, 255, 255 );
	m_moveFrame.SetColor( 255, 255, 255, 255 );

}

void Selection::ResetTabSelect()
{
	ResetTabFrame();
	m_pStage->ResetSelect();
	m_selectionFlag = _SELECT_LOG_BIT_;
	m_arrayCheckResult = 0;
	m_plyaerSelectType = _SELECT_NONE_;
}

//	
void Selection::Draw()
{
	if ( !(m_selectionFlag>>1) || 
		 m_pPlayer[m_playerID-1]->CheckDestroy( static_cast<ShipObject::_SHIP_TYPE_NUM_>( m_ShipCount) ))
	{
		m_pDrawManager->VertexDraw( _TEX_TABFRAME_, m_actionFrame.GetPositionX(), m_actionFrame.GetPositionY(),
			m_actionFrame.GetWidth(), m_actionFrame.GetHeight(),
			0.f, (_TAB_HEIGHT_*2)/_TAB_WIDTH_, 1.f, 1.f,
			m_actionFrame.GetAlpha(), m_actionFrame.GetRed(), m_actionFrame.GetGreen(), m_actionFrame.GetBlue() );
		
		m_pDrawManager->VertexDraw( _TEX_TABFRAME_, m_searchFrame.GetPositionX(), m_searchFrame.GetPositionY(),
			m_searchFrame.GetWidth(), m_searchFrame.GetHeight(),
			0.f, _TAB_HEIGHT_/_TAB_WIDTH_, 1.f, (_TAB_HEIGHT_*2)/_TAB_WIDTH_,
			m_searchFrame.GetAlpha(), m_searchFrame.GetRed(), m_searchFrame.GetGreen(), m_searchFrame.GetBlue() );
		
		m_pDrawManager->VertexDraw( _TEX_TABFRAME_, m_moveFrame.GetPositionX(), m_moveFrame.GetPositionY(),
			m_moveFrame.GetWidth(), m_moveFrame.GetHeight(), 
			0.f, 0.f, 1.f, _TAB_HEIGHT_/_TAB_WIDTH_,
			m_moveFrame.GetAlpha(), m_moveFrame.GetRed(), m_moveFrame.GetGreen(), m_moveFrame.GetBlue() );

	}
	else{
		
	}
}

