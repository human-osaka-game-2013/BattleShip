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
				tempX = ( iLine*( _BLOCK_WIDTH_SIZE_ ))+( _BLOCK_WIDTH_SIZE_ );
				tempY = ( iColumn*( _BLOCK_HEIGHT_SIZE_ ))+( _BLOCK_HEIGHT_SIZE_ );
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

int StageObject::CheckStageBlock( int _player, int _column, int _line, ShipObject* _ship )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return -1;	///<	プレイヤーIDが1か2以外だった場合

	_player--;	///<	配列指数用に直す

	for( int iColumn = 0, iStageCol = _column-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _line-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){

			bool bStageOutside = false;	///<	駒の配列情報がステージからはみ出てしまう場合のフラグ

			//	指定したブロック中心に5×5マス範囲調べる際に、ステージ外を調べてしまわない様に
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}

			//	指定したブロック範囲がステージからはみ出た場合
			if( bStageOutside ){
				if( _ship->m_shipArray[iColumn][iLine] != 0 )
					return 1;	///<	ステージから出ていて、駒の一部が存在していれば駒自体がはみ出ている場合なので、指定した場所は無効である。
			} else if( m_stageArray[_player][iStageCol][iStageLine] != 0 ) {
				if( _ship->m_shipArray[iColumn][iLine] != 0 )	///<	ステージに駒が置ける場所
					return 2;
			}
		}
	}
	return 0;
}


bool StageObject::SetShip( int _player, int _column, int _line, ShipObject* _ship )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	プレイヤーIDが1か2以外だった場合

	_player--;	///<	配列指数用に直す

	for( int iColumn = 0, iStageCol = _column-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _line-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){
		
			bool bStageOutside = false;	///<	駒の配列情報がステージからはみ出てしまう場合のフラグ
		
			//	指定したブロック中心に5×5マス範囲調べる際に、ステージ外を調べてしまわない様に
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}
			//	ステージ内で、駒がなければ
			if( !bStageOutside &&  m_stageArray[_player][iStageCol][iStageLine]%100 == 0 ){
				if( _ship->m_shipArray[iColumn][iLine] != 0 )
					m_stageArray[_player][iStageCol][iStageLine] = _ship->m_shipArray[iColumn][iLine];
			}
		}

	}
	return true;
}

bool StageObject::SetRange( int _player, int _column, int _line, const int(*_array)[_SHIP_ARRAY_INDEX_], int _setType)
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	プレイヤーIDが1か2以外だった場合

	_player--;	///<	配列指数用に直す

	for( int iColumn = 0, iStageCol = _column-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _line-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){

			bool bStageOutside = false;	///<	駒の配列情報がステージからはみ出てしまう場合のフラグ

			//	指定したブロック中心に5×5マス範囲調べる際に、ステージ外を調べてしまわない様に
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}

			//	ステージ内で、今調べてる配列情報の中身が0じゃ無かったら（駒や攻撃などの範囲情報があれば）
			if( !bStageOutside && _array[iColumn][iLine] != 0  ){
				m_stageArray[_player][iStageCol][iStageLine] += 100*_setType;
			}
		}

	}
	return true;
}

void StageObject::ResetSelect()
{
	//        プレイヤー数
	for( int iPlayer=0; iPlayer<_PLAYER_NUM_; iPlayer++ )
	{	
		//        行
		for( int iColumn=0; iColumn<_STAGE_COLUMN_MAX_; iColumn++ )
		{	 
			//        列
			for( int iLine=0; iLine<_STAGE_LINE_MAX_; iLine++ )
			{	
				//        3桁目は選択情報なので、選択情報だけ消せる様にしている
				m_stageArray[iPlayer][iColumn][iLine] -= 100*(m_stageArray[iPlayer][iColumn][iLine]/100);
			}		
		}	
	}
}
