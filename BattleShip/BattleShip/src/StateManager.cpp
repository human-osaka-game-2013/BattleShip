/**
*@file	StateManager.cpp
*@author	�T�c
*/

#include "StateManager.h"

//--------�X�e�[�g�p�^�[���N���X�̃w�b�_�[-------
#include "SetShip.h"
#include "Selection.h"
#include "Result.h"
#include "StageEffect.h"
//-------------------------------------------
#include "DebugNew.h"


#define _FIRST_SETATE_ StateManager::STATE_SET_SHIP	///<	�ŏ��̃X�e�[�g�p�^�[��
#define _POS_PLAYER1FRAME_	0.f, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)						///<�v���C���[1���̘g�̕\�����W
#define _POS_PLAYER2FRAME_	_BLOCK_WIDTH_SIZE_*12, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)	///<�v���C���[2���̘g�̕\�����W
#define _SIZE_PLAYERFRAME_	_BLOCK_WIDTH_SIZE_*11, _BLOCK_HEIGHT_SIZE_*5	///<�v���C���[���̘g�T�C�Y


//#define _DEBUG_SCENE_TEST_

//	�R���X�g���N�^ 
StateManager::StateManager( Player* const _pPlayer1, Player* const _pPlayer2, 
							StageObject* const _pStageObject, const int _playerID) 
	: m_pPlayer1(_pPlayer1), m_pPlayer2(_pPlayer2), m_pStageObject( _pStageObject), m_playerID(_playerID)
{
	m_connectFlag = false;
	m_resultPlayer	= static_cast<int>(Result::RESULT_NONE);
	m_resultEnemy	= static_cast<int>(Result::RESULT_NONE);
	m_resultBattle	= static_cast<int>(Result::TYPE_DRAW);
	m_plyaerSelectType	= static_cast<int>(GameState::_SELECT_NONE_);
	m_turnCount = 1;
}

