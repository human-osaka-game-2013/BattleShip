/**
*@file	read_file.cpp
*@author	亀田
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "read_file.h"


bool ReadFile::ReadTableData( char* _pFileName, const int _ColumnMax, const int _LineMax )
{
	
	FILE*	fp;
		
	if ( ( fopen_s( &fp, _pFileName, "r" ) ) == 0 )
	{
	
		int iColumn = 0, iLine = 0;
		char	buf[256]={0};
		char*	p, *q;

		while ( fgets ( buf, 256, fp) != NULL )
		{
			p = buf;
			
			do
			{
				q = strstr( p, "," );
				
				if ( q != NULL ) *q = '\0';

				SetTable ( p, iColumn, iLine);

				p = q + 1;

				iLine++;

			}while ( q != NULL );

			iColumn++;
			iLine = 0;
			if ( iColumn >= _ColumnMax )	{ iColumn=0; }
		
		}

		fclose (fp);
	}
	else
	{
		printf( "%sファイルが開けません", _pFileName );
		return false;
	}
	return true;
}

bool ReadFile::SetDataFile( const std::string& _str )
{
	std::ofstream ofs;
	ofs.open( _CONNECTDATA_PASS_ );

	if (!ofs) {
		std::cout << "ファイル file.txt が開けません";
        return false;
    }

	ofs <<_str.c_str()<< std::endl;

	ofs.close();
	return true;
}

bool ReadFile::SaveToBinaryData( char* _pFileName, void* _data, int _size )
{
	std::ofstream ofs;
	ofs.open( _pFileName, std::ios::out | std::ios::binary );

	if (!ofs) {
		std::cout << "ファイルが開けません";
		//	ファイルが無かった場合は全ての値を0で作成
		void* dummy = calloc(1,_size);
		ofs.write( static_cast<char*>(dummy), sizeof(_size) );
		delete dummy;

        return false;
    }

	ofs.write( static_cast<char*>(_data), sizeof(_size) );

	ofs.close();

	return true;
}

bool ReadFile::ReadBinaryData( char* _pFileName, void* _data, int _size )
{
	std::ifstream ifs;
	ifs.open( _pFileName, std::ios::in | std::ios::binary );
	
	if (!ifs) {
		std::cout << "ファイルが開けません";
	
        return false;
    }

	ifs.read( static_cast<char*>(_data), sizeof(_size) );

	ifs.close();

	return true;
}