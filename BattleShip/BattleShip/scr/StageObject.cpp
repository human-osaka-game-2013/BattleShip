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

int StageObject::CheckStageBlock( int _player, int _column, int _line, ShipObject* _ship, ShipObject::_SHIP_ARRAY_TYPE_ _arrayType )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return -1;	///<	プレイヤーIDが1か2以外だった場合

	int(*_array)[_SHIP_ARRAY_INDEX_];	///<どの配列データとのチェックを行うかの格納用
	_player--;	///<	配列指数用に直す
	
	//---どの配列データをチェックするかの分岐---
	switch( _arrayType )
	{
	case ShipObject::ARRAY_TYPE_SHIP:
		_array = _ship->m_shipArray;
		break;
	case ShipObject::ARRAY_TYPE_ACTION:
		_array = _ship->m_actionArray;
		break;
	case ShipObject::ARRAY_TYPE_SEARCH:
		_array = _ship->m_searchArray;
		break;
	case ShipObject::ARRAY_TYPE_MOVE:
		return -1;
	
	}//---

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
				if( _array[iColumn][iLine] != 0 )
					return 1;	///<	ステージ外にブロックの実体があった場合
			} else if( m_stageArray[_player][iStageCol][iStageLine] != 0 ) {
				if( _array[iColumn][iLine] != 0 )	
					return 2;	///<	指定したブロックの範囲にすでにステージ上で何かが存在していた場合
			}
		}
	}
	return 0;	///<指定した範囲は何にも接触をしなかった
}

int StageObject::CheckStageBlock( int _player, int _column, int _line, ShipObject* _ship, 
	const int(*_array)[_SHIP_ARRAY_INDEX_], int _shipCount )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	プレイヤーIDが1か2以外だった場合

	_player--;	///<	配列指数用に直す
	int iStageCol;
	int iStageLine;
	
	for( int iColumn = 0, iStageCol = _ship->GetArrayColumn()-2; iColumn < _SHIP_ARRAY_INDEX_; iColumn++, iStageCol++ ){
		for( int iLine = 0, iStageLine = _ship->GetArrayLine()-2 ; iLine < _SHIP_ARRAY_INDEX_; iLine++, iStageLine++ ){

			bool bStageOutside = false;	///<	駒の配列情報がステージからはみ出てしまう場合のフラグ

			//	指定したブロック中心に5×5マス範囲調べる際に、ステージ外を調べてしまわない様に
			if( iStageCol >= _STAGE_COLUMN_MAX_ || iStageCol < 0 ||
				iStageLine >= _STAGE_LINE_MAX_ || iStageLine < 0 ) {
				bStageOutside = true;
			}

			//	指定したブロック範囲がステージからはみ出た場合
			if( bStageOutside ){
				if( _array[iColumn][iLine] != 0 ){
					return 
				}
			} else if( (m_stageArray[_player][iStageCol][iStageLine]%10) != _shipCount+1 
					&& iStageCol != 0 && iStageLine != 0 ) {
				if( _array[iColumn][iLine] != 0 )
					SetRange( _player+1, iStageCol, iStageLine, 2 );
				continue;
			}
			if( _array[iColumn][iLine] != 0 ){
				
				SetRange( _player+1, iStageCol, iStageLine, 1 );
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

bool StageObject::SetRange( int _player, int _column, int _line, int _setType )
{
	if( _player > _PLAYER_NUM_ || _player <= 0 )	
		return false;	///<	プレイヤーIDが1か2以外だった場合

	_player--;	///<	配列指数用に直す

	//	ステージ内で、今調べてる配列情報の中身が0じゃ無かったら（駒や攻撃などの範囲情報があれば）
	if( (m_stageArray[_player][_column][_line] / 100) != 0 ){
		//        3桁目は選択情報なので、選択情報だけ消せる様にしている
		m_stageArray[_player][_column][_line] -= 100*(m_stageArray[_player][_column][_line]/100);
		m_stageArray[_player][_column][_line] += 100*_setType;
	}
	else{
		m_stageArray[_player][_column][_line] += 100*_setType;
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