//	�X�e�[�g�̏�����
void StateManager::StateInit()
{
	m_beforeState	= STATE_NONE;		///<	�������Ȃ̂ňȑO�̃X�e�[�g�͂������������ׁASTATE_NONE�ɁB
	m_currentState	= _FIRST_SETATE_;///<	�X�e�[�g�̏������Ȃ̂ōŏ��ɓǂݍ��ނł��낤�p�^�[���̒萔������
	m_currentShip	= ShipObject::TYPE_AIRCARRIER;	///<	�����I����͋��Ȃ̂Ő��l�����ɃZ�b�g�B
	
	m_StageFrame.Init( 0.f, -2.f, WIDTH, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_));
	///<��ʏ㕔����P�P�}�X���ڂ܂ŔՖʃt���[��������̂�11/16�ƂȂ�B
	m_PlayerFrame[0].Init( _POS_PLAYER1FRAME_, _SIZE_PLAYERFRAME_ );
	m_PlayerFrame[1].Init( _POS_PLAYER2FRAME_, _SIZE_PLAYERFRAME_ );

	//	�Q�[�����O�̏�����
	int plIndex = m_playerID%2;	
	m_gameLog.Init( static_cast<long>( m_PlayerFrame[plIndex].GetPositionX() + static_cast<long>(_LOG_POS_TWEAK_)), 
		static_cast<long>( m_PlayerFrame[plIndex].GetPositionY() + static_cast<long>(_LOG_POS_TWEAK_)) );
	//	�Q�[���o�ߎ��ԃ��O�̏�����
	m_gameElapsed.Init( static_cast<long>( m_PlayerFrame[plIndex].GetPositionX() + static_cast<long>(_LOG_POS_TWEAK_) ),
		static_cast<long>( m_PlayerFrame[plIndex].GetPositionY()) + static_cast<long>(_LOG_HEIGHT_MAX_) );
	//	�ʐM��ԃ��O�̏�����
	float tempX = ( m_playerID/_PLAYER_NUM_ ? (_BOARD_OF_SHIPDATA_LINE_P1_) : (_BOARD_OF_SHIPDATA_LINE_P2_+_SHIP_ARRAY_INDEX_) ) * _BLOCK_WIDTH_SIZE_;
	m_gameConnectState.Init( static_cast<long>( tempX ), static_cast<long>( m_PlayerFrame[plIndex].GetPositionY()) + static_cast<long>(_LOG_HEIGHT_MAX_) );

	m_tempStr1 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::START_BATTLE];
	m_gameLog.AddStream( m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
	
	//	�X�e�[�g�ύX�i���������j
	ChangeState(m_currentState);	///<	�܂��X�e�[�g�|�C���g�ɂ͉��������Ă��Ȃ��̂ŏ����������˂�

	m_beforeShip = -1;	///<�O�t���[���őI���i�Ώہj����Ă�����ێ����Ă����B�ŏ��ɓ����Ă����ꍇ�͏����l�Ƃ���-1�����Ă���B	

	for( int iPlayer=0; iPlayer<_PLAYER_NUM_; iPlayer++ )	///<�\���ʒu�Ȃǂ�\�ߏ��������Ă����A�`�掞�ⓖ���蔻�莞�Ȃǂɂ����p����B
	{
		float tempX, tempY;	
		//	�͎핪���[�v�őS�Ă̋��������
		for( int iShip=0; iShip<ShipObject::TYPE_MAX; iShip++ ){

		//	------����̃X�e�[�^�X�i���Q���j�̏�����------
			float tempW = _BLOCK_WIDTH_SIZE_, tempH = _BLOCK_HEIGHT_SIZE_;	///<��ʂɉϐ�������̂ŏc�����̉��ۑ������ď����������グ��B
			tempX = tempW;
			tempY = (_STAGE_HEIGHT_MAX_*tempH)+(iShip*tempH);	///<Y���W�͂܂��v���C���[���g�̊�_����
			
			//	��̌����̏�����
			ShipObject* tempShip;
			
			if( iPlayer == 0 ){
				tempX += tempW*5;	///<�v���C���[1��1�}�X�ڂ���5�}�X�����炷�̂�
				tempShip = m_pPlayer1->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
			}else{
				tempX += tempW*11;	///<�v���C���[2��1�}�X�ڂ���11�}�X�����炷�̂�
				tempShip = m_pPlayer2->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
			}
		}
	}
}

