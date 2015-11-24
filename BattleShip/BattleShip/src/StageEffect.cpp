/**
*@file	StageEffect.cpp
*@author	�T�c
*/

#include "StageEffect.h"
#include <cmath>
#include <cstdio>

#define _EFFECT_POS_TWEAK_	4.0f


bool StageEffect::Init()
{
	CheckOfMyShipPos();		///< 
	CheckSelectOfStage();	///< 
	
	return false;
}

void StageEffect::CheckSelectOfStage()
{
	for( int iPlayer = 0; iPlayer < _PLAYER_NUM_; iPlayer++ )
	{
		for( int iColumn = 0; iColumn < _STAGE_COLUMN_MAX_; iColumn++ )
		{
			for( int iLine = 0; iLine < _STAGE_LINE_MAX_; iLine++ )
			{

				int selectType = StageObject::SelectOfData( m_pStage->m_stageArray[iPlayer][iColumn][iLine]);
				//	�G�t�F�N�g�͍U�����G�̂�
				switch( selectType )
				{
				case StageObject::_SEARCH_NOMAL_:
				case StageObject::_SEARCH_ALL_:
				case StageObject::_ACTION_NOMAL_:
				case StageObject::_ACTION_ALL_:
					if( iPlayer == m_playerID/_PLAYER_NUM_ )	///<�v���C���[���̃}�X�i�G�ɂ��s���I���j
					{
						m_enemySelect.push_back(m_pStage->m_stageBlock[iPlayer][iColumn][iLine] );
						//	�G�̑I�������s�����v���C���[���̑I�����ꂽ�}�X���画�f����
						switch(selectType)
						{
							case StageObject::_SEARCH_NOMAL_:
							case StageObject::_SEARCH_ALL_:
								m_enemySelectType = _SELECT_SEARCH_;
								break;
							case StageObject::_ACTION_NOMAL_:
							case StageObject::_ACTION_ALL_:
								m_enemySelectType = _SELECT_ACTION_;
									break;
						}
					}
					else	///<�G���̃}�X�i�v���C���[�ɂ��s���}�X�j
					{
						m_playerSelect.push_back( m_pStage->m_stageBlock[iPlayer][iColumn][iLine] );						
					}
					break;
				}

			}
		}
	}
	D3DXVECTOR2 tempVec;	//���K�����s���ۂ̉��ۑ��x�N�g��
	//	�����ƃv���C���[�͍U��or���G�����Ă���Ȃ�
	if( !m_playerSelect.empty() )
	{
		//	�G�t�F�N�g�ɕK�v�ȍ��W��x�N�g�����Z�b�g���Ă�����B
		m_plTargetPointX = m_playerSelect[m_playerSelect.size()/2].GetPositionX();
		m_plTargetPointY = m_playerSelect[m_playerSelect.size()/2].GetPositionY();
		m_plTargetVector = D3DXVECTOR2( m_plTargetPointX-m_myShipBlock.GetPositionX(), m_plTargetPointY-m_myShipBlock.GetPositionY() );
		
		tempVec = m_plTargetVector;	///<��x�x�N�g���̐��K�����s��
		D3DXVec2Normalize( &m_plTargetVector, &tempVec );

		//	�ړ����x���|���Ă��B
		//	�`�掞�ɂ��̏����𖈉񂷂�͖̂ʓ|�B
		if( m_ShipCount >= ShipObject::TYPE_DESTROYER )
		{
			float tempX =( m_plTargetPointX-m_myShipBlock.GetPositionX() ) / static_cast<float>( TIME_CHANGE_EFFECT );
			float tempY =( m_plTargetPointY-m_myShipBlock.GetPositionY() ) / static_cast<float>( TIME_CHANGE_EFFECT );
			m_plTargetVector.x = tempX;
			m_plTargetVector.y = tempY;
		}
		else
		{
			m_plTargetVector.x *= _MOVE_SPEED_RECON_;
			m_plTargetVector.y *= _MOVE_SPEED_RECON_;
		}
	}
	//	�G�̏ꍇ��
	if( !m_enemySelect.empty() )
	{
		//	�G�t�F�N�g�ɕK�v�ȍ��W��x�N�g�����Z�b�g���Ă�����B
		//	�G�̏ꍇ��X���݂̂�K�������āA���m�Ȉʒu������ł����l�Ɍ����Ȃ��l�ɂ�����B
		//	�������A�G�t�F�N�g���o���Ƀv���C���[���ɏo�Ă���܂œ��߂Ȃǂ��������	
		for( unsigned int i=0; i<m_enemySelect.size(); i++ )
		{
			m_enTargetPointX += m_enemySelect[i].GetPositionX();
			m_enTargetPointY += m_enemySelect[i].GetPositionY();
		}
		//	�W�I���W�̕��ύ��W�𒲂ׂ�
		m_enTargetPointX = m_enTargetPointX/m_enemySelect.size();
		m_enTargetPointY = m_enTargetPointY/m_enemySelect.size();

		//	�G����X���̃|�W�V�����͉�ʒ[�
		m_enTargetVector = D3DXVECTOR2( m_enTargetPointX-( (m_playerID%_PLAYER_NUM_) * WIDTH), m_enTargetPointY-m_enTargetPointY );
		
		tempVec = m_enTargetVector;	///<��x�x�N�g���̐��K�����s��
		D3DXVec2Normalize( &m_enTargetVector, &tempVec );
		//Vec2Normalize( m_enTargetVector );	///<��x�x�N�g���̐��K�����s��
		
		//	�ړ����x���|���Ă��B
		//	�`�掞�ɂ��̏����𖈉񂷂�͖̂ʓ|�B
		if( m_ShipCount >= ShipObject::TYPE_DESTROYER )
		{
			m_enTargetVector.x *= ( fabs(((m_playerID%_PLAYER_NUM_) * WIDTH )-m_enTargetPointX) ) / TIME_CHANGE_EFFECT;
			m_enTargetVector.y *= (m_enTargetPointY-m_enTargetPointY) / TIME_CHANGE_EFFECT;
		}
		else
		{
			m_enTargetVector.x *= _MOVE_SPEED_RECON_;
			m_enTargetVector.y *= _MOVE_SPEED_RECON_;
		}
	}
	
}


