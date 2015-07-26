/**
*@file	Proc.h
*@author	亀田
*@brief	Proc関数系のまとめ
*/

//----------------------------------------------------------------
//	プロトタイプ宣言
//----------------------------------------------------------------

/**
*@brief	ウインドウ生成
*/
int CreateWindowProcess ( HINSTANCE, HWND* );

/**
*@brief	ウインドウプロシージャ
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);