//	�X�e�[�g�̊�{���[�`������
int StateManager::StateCotrol()
{
	m_beforeState = m_currentState;	///<	���[�`���I�ɂȏ����őO�t���[�����̃X�e�[�g�����݂̃X�e�[�g�ɍ��킹��B
	int stateResult = this->CheckState();	///<	�X�e�[�g�̕ύX�`�F�b�N�̏���
	UpdateStatInTime( m_stateTime );	///<	�^�C���̍X�V
	
#ifdef _DEBUG_SCENE_TEST_
	stateResult = -1;

#endif
	if( stateResult == 1 )	///<	�X�e�[�g�̃��[�`�������̌��ʃV�[�����ς��K�v�������
	{
		switch( m_currentState )	///<	�ύX����X�e�[�g�͏��Ԃ�������x���܂��Ă���̂ŕ���
		{
		case STATE_SET_SHIP:
			ChangeState(STATE_SELECTION);

			break;
		case STATE_SELECTION:
			ChangeState(STATE_STAGE_EFFECT);

			break;
		case STATE_STAGE_EFFECT:
			ChangeState(STATE_RESULT);
			
			break;
		case STATE_RESULT:
			ChangeState(STATE_SELECTION);

			break;
		}
	}
	else if( stateResult == -1 )
	{
		m_pAudio->SoundAllStop();
		//	�퓬�I���ɔ����틵�̍ŏI���ʂ����O�ɕ\��
		if( m_resultBattle == Result::TYPE_DRAW )
		{
			m_tempStr1 = m_gameLog.GetPhrase( FixedPhrase::RESULT_DRAW_STR );
			m_pAudio->SoundPlay( Audio::_TITLE_BGM_, true );
		}
		else if( m_resultBattle == Result::TYPE_VICTORY )
		{
			m_tempStr1 = m_gameLog.GetPhrase( FixedPhrase::RESULT_VICTORY_STR );
			m_pAudio->SoundPlay( Audio::_WIN_BGM_, true );
		}
		else if( m_resultBattle == Result::TYPE_DEFEAT )
		{
			m_tempStr1 = m_gameLog.GetPhrase( FixedPhrase::RESULT_DEFEAT_STR );
			m_pAudio->SoundPlay( Audio::_LOSE_BGM_, true );
		}
		m_gameLog.AddStream( m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		//	�퓬�I�����O��\��
		m_tempStr1 = m_gameLog.GetPhrase( FixedPhrase::RESULT_END );
		m_gameLog.AddStream( m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		m_tempStr1 = "���N���b�N�Ń^�C�g���ɖ߂�܂��傤";
		m_gameLog.AddStream( m_tempStr1.c_str(), _LOG_COLOR_NOMAL_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
	}
	
	return stateResult;
}

int StateManager::CheckState()
{
	
	int checkResult = 0;
	int stageResult = 0;

	//	�퓬���s���Ȃ�e�X�e�[�g�̏�����ʂ�
	//	�ʐM��K�v�Ƃ���X�e�[�g��SetShip�ASelection�݂̂Ȃ̂ŁA���̃X�e�[�g�ł͂���m_connectFlag�ɂ͊����Ȃ����B
	m_pGameState->SetConnectFlag( m_connectFlag );	//	���t���[���ʐM�̃t���O���X�V
	stageResult = m_pGameState->Control();	///<�@�X�e�[�g���Ƃ̏����Ɉڍs
	SetConnectFlag( m_pGameState->GetConnectFlag() );	//	�X�e�[�g���ł̃t���O�ύX�𔽉f������
	
	switch( m_currentState )	///<�@�V�[�����ɃX�e�[�g�̌��ʂւ̑Ώ����ς��̂ŕ���
	{
	case STATE_SET_SHIP:
		//	��z�u�𑣂����O���o��
		if( m_beforeShip != m_currentShip && m_currentShip != ShipObject::TYPE_MAX )
		{
			m_tempStr2 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::SET_PHRASE_STR];
			
			m_tempStr1 = m_gameLog.GetMultiplePhrase( 2, static_cast<int>(m_currentShip), static_cast<int>(FixedPhrase::SET_PHRASE_STR) );
			m_gameLog.AddStream( m_tempStr1.c_str() );
		}

		if( m_currentShip >= ShipObject::TYPE_MAX && !m_connectFlag )	///<�@�S�Ă̋�Z�b�g���ꂽ
			checkResult = 1;
		break;

	case STATE_SELECTION:
		if( stageResult == 1 && !m_connectFlag ){	///<�@���ʂ�1���A�ʐM���������Ă����ꍇ
			Selection* pSelection = dynamic_cast<Selection*>(m_pGameState);	///<Selection�̊֐��ɃA�N�Z�X����K�v������̂ŁA�_�E���L���X�g����B
			m_plyaerSelectType = pSelection->GetSelectionType();
		
			checkResult = 1;	///<�@�I�����ʂɈڂ�
		}
		break;

	case STATE_STAGE_EFFECT:
		if( stageResult == 1 ){	///<�@���ʂ�1(�X�e�[�W�̉��o������)�̏ꍇ
			
			checkResult = 1;
		}
		break;

	case STATE_RESULT:
		//����or�s�kor�퓬�I��
		if( stageResult == Result::TYPE_VICTORY || stageResult == Result::TYPE_DEFEAT )
		{
			Result* pResult = dynamic_cast<Result*>(m_pGameState);	///<Result�̊֐��ɃA�N�Z�X����K�v������̂ŁA�_�E���L���X�g����B
			checkResult = -1;	//StateManager���ɐ퓬���ʁ��퓬�I���������������Ă��B
			pResult->GetResultOfBattle( m_resultBattle );
			m_pStageObject->ResetSelect();	//�����������̂őI�����͏���
		}
		//���s�͂܂����Ă��Ȃ�
		else	
		{
			Result* pResult = dynamic_cast<Result*>(m_pGameState);	///<Result�̊֐��ɃA�N�Z�X����K�v������̂ŁA�_�E���L���X�g����B
			pResult->GetResultPlayerAndEnemy( m_resultPlayer, m_resultEnemy );
			pResult->GetResultOfBattle( m_resultBattle );
			checkResult = 1;
			m_pStageObject->ResetSelect();	//�����������̂őI�����͏���
			
			// Selection�X�e�[�g�Ɉڂ�O�Ɍ��݂̃^�[�����I�������̂Ŏ��̋���w��
			if( m_currentShip < ShipObject::TYPE_SUBMARINE){

				m_currentShip = static_cast< ShipObject::_SHIP_TYPE_NUM_ >( m_beforeShip+1 );
			}else{
				//	�e�͂̍s���t�F�[�Y����������̂Ń^�[�����𑝂₷
				m_turnCount++;
				m_currentShip = ShipObject::TYPE_AIRCARRIER;
			}
		}

		break;
	
	}

	///< �X�e�[�g��Control���I������̂őO�t���[���ł̑I������X�V
	m_beforeShip = static_cast<int>(m_currentShip);
	return checkResult;
}

//	�X�e�[�g�p�^�[���̐؂�ւ�
bool StateManager::ChangeState( _STATE_NUM_ _stateType )
{
	if( _stateType > STATE_STAGE_EFFECT&& _stateType < STATE_SET_SHIP )
	{
		MessageBoxA(0,"�X�e�[�g�p�^�[���̕ύX�Ɏ��s���܂����I\n�������m�F���ĉ������I(����;)",NULL,MB_OK);
		return false;
	}
	
	//	���łɃX�e�[�g�����܂��Ă����ꍇ�i�ύX����ہj�͑O�̃C���X�^���X�����������̂������K�v������B
	if( m_beforeState != STATE_NONE )
	{
		CLASS_DELETE(m_pGameState); 
	}
	//	�e�X�e�[�g�ʂɃX�e�[�g����
	switch( _stateType )
	{
	case STATE_SET_SHIP:
		m_tempStr1 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::STATE_SET_SHIP_STR];
		m_gameLog.AddStream(m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		// ����͍ŏ��ɔz�u����̂͋��ŁACheckState�֐����ł͋��̃��O
		m_pGameState = new SetShip( m_currentShip, &m_gameLog );

		break;
	case STATE_SELECTION:
		m_tempStr1 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::STATE_SELECTION_STR];
		m_gameLog.AddStream(m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		m_pGameState = new Selection( m_currentShip, &m_gameLog );

		break;

	case STATE_STAGE_EFFECT:
		m_pGameState = new StageEffect( m_currentShip, &m_gameLog );
		static_cast<StageEffect*>(m_pGameState)->SetSelectionType( m_plyaerSelectType );	///<�G�t�F�N�g�ɂ͂ǂ̍s����I���������̔��f������̂ŏ���n���Ă��B
		break;

	case STATE_RESULT:
		m_tempStr1 = m_gameLog.m_fixedPhrase.m_phrase[FixedPhrase::STATE_RESULT_STR];
		m_gameLog.AddStream(m_tempStr1.c_str(), _LOG_COLOR_DEFAULT_, _LOG_FONT_BIGSIZE_, _LOG_FONT_BIGSIZE_, DT_CENTER );
		m_pGameState = new Result( m_currentShip, &m_gameLog );

		break;
	}


	m_currentState = _stateType;	///<	���݂̃X�e�[�g�ϐ����X�V
	
	if( m_currentShip >= ShipObject::TYPE_MAX )	///<	�X�e�[�g�ύX�̂��łɑI����͈͂𒴂��Ă��邩�`�F�b�N
		m_currentShip = ShipObject::TYPE_AIRCARRIER;	///<	���ɕύX

	//	�X�e�[�g���ς�����̂ŁA��A�̏��������s��
	m_pGameState->SetPlayerPtr( m_pPlayer1, 0 );
	m_pGameState->SetPlayerPtr( m_pPlayer2, 1 );
	m_pGameState->SetStagePtr( m_pStageObject );
	m_pGameState->SetDraw( m_pDrawManager );
	m_pGameState->SetMouse( m_pMouse );
	m_pGameState->SetAudio( m_pAudio );
	m_pGameState->SetPlayerID( m_playerID );
	m_pGameState->Init();	///<�Ō�ɃX�e�[�g���̏��������s���i�����͂��̃N���X�������Ă��錻�݂̑I����j

	return true;
}

//	�X�e�[�g�̊�{�`��
void StateManager::StateDraw()
{	
	DrawStageFrame();

	//	�X�e�[�g�ʂ̕`��
	m_pGameState->Draw();

	DrawLog();

	//	�ʐM�҂���
	if( GetConnectFlag() )
	{
		m_pGameState->ComStandby( m_gameConnectState );
	}
}

void StateManager::DrawStageFrame()
{	
	float tempX, tempY;

	if( m_playerID == 1 )
	{
		//	�v���C���[1�g�\��
		m_PlayerFrame[0].GetPosition( &tempX, &tempY );
		m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
			m_PlayerFrame[0].GetWidth(),  m_PlayerFrame[0].GetHeight(),
			0.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
			11/_BLOCK_WIDTH_MAX_, 1.f,
			180, 255, 100, 100);	///<	�v���C���[1�̘g�`��
		
	}
	else
	{
		//	�v���C���[2�g�\��
		m_PlayerFrame[1].GetPosition( &tempX, &tempY );
		m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
			m_PlayerFrame[1].GetWidth(),  m_PlayerFrame[1].GetHeight(),
			12/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
			1.f, 1.f,
			180, 100, 100, 255);	///<	�v���C���[2�̘g�`��
	}

	//	�v���C���[�����[�v���āA��ƃ}�X�ڂ�`�悷��
	for( int ip=0; ip<_PLAYER_NUM_; ip++ )
	{
		DrawShipObject( ip );
		DrawStageBlock( ip );
	}
	
	//	�Ֆʘg�\���i���j
	m_StageFrame.GetPosition( &tempX, &tempY );
	m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		0.f, 0.f, 
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);	///<	�Ֆʂ̍����̕`��

	//	�Ֆʘg�\���i�E�j
	m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*12, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 0.f, 
		1.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);	///<	�Ֆʂ̉E���̕`��

	//	�Ֆʘg�\���i���j
	m_pDrawManager->VertexDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*_STAGE_WIDTH_MAX_, tempY, 
		_BLOCK_WIDTH_SIZE_, HEIGHT,
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, 0.f,
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 1.f,
		100, 220, 220, 220);	///<	�Ֆʂ̐^�񒆂̕`��

	
}