void StageEffect::CheckOfMyShipPos()
{
	ShipObject* tempShip = m_pPlayer[m_playerID/_PLAYER_NUM_]->GetShip( static_cast<ShipObject::_SHIP_TYPE_NUM_>(m_ShipCount) );
	tempShip->GetArrayPos( m_actionShipPosColumn, m_actionShipPosLine );
	m_myShipBlock = m_pStage->m_stageBlock[m_playerID/_PLAYER_NUM_][m_actionShipPosColumn][m_actionShipPosLine];
}


int StageEffect::Control()
{
	//	�G�t�F�N�g���Đ�����ۂɊ�ɂ���J�E���^
	//	�����ł̓��O�ɒǉ��Ȃǂ�����B
	if( m_elapsedTimeFormStateInstance < TIME_END_RUSULT_EFFECT  )
	{
		EffectSoundControl();
	}
	else
	{
		
		return 1;
	}

	return 0;
}


//	
void StageEffect::Draw()
{
	//	�G�t�F�N�g���Đ�����ۂɊ�ɂ���J�E���^����
	if( m_elapsedTimeFormStateInstance < TIME_END_ACTION_EFFECT  )
	{
		AttackStartControl();
		SearchStartControl();
		
	}
	else if( m_elapsedTimeFormStateInstance < TIME_CHANGE_EFFECT )
	{
		//	�쒀�͂Ȃǂ̏ꍇ�͋��������X�ɖڕW�}�X�ɋ߂Â������̂ōU���G�t�F�N�g�`�������
		if( m_ShipCount >= ShipObject::TYPE_DESTROYER )
			AttackStartControl();
	}
	else if( m_elapsedTimeFormStateInstance < TIME_END_RUSULT_EFFECT )
	{
		HitEffectControl();
		SearchResultControl();
	}

}


void StageEffect::AttackStartControl()
{
	//	�v���C���[��
	if( m_plyaerSelectType == _SELECT_ACTION_ )
	{
		if( m_ShipCount == static_cast<int>(ShipObject::TYPE_AIRCARRIER) )
		{
			AircraftEffect( m_myShipBlock, 0 );
		}
		else if( m_ShipCount >= static_cast<int>(ShipObject::TYPE_DESTROYER) )
		{
			TorpedoEffect( m_myShipBlock );
		}
		else
		{

			FireEffect( m_myShipBlock );
		}
	}
	
	//	�G��
	if( m_enemySelectType == _SELECT_ACTION_ )
	{
		if( m_ShipCount == static_cast<int>(ShipObject::TYPE_AIRCARRIER) )
		{
			AircraftEffect( m_myShipBlock, 0, true );
		}
		else if( m_ShipCount >= static_cast<int>(ShipObject::TYPE_DESTROYER) )
		{
			TorpedoEffect( m_myShipBlock, true );
		}
		
	}
}

