/**
*@file	StageDefineList.h
*@author	亀田
*/
#ifndef _STAGEDEFINELIST_H_
#define _STAGEDEFINELIST_H_

#include "Window.h"

#define _STAGE_COLUMN_MAX_ 10	///<	ステージの行数
#define _STAGE_LINE_MAX_	10	///<	ステージの列数

#define _BLOCK_WIDTH_SIZE_	WIDTH/_BLOCK_WIDTH_MAX_
#define _BLOCK_HEIGHT_SIZE_	HEIGHT/_BLOCK_HEIGHT_MAX_

#define _BLOCK_WIDTH_MAX_	(float)23	///<盤面の横幅の最大ブロック数
#define _BLOCK_HEIGHT_MAX_	(float)16	///<盤面の縦幅の最大ブロック数
#define _STAGE_HEIGHT_MAX_	(float)11	///<ステージ部分の縦幅の最大ブロック数
#define _STAGE_WIDTH_MAX_ _STAGE_HEIGHT_MAX_

#define _BOARD_OF_SHIPDATA_LINE_P1_	(float)8	///<自駒の詳細データの表示列位置（プレイヤー1）
#define _BOARD_OF_SHIPDATA_LINE_P2_ (float)14	///<自駒の詳細データの表示列位置（プレイヤー2）
#define _BOARD_OF_SHIPDATA_COLUMN_	(float)_STAGE_HEIGHT_MAX_	///<自駒の詳細データの表示行位置

#endif