void StateManager::DrawShipObject( const int _playerIndex )
{
	//	�v���C���[�ʂ̋���̕\��
	for( int iShip=0; iShip<ShipObject::TYPE_MAX; iShip++ )
	{
		//	�X�e�[�W��̋�̕\��
		float tempW = _BLOCK_WIDTH_SIZE_;	
		float tempH = _BLOCK_HEIGHT_SIZE_;
		
		/**
		*@todo	���݂͎��g�̋�݂̂�\�����Ă���B
		*/
		if( _playerIndex == m_playerID-1 )	///<���͎����̃v���C���[�̋���\�����Ȃ�
		{
			Player* tempPlayer = m_playerID%_PLAYER_NUM_ ? m_pPlayer1:m_pPlayer2;
			ShipObject* tempShip = tempPlayer->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
				
			if( !tempShip->GetDeadFlag() )
			{
				//	�Ֆʏ�ɒu����Ă��鎩���̋��`��
				m_pDrawManager->VertexTransform( iShip + _TEX_AIRCARRIER_, tempShip->m_vertex, 
					tempShip->GetPositionX(), tempShip->GetPositionY(), 1.f, 1.f, tempShip->GetDirection()*90.f );
				
				if( _playerIndex== 0 ){	//	�v���C���[1�̏ꍇ
					//	�z�u�������̂���v���C���[���̏���������`��
					m_pDrawManager->VertexTransform( iShip + _TEX_AIRCARRIER_, tempShip->m_vertex, 
						(_BOARD_OF_SHIPDATA_LINE_P1_*tempW)+(tempW/2), ((_BOARD_OF_SHIPDATA_COLUMN_+iShip)*tempH) + (tempH/2),
						1.f, 1.f, CGameObject::CH_RIGHT*90.f );

				}else{	//	�v���C���[2�̏ꍇ

					//	�z�u�������̂���v���C���[���̏���������`��
					m_pDrawManager->VertexTransform( iShip + _TEX_AIRCARRIER_, tempShip->m_vertex, 
						(_BOARD_OF_SHIPDATA_LINE_P2_*tempW)+(tempW/2), ((_BOARD_OF_SHIPDATA_COLUMN_+iShip)*tempH) + (tempH/2),
						1.f, 1.f, CGameObject::CH_RIGHT*90.f );
				}
				
			}
		}
		
	}
		
}