void StageEffect::SearchStartControl()
{
	
	//	�v���C���[��
	if( m_plyaerSelectType == _SELECT_SEARCH_ )
	{
		if( m_ShipCount >= static_cast<int>(ShipObject::TYPE_DESTROYER) )
		{
			SonarEffect( m_myShipBlock );
		}
		else
		{
			AircraftEffect( m_myShipBlock, 1 );
		}
	}
	//	�G��
	if( m_enemySelectType == _SELECT_SEARCH_ )
	{
		//	�G���͋쒀�����ȊO�͍��G�@���΂�
		if( m_ShipCount < static_cast<int>(ShipObject::TYPE_DESTROYER) )
		{
			AircraftEffect( m_myShipBlock, 1, true );
		}
	}
}

void StageEffect::HitEffectControl()
{
	/**
	*@details	�I�����ꂽ�}�X���G�t�F�N�g���o��
	*/

	//	�v���C���[��
	if( m_plyaerSelectType == _SELECT_ACTION_ )
	{
		for( unsigned int i = 0; i< m_playerSelect.size(); i++ )
		{
			ExplosionEffect( m_playerSelect[i] );
		}
	}
	
	//	�G��
	if( m_enemySelectType == _SELECT_ACTION_ )
	{
		for( unsigned int i = 0; i< m_enemySelect.size(); i++ )
		{
			ExplosionEffect( m_enemySelect[i] );
		}
	}

}

void StageEffect::SearchResultControl()
{
	/**
	*@details	�I�����ꂽ�}�X���G�t�F�N�g���o��
	*/

	if( m_plyaerSelectType == _SELECT_SEARCH_ )
	{
		for( unsigned int i = 0; i< m_playerSelect.size(); i++ )
		{
			SonarEffect( m_playerSelect[i] );
		}
	}
	if( m_enemySelectType == _SELECT_SEARCH_ )
	{
		for( unsigned int i = 0; i< m_enemySelect.size(); i++ )
		{
			SonarEffect( m_enemySelect[i] );
		}
	}

}


void StageEffect::FireEffect( BoardOfFrame& _block )
{
	float tempX, tempY;
	tempX = _block.GetPositionX()-_EFFECT_POS_TWEAK_;
	tempY = _block.GetPositionY()-_EFFECT_POS_TWEAK_;

	int wDiv = static_cast<int>(m_elapsedTimeFormStateInstance/_DIVISON_OF_EFFECT_TIME_);	///<�V�[���̌o�ߎ��Ԃ��牽�R�}�ڂ̃A�j���[�V�����������邩���v�Z�i�e�X�g�����j
	bool flipHorizontal = m_playerID/_PLAYER_NUM_ ? true : false;	///<�v���C���[�ɂ���ĉ摜�̔��]��������

	m_pDrawManager->AnimationDraw( _TEX_FIRE_EFFECT_, tempX, tempY, 
				_block.GetWidth()+_EFFECT_POS_TWEAK_*2, 
				_block.GetHeight()+_EFFECT_POS_TWEAK_*2,
				flipHorizontal, false, wDiv );	///<	�}�X�̕`��

	
}

void StageEffect::ExplosionEffect( BoardOfFrame& _block )
{
	
	float tempX, tempY;
	tempX = _block.GetPositionX();
	tempY = _block.GetPositionY();
	int wDiv = static_cast<int>(m_elapsedTimeFormStateInstance/_DIVISON_OF_EFFECT_TIME_);	///<�V�[���̌o�ߎ��Ԃ��牽�R�}�ڂ̃A�j���[�V�����������邩���v�Z�i�e�X�g�����j
	bool flipHorizontal = m_playerID/_PLAYER_NUM_ ? true : false;	///<�v���C���[�ɂ���ĉ摜�̔��]��������

	m_pDrawManager->AnimationDraw( _TEX_EXPLOSION_EFFECT_, tempX, tempY, 
				_block.GetWidth(), 
				_block.GetHeight(),
				flipHorizontal, false, wDiv );	///<	�}�X�̕`��

	
}

