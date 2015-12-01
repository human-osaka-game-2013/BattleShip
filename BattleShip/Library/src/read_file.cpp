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
	ofs.open( _READ_FILE_PASS_1_ );

	ofs <<_str.c_str()<< std::endl;

	ofs.close();
	return true;
}