void StateManager::DrawStageBlock( const int _playerIndex )
{
	float tempX, tempY;

	//	�s
	for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ )
	{	
		//	��
		for( int il=0; il<_STAGE_LINE_MAX_; il++ )
		{
			m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetPosition( &tempX, &tempY );
			
			int tempA = 0, tempR = 200, tempG = 200, tempB = 200;
			int tempArrayData = m_pStageObject->m_stageArray[_playerIndex][ic][il];
		
			//	�I���}�Xor�����}�X�͌�����悤�ɂ���
			if( StageObject::SelectOfData(tempArrayData) != StageObject::_SELECT_NOMAL_ ||
				StageObject::ConditionOfData(tempArrayData) == StageObject::_CONDITION_DAMAGE_)
			{
					
				//	�͈͎w�茅�`�F�b�N
				switch( StageObject::SelectOfData(tempArrayData) )
				{
				case StageObject::_SELECT_TRUE_:	///<�I������Ă���}�X
					tempA = 100;
					break;
				case StageObject::_SELECT_FALSE_:	///<��u���Ȃ�or�I��͈͂������ɐڐG���Ă���}�X
					tempA = 100, tempR = 255, tempG = 0, tempB = 0;
					break;
				case StageObject::_SEARCH_NOMAL_:
				case StageObject::_SEARCH_ALL_:
					tempA = 100, tempR = 0, tempG = 255, tempB = 0;
					break;
				case StageObject::_ACTION_NOMAL_:
				case StageObject::_ACTION_ALL_:
					tempA = 100, tempR = 0, tempG = 0, tempB = 255;
					break;
				}
	
				//	������Ԍ��`�F�b�N
				switch( StageObject::ConditionOfData(tempArrayData) )
				{
				case StageObject::_CONDITION_NONE_:
				case StageObject::_CONDITION_NOMAL_:
					break;
				case StageObject::_CONDITION_DAMAGE_:
					tempA = 200, tempR = 100, tempG = 50, tempB = 50;
					break;
	
				}
				
			m_pDrawManager->VertexDraw( _TEX_BLOCK_, tempX, tempY, 
				m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetWidth(), 
				m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetHeight(),
				0.f, 0.f, 
				1.f, 1.f,
				tempA, tempR, tempG, tempB);	///<	�}�X�̕`��
			}
			m_pDrawManager->VertexDraw( _TEX_BLOCKFRAME_, tempX, tempY, 
				m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetWidth(), 
				m_pStageObject->m_stageBlock[_playerIndex][ic][il].GetHeight(),
				0.f, 0.f, 
				1.f, 1.f,
				100, 200, 200, 200);	///<	�}�X�̕`��
		}
	}
}

