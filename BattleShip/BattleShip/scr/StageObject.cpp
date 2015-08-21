/**
*@file	StageObject.cpp
*@author	亀田
*/

#include "StageObject.h"
#include "StateManager.h"

bool StageObject::Init()
{
	float tempX, tempY;
	//	ステージマス目表示
	//	プレイヤー数
	for( int iPlayer=0; iPlayer<_PLAYER_NUM_; iPlayer++ ){
		//	行
		for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ ){	
			//	列
			for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ ){
				m_stageArray[iPlayer][iColumn][iLine] = 0;	///<	プレイヤー1のステージデータ初期化
				
				//	基準点の計算。ただのループ回数に合わえてブロック幅分座標を調節
				tempX = ( iColumn*( _BLOCK_WIDTH_SIZE_ ))+( _BLOCK_WIDTH_SIZE_ );
				tempY = ( iLine*( _BLOCK_HEIGHT_SIZE_ ))+( _BLOCK_HEIGHT_SIZE_ );
				if( iPlayer == 1 )	//	プレイヤー2の表示のみX座標をずらす。
					tempX += _BLOCK_WIDTH_SIZE_*11;

				m_stageBlock[iPlayer][iColumn][iLine].Init( tempX, tempY, _BLOCK_WIDTH_SIZE_, _BLOCK_HEIGHT_SIZE_ );
			}
		}
	}
	return true;
}


void  StageObject::Free()
{

}

bool StageObject::CheckStageBlock( int _player, int _column, int _line, unsigned char _vol )
{
	if( m_stageArray[_player-1][_column][_line] == _vol )
	{
		return true;
	}
	return false;
}

