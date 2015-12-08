/**
*@file	read_file.h
*@author	亀田
*/

#ifndef _READ_FILE_H_
#define _READ_FILE_H_
#include <iostream>

#define _READ_FILE_PASS_1_ "table/ConnectData.csv"

/**
*@brief	ファイルを読み込み
*@details	textやCSV形式のファイルを読み込み、数値をテーブルにセットするためのクラス。@n
			テーブルにセットする際はSetTable関数の実態をこのクラスを継承した先でつくること。
*/
class ReadFile
{
public:
	/**
	*@brief	テーブルデータの読み取り
	*/
	bool ReadTableData( char* _pFileName, const int _ColumnMax, const int _LineMax );
	
	/**
	*@brief	文字列からデータファイルに変換
	*@details	文字列をデータファイルにセット出来るように変換する。
				SetDataFile関数を用いる際にこの関数を各クラスでオーバーライドして使って下さい。
	*@retval false	データファイルにセットするデータに不備があった。
	*@retval true	成功
	*/
	virtual bool ConvertDataFileFromStr( std::string* _outStr ){ return true; }

	/**
	*@brief	データファイルへ情報セット
	*/
	bool SetDataFile( const std::string& _str );

	/**
	*@brief	読み取ったデータをテーブルにセット
	*@details	テーブルデータは派生クラスに1種類のファイルのみを使う事。@n
				よってどのテーブルにデータを入れるかの調節は派生先の関数で行う事。
	*/
	virtual void SetTable( char* _p, int _iColumn, int _iLine)=0;

};

#endif _READ_FILE_H_