void StageEffect::AircraftEffect( BoardOfFrame& _block, int _aircraftType, bool _appearanceInvisibility )
{
	float tempX, tempY;
	bool flipHorizontal = m_playerID/_PLAYER_NUM_ ? true : false;	///<�v���C���[�ɂ���ĉ摜�̔��]��������
	unsigned long color = 0xffffffff;
	static const int multiplOfAircraftAlpha = 8;	///< �q��@�̃A���t�@�l��time�����Z���ďo���ۂ̐�
	int texNum;

	if( !_appearanceInvisibility )
	{
		//	�q��@�̈ړ���̈ʒu���Q�[���J�E���g�Ő���
		tempX = _block.GetPositionX()+(m_plTargetVector.x)*m_elapsedTimeFormStateInstance;
		tempY = _block.GetPositionY()+(m_plTargetVector.y)*m_elapsedTimeFormStateInstance;
	}
	//	�o���ʒu���B�������ꍇ
	else 
	{
		int alpha = 0;
		/*
			�ǂ���̃v���C���[���q��@���΂��Ă��邩�����f���Ȃ���
			�ǂ̏ꏊ�����΂��ĉ���������Ηǂ���������Ȃ��B
			��U���Ώۑ��̐w�n�ɓ������ꍇ�A���X�ɃA���t�@�l���グ�Ă����B
		*/
		//	�o���ʒu�͑��葤�̉�ʒ[
		tempX = ( (m_playerID%_PLAYER_NUM_) * WIDTH )+(m_enTargetVector.x)*m_elapsedTimeFormStateInstance;
		tempY = m_enTargetPointY+(m_enTargetVector.y)*m_elapsedTimeFormStateInstance;
									
		alpha = m_elapsedTimeFormStateInstance*multiplOfAircraftAlpha;
		
		if( alpha >= 255 )
			alpha = 255;

		color = D3DCOLOR_ARGB( alpha, 255, 255, 255 );	///< �A���t�@�l���J���[�l�ɓ����
		flipHorizontal = m_playerID/_PLAYER_NUM_ ? false : true;	///< �����Ă�����͍��̎��_�ł͎��g�Ƃ�
	}
	//	�q��@�̃e�N�X�`����ݒ�
	switch( _aircraftType )
	{
	case 0:
		texNum = _TEX_RECON_;
		break;
	case 1:
		texNum = _TEX_RECON_;
		break;
	}
	m_pDrawManager->AnimationDraw( texNum, tempX, tempY, 
				_block.GetWidth(), 
				_block.GetHeight(),
				flipHorizontal, false, 0, 0, color );	///<	�}�X�̕`��
}


void StageEffect::TorpedoEffect( BoardOfFrame& _block, bool _appearanceInvisibility )
{
	float tempX, tempY;
	bool flipHorizontal = m_playerID/_PLAYER_NUM_ ? true : false;	///<�v���C���[�ɂ���ĉ摜�̔��]��������
	unsigned long color = 0xe0a0a0ff;
	static const int multiplOfTorpedoAlpha = 4;	///< �q��@�̃A���t�@�l��time�����Z���ďo���ۂ̐�
	int texNum = _TEX_TORPEDO_;

	if( !_appearanceInvisibility )
	{
		//	�q��@�̈ړ���̈ʒu���Q�[���J�E���g�Ő���
		tempX = _block.GetPositionX()+((m_plTargetVector.x)*m_elapsedTimeFormStateInstance);
		tempY = _block.GetPositionY()+((m_plTargetVector.y)*m_elapsedTimeFormStateInstance);
	}
	//	�o���ʒu���B�������ꍇ
	else 
	{
		int alpha = 0;
		/*
			�ǂ���̃v���C���[���q��@���΂��Ă��邩�����f���Ȃ���
			�ǂ̏ꏊ�����΂��ĉ���������Ηǂ���������Ȃ��B
			��U���Ώۑ��̐w�n�ɓ������ꍇ�A���X�ɃA���t�@�l���グ�Ă����B
		*/
		//	�o���ʒu�͑��葤�̉�ʒ[
		tempX = ( (m_playerID%_PLAYER_NUM_) * WIDTH )+(m_enTargetVector.x)*m_elapsedTimeFormStateInstance;
		tempY = m_enTargetPointY+(m_enTargetVector.y)*m_elapsedTimeFormStateInstance;
									
		alpha = m_elapsedTimeFormStateInstance*multiplOfTorpedoAlpha;
		
		if( alpha >= 224 )
			alpha = 224;

		color = D3DCOLOR_ARGB( alpha, 160, 160, 255 );	///< �A���t�@�l���J���[�l�ɓ����
		flipHorizontal = m_playerID/_PLAYER_NUM_ ? false : true;	///< �����Ă�����͍��̎��_�ł͎��g�Ƃ�
	}
	
	m_pDrawManager->AnimationDraw( texNum, tempX, tempY, 
				_block.GetWidth(), 
				_block.GetHeight(),
				flipHorizontal, false, 0, 0, color );	///<	�}�X�̕`��
}

