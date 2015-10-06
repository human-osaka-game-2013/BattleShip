/**
*@file	Selection.cpp
*@author	亀田
*/

#include "Selection.h"

bool Selection::Init()
{
	m_StateCompFlag = false;
	m_tabSelectFlag = false;
	m_areaSelectFlag= false;
	m_arrayCheckResult = 0;
	m_margeStageDataFlag = false;

	m_tempShip = m_pPlayer[m_playerID-1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)(m_ShipCount) );
		
	m_actionFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY()+_TAB_HEIGHT_*2, 
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_actionFrame.SetColor( 255, 255, 255, 255 );
	
	m_searchFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY()+_TAB_HEIGHT_,
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_searchFrame.SetColor( 255, 255, 255, 255 );

	m_moveFrame.Init( m_tempShip->GetPositionX(), m_tempShip->GetPositionY(),
						_TAB_WIDTH_, _TAB_HEIGHT_ );
	m_moveFrame.SetColor( 255, 255, 255, 255 );

	return false;
	
}

//	
int Selection::Control()
{
	m_tempX = (float)m_pMouse->GetCursorPosX();
	m_tempY = (float)m_pMouse->GetCursorPosY();

	if( !m_StateCompFlag )
	{
		if( !m_tabSelectFlag )
		{	
			m_tabSelectFlag = TabCheck();
		}
		else if( !m_areaSelectFlag )
		{
			m_areaSelectFlag = SetTypeArray();
			if( !m_areaSelectFlag )	///< 選択した範囲にデータが無い（orその行動は出来ない）場合、タブの選択も解除する。
				m_tabSelectFlag = false;
		}
		else if( m_arrayCheckResult != 2 )
		{
			m_pStage->ResetSelect();
			m_arrayCheckResult = SelectArrayCheck();
		}
		else{
			if( !m_margeStageDataFlag ){
				m_margeStageDataFlag = ComStandby();
			}
			else{
				m_StateCompFlag = true;
			}
		}
		
	}

	return ((m_StateCompFlag) ? 1 : 0);
}


bool Selection::TabCheck()
{
	ResetTabFrame();
	bool tempFlag = false;

	//	選択タブごとのマウスとの接触判定
	if( m_actionFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		m_actionFrame.SetColor( 255, 150, 150, 150 );
		if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			m_selectType = _SELECT_ACTION_;
			tempFlag = true;
		}
	}
	if( m_searchFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		m_searchFrame.SetColor( 255, 150, 150, 150 );
		if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			m_selectType = _SELECT_SEARCH_;
			tempFlag = true;
		}
	}
	if( m_moveFrame.HitBlockCheck( m_tempX, m_tempY ) )
	{
		m_moveFrame.SetColor( 255, 150, 150, 150 );
		if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )){
			m_selectType = _SELECT_MOVE_;
			tempFlag = true;
		}
	}

	return tempFlag;
}


bool Selection::SetTypeArray()
{
	switch( m_selectType )
	{
	case _SELECT_ACTION_:
		m_tempArray = m_tempShip->m_actionArray;
		break;
	case _SELECT_SEARCH_:
		m_tempArray = m_tempShip->m_searchArray;
		break;
	case _SELECT_MOVE_:
		m_tempArray = m_tempShip->m_moveArray;
		
		break;
	}

	for( int iColumn = 0; iColumn < _SHIP_ARRAY_INDEX_; iColumn++ ){
		for( int iLine = 0; iLine < _SHIP_ARRAY_INDEX_; iLine++ ){
			if( m_tempArray[iColumn][iLine] != StageObject::_CONDITION_NONE_)
			return true;
		}
	}

	MessageBoxA(0,"この行動は選択出来ない。\n申し訳ないが、他の行動を選択してくれ",NULL,MB_OK);
	return false;
}



