#include "GameLog.h"

void GameLog::Init( const long& _x, const long& _y, const char* _firstStr )
{
	SetPosition( _x, _y );
	if( _firstStr != NULL )
	{
		AddStream( _firstStr );
	}
}

void GameLog::AddStream( const char* _str, const D3DXCOLOR& _color, const unsigned int _width, const unsigned int _height )
{
	long tempX = m_posX, tempY = m_posY;

	if( !m_logStream.empty() ){
		//	最終に追加した文字列の座標を基に、その文字の下に配置出来るようにする
		LogStream* const logBack = m_logStream.back();
		logBack->GetPosition( tempX, tempY );
		tempY += logBack->GetHeight();	///< 基本高さしか変わらないのでY座標だけ文字の縦幅分加算
	}
	m_logStream.push_back( new LogStream( _str, tempX, tempY, _width, _height, _color ) );
	CheckStream( _LOG_HEIGHT_MAX_ );
}


bool GameLog::CheckStream( const unsigned int _height )
{
	bool result = false;

	unsigned int allStreamHeight = 0;	///< 登録されている全て文字列の縦幅を加算
	//	要素が空で無かったら
	if( !m_logStream.empty() ){
		//	全部の要素の確認をする
		std::list<LogStream*>::const_iterator itEnd = m_logStream.end();
		for( std::list<LogStream*>::iterator it = m_logStream.begin(); it != itEnd; ++it)
		{
			allStreamHeight += (*it)->GetHeight();	///< 縦幅の加算
		}
	}
	else{
		result = false;	///< 調べる以前に中身が空なのでfalse
	}
	
	//	登録されている全ての文字列の幅が指定した値より多かったら
	if( allStreamHeight > _height )
	{
		int tempHeight = 0;	///< 削除する対象の文字列の高さを保持しておく

		//	一番先頭（古い）データを解放＆削除
		std::list<LogStream*>::iterator it = m_logStream.begin();
		tempHeight = (*it)->GetHeight();
		delete *it;
		m_logStream.pop_front();

		RealignmentStream();

		//	削除した文字の高さ分を引いて再度計算して、まだはみ出ていたらもう一度削除させる。
		if( allStreamHeight-tempHeight > _height )
			CheckStream( _height );
		result = true;	///< 中身を削除した事を伝える為にtrue
	}
	return result;
}

void GameLog::RealignmentStream()
{
	long tempX = m_posX, tempY = m_posY;	///<座標XYセット用(先頭ならGameLogの方に設定している座標を渡す)
	long beforeHeight = 0;	///<一つ前の文字列の高さが分かれば、Y座標をずらす事が出来る

	std::list<LogStream*>::const_iterator itEnd = m_logStream.end();
	for( std::list<LogStream*>::iterator it = m_logStream.begin();
		it != itEnd; ++it)
	{
		tempY += beforeHeight;
		beforeHeight = (*it)->GetHeight();
		(*it)->SetPosition( tempX, tempY );
		(*it)->GetPosition( tempX, tempY );
	}
}