void StageEffect::SonarEffect( BoardOfFrame& _block )
{
	/**
	*@details	0�`8�b 12�`20�b 4�`12�b �̂R�p�^�[���̒��ŁA���G������W�̒��S����A
				�~�̉摜���o�ߎ���%8/5�i���ꂪ�F�X���������ň�Ԍ����ڂ��ǂ������j��
				�k�����g�傳���Ă����B
				4�`12�b�̃p�^�[�����o�ߎ���%8+4/5�Ȃ̂͑���2�p�^�[���Ƃ̍������邽�߁B
	*/
	if( m_elapsedTimeFormStateInstance <= 8 || m_elapsedTimeFormStateInstance >= 12 )
	{
		float tempX, tempY, tempW, tempH;
		int Alpha = 255;
		tempX = _block.GetPositionX()+_BLOCK_WIDTH_SIZE_/2;
		tempY = _block.GetPositionY()+_BLOCK_HEIGHT_SIZE_/2;		
		tempW = _block.GetWidth() *(m_elapsedTimeFormStateInstance%8)/5;
		tempH =	_block.GetHeight()*(m_elapsedTimeFormStateInstance%8)/5;
		Alpha -= (m_elapsedTimeFormStateInstance%(TIME_END_ACTION_EFFECT/2))*2;
		m_pDrawManager->CenterDraw( _TEX_SEARCH_EFFECT_, tempX, tempY, 0.f, 
					tempW, tempH, 0.f, 0.f, 1.f, 1.f, Alpha, 255, 255, 255 );
	}
	if( m_elapsedTimeFormStateInstance >= 4 || m_elapsedTimeFormStateInstance <= 12 )
	{
		float tempX, tempY, tempW, tempH;
		int Alpha = 255;
		tempX = _block.GetPositionX()+_BLOCK_WIDTH_SIZE_/2;
		tempY = _block.GetPositionY()+_BLOCK_HEIGHT_SIZE_/2;
		tempW = _block.GetWidth() *((m_elapsedTimeFormStateInstance%8)+4)/5;
		tempH =	_block.GetHeight()*((m_elapsedTimeFormStateInstance%8)+4)/5;
		Alpha -= (m_elapsedTimeFormStateInstance%(TIME_END_ACTION_EFFECT/2))*2;

	m_pDrawManager->CenterDraw( _TEX_SEARCH_EFFECT_, tempX, tempY, 0.f, 
				tempW, tempH, 0.f, 0.f, 1.f, 1.f, Alpha, 255, 255, 255 );	///<	�}�X�̕`��

	}
}


int StageEffect::Vec2Normalize( D3DXVECTOR2& _vec2 )
{
	float x, y;
	float len;
	x = _vec2.x;
	y = _vec2.y;
	len = 1/hypotf(x,y);
	if( len <= 0 )	return 0;
	_vec2.x *= len;
	_vec2.y *= len;
	return 1;
}

