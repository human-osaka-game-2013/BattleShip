/**
*@file	StageEffect.cpp
*@author	亀田
*/

#include "StageEffect.h"

bool StageEffect::Init()
{
	CheckOfMyShipPos();		///< 
	CheckSelectOfStage();	///< 
	
	return false;
}

int StageEffect::Control()
{
	//	エフェクトを再生する際に基準にするカウンタ
	//	ここではログに追加などをする。
	if( m_elapsedTimeFormStateInstance < TIME_END_ACTION_EFFECT  )
	{
		if( m_selectType == _SELECT_ACTION_ )
		{
			
		}
		else if( m_selectType == _SELECT_SEARCH_ )
		{
			
		}
	}
	else if( m_elapsedTimeFormStateInstance < TIME_CHANGE_EFFECT )
	{

	}
	else if( m_elapsedTimeFormStateInstance < TIME_END_RUSULT_EFFECT )
	{
		if( m_selectType == _SELECT_ACTION_ )
		{
			
		}
		else if( m_selectType == _SELECT_SEARCH_ )
		{
			
		}
		if( m_enemyType == _SELECT_ACTION_ )
		{
			
		}
		else if( m_enemyType == _SELECT_SEARCH_ )
		{
			
		}
	}
	else
	{
		return 1;
	}

	return 0;
}

void StageEffect::CheckSelectOfStage()
{
	for( int iPlayer = 0; iPlayer < _PLAYER_NUM_; iPlayer++ )
	{
		for( int iColumn = 0; iColumn < _STAGE_COLUMN_MAX_; iColumn++ )
		{
			for( int iLine = 0; iLine < _STAGE_LINE_MAX_; iLine++ )
			{
				switch( StageObject::SelectOfData( m_pStage->m_stageArray[iPlayer][iColumn][iLine]) )
				{
				case StageObject::_SEARCH_NOMAL_:
				case StageObject::_SEARCH_ALL_:
				case StageObject::_ACTION_NOMAL_:
				case StageObject::_ACTION_ALL_:
					if( iPlayer == m_playerID/2 )
					{
						m_enemySelect.push_back(m_pStage->m_stageBlock[iPlayer][iColumn][iLine] );
					}
					else
					{
						m_playerSelect.push_back( m_pStage->m_stageBlock[iPlayer][iColumn][iLine] );
						m_enemyType = (StageObject::SelectOfData( m_pStage->m_stageArray[iPlayer][iColumn][iLine])
							/StageObject::_ACTION_NOMAL_) ? _SELECT_SEARCH_ : _SELECT_ACTION_;
					}
					break;
				}
			}
		}
	}
}


void StageEffect::CheckOfMyShipPos()
{
	ShipObject* tempShip = m_pPlayer[m_playerID/2]->GetShip( static_cast<ShipObject::_SHIP_TYPE_NUM_>(m_ShipCount) );
	tempShip->GetArrayPos( m_actionShipPosColumn, m_actionShipPosLine );
	m_myShipBlock = m_pStage->m_stageBlock[m_playerID/2][m_actionShipPosColumn][m_actionShipPosLine];
}

//	
void StageEffect::Draw()
{
	//	エフェクトを再生する際に基準にするカウンタ
	if( m_elapsedTimeFormStateInstance < TIME_END_ACTION_EFFECT  )
	{
		if( m_selectType == _SELECT_ACTION_ )
		{
			FireEffect();
		}
		else if( m_selectType == _SELECT_SEARCH_ )
		{
			SearchStratEffect();
		}
	}
	else if( m_elapsedTimeFormStateInstance < TIME_CHANGE_EFFECT )
	{

	}
	else if( m_elapsedTimeFormStateInstance < TIME_END_RUSULT_EFFECT )
	{
		if( m_selectType == _SELECT_ACTION_ )
		{
			HitEffect( m_playerID );
		}
		else if( m_selectType == _SELECT_SEARCH_ )
		{
			SearchResultEffect( m_playerID );
		}
		if( m_enemyType == _SELECT_ACTION_ )
		{
			HitEffect( m_playerID/2 ? 2:1 );
		}
		else if( m_enemyType == _SELECT_SEARCH_ )
		{
			SearchResultEffect( m_playerID/2 ? 2:1 );
		}
	}

}

bool StageEffect::FireEffect()
{
	bool result = false;
	float tempX, tempY;
	tempX = m_myShipBlock.GetPositionX();
	tempY = m_myShipBlock.GetPositionY();
	int wDiv = m_elapsedTimeFormStateInstance/2;	///<シーンの経過時間から何コマ目のアニメーションをさせるかを計算（テスト実装）
	bool flipHorizontal = m_playerID/2 ? true : false;	///<プレイヤーによって画像の反転をさせる

	m_pDrawManager->AnimationDraw( _TEX_FIRE_EFFECT_, tempX, tempY, 
				m_myShipBlock.GetWidth(), 
				m_myShipBlock.GetHeight(),
				flipHorizontal, false, wDiv );	///<	マスの描画

	return result;
}

bool StageEffect::SearchStratEffect()
{
	bool result = false;

	
	return result;
}

bool StageEffect::HitEffect( const int _playerID )
{
	bool result = false;


	return result;
}

bool StageEffect::SearchResultEffect( const int _playerID )
{
	bool result = false;


	return result;
}

void StageEffect::SonarEffect()
{
	if( m_elapsedTimeFormStateInstance <= 8 || m_elapsedTimeFormStateInstance >= 12 )
	{
		float tempX, tempY, tempW, tempH;
		int Alpha = 255;
		tempX = m_myShipBlock.GetPositionX()+_BLOCK_WIDTH_SIZE_/2;
		tempY = m_myShipBlock.GetPositionY()+_BLOCK_HEIGHT_SIZE_/2;		
		tempW = m_myShipBlock.GetWidth() *(m_elapsedTimeFormStateInstance%8)/5;
		tempH =	m_myShipBlock.GetHeight()*(m_elapsedTimeFormStateInstance%8)/5;
		Alpha -= (m_elapsedTimeFormStateInstance%8)*2;
		m_pDrawManager->CenterDraw( _TEX_SEARCH_EFFECT_, tempX, tempY, 0.f, 
					tempW, tempH, 0.f, 0.f, 1.f, 1.f, Alpha, 255, 255, 255 );
	}
	if( m_elapsedTimeFormStateInstance >= 4 || m_elapsedTimeFormStateInstance <= 12 )
	{
		float tempX, tempY, tempW, tempH;
		int Alpha = 255;
		tempX = m_myShipBlock.GetPositionX()+_BLOCK_WIDTH_SIZE_/2;
		tempY = m_myShipBlock.GetPositionY()+_BLOCK_HEIGHT_SIZE_/2;
		tempW = m_myShipBlock.GetWidth() *((m_elapsedTimeFormStateInstance%8)+4)/5;
		tempH =	m_myShipBlock.GetHeight()*((m_elapsedTimeFormStateInstance%8)+4)/5;
		Alpha -= (m_elapsedTimeFormStateInstance%8)*2;

	m_pDrawManager->CenterDraw( _TEX_SEARCH_EFFECT_, tempX, tempY, 0.f, 
				tempW, tempH, 0.f, 0.f, 1.f, 1.f, Alpha, 255, 255, 255 );	///<	マスの描画

	}
}

bool StageEffect::ComStandby()
{
	return true;
}