void StateManager::DrawLog()
{
	DirectXFont* const pDxFont =  &m_pDrawManager->m_dxFont;
	int logValue = 0;
	float tempX, tempY;

	//���O�̘g�\��
	if( m_playerID == 1 )
	{
		//	�Q�[�����O�\��
		m_PlayerFrame[1].GetPosition( &tempX, &tempY );
		m_pDrawManager->VertexDraw( _TEX_GAMELOG_, tempX, tempY, 
			m_PlayerFrame[1].GetWidth(),  m_PlayerFrame[1].GetHeight(),
			0.f, 0.f, 1.f, 1.f,
			200, 255, 255, 255 );	///<	�v���C���[2�̘g�`��
	}
	else
	{
		//	�Q�[�����O�\��
		m_PlayerFrame[0].GetPosition( &tempX, &tempY );
		m_pDrawManager->VertexDraw( _TEX_GAMELOG_, tempX, tempY, 
			m_PlayerFrame[0].GetWidth(),  m_PlayerFrame[0].GetHeight(),
			0.f, 0.f, 1.f, 1.f,
			200, 255, 255, 255 );	///<	�v���C���[1�̘g�`��
	}
	
	//	�퓬�n���O
	if( !m_gameLog.m_logStream.empty() )
	{
		logValue = m_gameLog.m_logStream.size();
		long tempX = 0, tempY = 0;
		unsigned int tempW = 0, tempH = 0;
		std::string* pStr;
		LPCSTR lpTempStr;
		std::list<LogStream*>::const_iterator itEnd = m_gameLog.m_logStream.end();
		for( std::list<LogStream*>::iterator it = m_gameLog.m_logStream.begin();
			it != itEnd; ++it)
		{
			(*it)->GetPosition( tempX, tempY );
			(*it)->GetSize( tempW, tempH );
			pStr = (*it)->GetStringPtr();
			lpTempStr = const_cast<char *>(pStr->c_str());
			if(pDxFont->DrawA( tempX, tempY, static_cast<unsigned long>(_LOG_FONT_WIDTH_), 
							tempH, lpTempStr, (*it)->GetColor(), (*it)->GetFormat() ))
			{

			}
		}
	}
	//	�o�ߎ��ԃ��O
	if( !m_gameElapsed.m_logStream.empty() )
	{
		logValue = m_gameElapsed.m_logStream.size();
		long tempX = 0, tempY = 0;
		unsigned int tempW = 0, tempH = 0;
		std::string* pStr;
		LPCSTR lpTempStr;
		std::list<LogStream*>::const_iterator itEnd = m_gameElapsed.m_logStream.end();
		for( std::list<LogStream*>::iterator it = m_gameElapsed.m_logStream.begin();
			it != itEnd; ++it)
		{
			(*it)->GetPosition( tempX, tempY );
			(*it)->GetSize( tempW, tempH );
			pStr = (*it)->GetStringPtr();
			lpTempStr = const_cast<char *>(pStr->c_str());
			if(pDxFont->DrawA( tempX, tempY, tempW, tempH, lpTempStr, (*it)->GetColor(), (*it)->GetFormat() ))
			{

			}
		}
	}
	//	�ʐM�҂���
	if( GetConnectFlag() )
	{
		//	�ʐM�����O
		if( !m_gameConnectState.m_logStream.empty() )
		{
			logValue = m_gameConnectState.m_logStream.size();
			long tempX = 0, tempY = 0;
			unsigned int tempW = 0, tempH = 0;
			std::string* pStr;
			LPCSTR lpTempStr;
			std::list<LogStream*>::const_iterator itEnd = m_gameConnectState.m_logStream.end();
			for( std::list<LogStream*>::iterator it = m_gameConnectState.m_logStream.begin();
				it != itEnd; ++it)
			{
				(*it)->GetPosition( tempX, tempY );
				(*it)->GetSize( tempW, tempH );
				pStr = (*it)->GetStringPtr();
				lpTempStr = const_cast<char *>(pStr->c_str());
				if(pDxFont->DrawA( tempX, tempY, tempW, tempH, lpTempStr, (*it)->GetColor(), (*it)->GetFormat() ))
				{

				}
			}
		}
	}
	
}