void StageEffect::EffectSoundControl()
{
	/*
		�s�i�D�ł�����芸�������Ԃɍ��킹�Ċe�͕ʂɔ���SE��ς����肵�Ă��܂�
	*/
	switch(m_plyaerSelectType)
	{
		//	�U��
	case _SELECT_ACTION_:
		//	�G�t�F�N�g�J�n
		if( m_elapsedTimeFormStateInstance == 0 ){
			switch(m_ShipCount)
			{
			case ShipObject::TYPE_AIRCARRIER:
				m_pAudio->SoundPlay( Audio::_AIRCRAFT_SE_ );
				break;
			case ShipObject::TYPE_BATTLESHIP:
				m_pAudio->SoundPlay( Audio::_FIRE_H_SE_ );
				break;
			case ShipObject::TYPE_CRUISER:
				m_pAudio->SoundPlay( Audio::_FIRE_M_SE_ );
				break;
			case ShipObject::TYPE_DESTROYER:
			case ShipObject::TYPE_SUBMARINE:
				m_pAudio->SoundPlay( Audio::_TORPEDO_SE_ );

				break; 
			}
		
		}
		//	�G�t�F�N�g����
		if( m_elapsedTimeFormStateInstance == TIME_END_ACTION_EFFECT ){
			if( m_ShipCount == ShipObject::TYPE_AIRCARRIER ) 
				m_pAudio->SoundPlay( Audio::_AC_ATTACK_SE_ );
		}
		//	�G�t�F�N�g�I��
		if( m_elapsedTimeFormStateInstance == TIME_CHANGE_EFFECT ){
			m_pAudio->SoundPlay( Audio::_WATER_SE_ );
			m_pAudio->SoundPlay( Audio::_EXPLOSION_SE_ );
		}

		break;

		//	���G
	case _SELECT_SEARCH_:
		//	�G�t�F�N�g�J�n
		if( m_elapsedTimeFormStateInstance == 0 ){
			if( m_ShipCount <= ShipObject::TYPE_CRUISER ){
				m_pAudio->SoundPlay( Audio::_AIRCRAFT_SE_ );
			}else{
				m_pAudio->SoundPlay( Audio::_SONAR_SE_ );
			}
		}
		//	�G�t�F�N�g����
		if( m_elapsedTimeFormStateInstance == TIME_END_ACTION_EFFECT ){
			
		}
		//	�G�t�F�N�g�I��
		if( m_elapsedTimeFormStateInstance == TIME_CHANGE_EFFECT ){
			m_pAudio->SoundPlay( Audio::_SONAR_SE_ );
		}
		break;
	}		 
	
	//	�G��
	switch(m_enemySelectType)
	{
		//	�U��
	case _SELECT_ACTION_:
		//	�G�t�F�N�g�J�n
		if( m_elapsedTimeFormStateInstance == 0 ){
			switch(m_ShipCount)
			{
			case ShipObject::TYPE_AIRCARRIER:
				m_pAudio->SoundPlay( Audio::_AIRCRAFT_SE_ );
				break;
			case ShipObject::TYPE_BATTLESHIP:
				m_pAudio->SoundPlay( Audio::_FIRE_H_SE_ );
				break;
			case ShipObject::TYPE_CRUISER:
				m_pAudio->SoundPlay( Audio::_FIRE_M_SE_ );
				break;
			case ShipObject::TYPE_DESTROYER:
			case ShipObject::TYPE_SUBMARINE:
				m_pAudio->SoundPlay( Audio::_FIRE_L_SE_ );

				break; 
			}
		
		}
		//	�G�t�F�N�g����
		if( m_elapsedTimeFormStateInstance == TIME_END_ACTION_EFFECT ){
			if( m_ShipCount == ShipObject::TYPE_AIRCARRIER ) 
				m_pAudio->SoundPlay( Audio::_AC_ATTACK_SE_ );
		}
		//	�G�t�F�N�g�I��
		if( m_elapsedTimeFormStateInstance == TIME_CHANGE_EFFECT ){
			m_pAudio->SoundPlay( Audio::_WATER_SE_ );
			m_pAudio->SoundPlay( Audio::_EXPLOSION_SE_ );
		}

		break;

		//	���G
	case _SELECT_SEARCH_:
		//	�G�t�F�N�g�J�n
		if( m_elapsedTimeFormStateInstance == 0 ){
			if( m_ShipCount <= ShipObject::TYPE_CRUISER ){
				m_pAudio->SoundPlay( Audio::_AIRCRAFT_SE_ );
			}else{
				m_pAudio->SoundPlay( Audio::_SONAR_SE_ );
			}
		}
		//	�G�t�F�N�g����
		if( m_elapsedTimeFormStateInstance == TIME_END_ACTION_EFFECT ){
			
		}
		//	�G�t�F�N�g�I��
		if( m_elapsedTimeFormStateInstance == TIME_CHANGE_EFFECT ){
			m_pAudio->SoundPlay( Audio::_SONAR_SE_ );
		}
		break;
	}

}