int Selection::SelectArrayCheck( )
{
	int tempID = m_playerID;	///<どちらのプレイヤーのステージ配列を示すかの判定用にコピー
	int (*tempArray)[_SHIP_ARRAY_INDEX_];
	int iCheckResult = 0;
	int iColumn;	
	int iLine;

	//	攻撃と索敵なら相手側ID、移動なら自分側のIDを使うつもり
	switch( m_selectType )
	{
	case _SELECT_ACTION_:
	case _SELECT_SEARCH_:
		if( --tempID <= 0 )	///<チェックするステージ配列の指数の判定
			tempID+=2;
		//	行
		for( iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
			//	列
			for( iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
				
				if( m_pStage->m_stageBlock[tempID-1][iColumn][iLine].HitBlockCheck( m_tempX, m_tempY ))
				{
					//	ステージブロックのチェック
					switch( m_selectType )
					{
					case _SELECT_ACTION_:
						iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, ShipObject::ARRAY_TYPE_ACTION, m_ShipCount );
						tempArray = m_tempShip->m_actionArray;
						break;
					case _SELECT_SEARCH_:
						iCheckResult = m_pStage->CheckStageBlock( tempID, iColumn, iLine, m_tempShip, ShipObject::ARRAY_TYPE_SEARCH, m_ShipCount );
						tempArray = m_tempShip->m_searchArray;
						break;
					}

					if( iCheckResult == -1 )	///<駒を置けるマスじゃなかった。
					{	
						return -1;
					}
					else ///<置けるマス。
					{
						m_pStage->SetRange( tempID, iColumn, iLine, tempArray, StageObject::_SELECT_TRUE_ );
						//	駒が置けるマスであり、左クリックを押した時
						if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) 
						{
							m_pStage->SetRange( tempID, iColumn, iLine, tempArray, m_selectType );
							
							return 2;
						}
					}
				}
			}
		}
		break;

	case _SELECT_MOVE_:
		tempArray = m_tempShip->m_moveArray;
		m_pStage->SetStageToRange( tempID, m_tempShip, tempArray, m_ShipCount );
		
		iCheckResult =  m_pStage->CheckRangeOnStage( iColumn, iLine, tempID, m_tempX, m_tempY, m_tempShip, ShipObject::ARRAY_TYPE_SHIP );

		if( iCheckResult == -1 )	///<駒を置けるマスじゃなかった。
		{	
			return -1;
		}
		else if( iCheckResult == 1  )	///<置けるマス。
		{
			float tempW = _BLOCK_WIDTH_SIZE_;		///<	ステージ上の1コマのサイズの入力を簡略化
			float tempH = _BLOCK_HEIGHT_SIZE_;		///<	ステージ上の1コマのサイズの入力を簡略化
			m_tempX = iLine*tempW + tempW*1.5f ;		
			m_tempY = iColumn*tempH + tempH*1.5f;
			m_tempShip->SetPosition( m_tempX, m_tempY, 0.5f );
			
			if( m_pMouse->MouseStCheck( MOUSE_L, PUSH )) 
			{
				m_pStage->RelocationShip( tempID, iColumn, iLine, m_tempShip, m_ShipCount );
				return 2;
			}
			return 1;
		}
		else
		{
			m_tempShip->GetArrayPos( iColumn, iLine );

			float tempW = _BLOCK_WIDTH_SIZE_;		///<	ステージ上の1コマのサイズの入力を簡略化
			float tempH = _BLOCK_HEIGHT_SIZE_;		///<	ステージ上の1コマのサイズの入力を簡略化
			m_tempX = iLine*tempW + tempW*1.5f ;		
			m_tempY = iColumn*tempH + tempH*1.5f;
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

//	
void Selection::Draw()
{
	if( !m_tabSelectFlag ){
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

//	
bool Selection::ComStandby()
{
#ifdef	_COM_TEST_
	//本来なら相手側のステージ情報が来るまで、「通信中」などの画像を表示して、待たせて置くが、
	//今はテストの為、自分自身のステージ情報を相手と見立てて、マージする。
	if( MargeStage( m_pStage, m_pPlayer[m_playerID-1] ) )
		return true;

	return false;
#else
	return true;
#endif
}

bool Selection::MargeStage( StageObject* _pStage, Player* _pPlayer )
{
	for( int iColumn = 0; iColumn < _STAGE_COLUMN_MAX_; iColumn++ )
	{
		for( int iLine = 0; iLine < _STAGE_LINE_MAX_; iLine++ )
		{
#ifdef _COM_TEST_
			//	通信無しのテストの為、相手側の情報にはプレイヤー側の情報を全てコピーする。
			_pStage->m_stageArray[0][iColumn][iLine] =
				m_pStage->m_stageArray[0][iColumn][iLine] =
				( m_pStage->m_stageArray[0][iColumn][iLine]%100) +
				( (_pStage->m_stageArray[1][iColumn][iLine]/100)*100 );
			m_pStage->m_stageArray[1][iColumn][iLine] = 
				m_pStage->m_stageArray[1][iColumn][iLine] =
				( _pStage->m_stageArray[0][iColumn][iLine]%100) +
				( (m_pStage->m_stageArray[1][iColumn][iLine]/100)*100 );
#else

			//	相手側（_pStage）から貰ってきた、お互いのステージに対して行った、選択情報（3桁目）と、
			//	お互い自身の駒に対しての行動（移動）情報を更新してやる。
			_pStage->m_stageArray[0][iColumn][iLine] =
				m_pStage->m_stageArray[0][iColumn][iLine] =
				( m_pStage->m_stageArray[0][iColumn][iLine]%100) +
				( (_pStage->m_stageArray[0][iColumn][iLine]/100)*100 );
			m_pStage->m_stageArray[1][iColumn][iLine] = 
				m_pStage->m_stageArray[1][iColumn][iLine] =
				( _pStage->m_stageArray[1][iColumn][iLine]%100) +
				( (m_pStage->m_stageArray[1][iColumn][iLine]/100)*100 );
#endif
		}
	}

#ifdef _COM_TEST_
	//	通信無しのテストの為、相手側の情報にはプレイヤー側の必要な情報をコピーする。
	for( int iShip = 0; iShip < ShipObject::TYPE_MAX; iShip++ )
	{
		ShipObject* temp1 = m_pPlayer[1]->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
		ShipObject* temp0 = _pPlayer->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );

		temp1->SetArrayPos( temp0->GetArrayColumn(), temp0->GetArrayLine() );
	}
#endif

	return true;
}