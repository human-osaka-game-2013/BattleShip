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

#define _FIRST_SETATE_ StateManager::STATE_SET_SHIP	///<	�ŏ��̃X�e�[�g�p�^�[��
#define _POS_PLAYER1FRAME_	0.f, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)						///<�v���C���[1���̘g�̕\�����W
#define _POS_PLAYER2FRAME_	_BLOCK_WIDTH_SIZE_*12, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_)	///<�v���C���[2���̘g�̕\�����W
#define _SIZE_PLAYERFRAME_	_BLOCK_WIDTH_SIZE_*11, _BLOCK_HEIGHT_SIZE_*5	///<�v���C���[���̘g�T�C�Y

//	�R���X�g���N�^ 
StateManager::StateManager( Player* const _pPlayer1, Player* const _pPlayer2, 
							StageObject* const _pStageObject, const int _playerID) 
	: m_pPlayer1(_pPlayer1), m_pPlayer2(_pPlayer2), m_pStageObject( _pStageObject), m_playerID(_playerID)
{
	m_connectFlag = false;
	m_resultPlayer	= 0;
	m_resultEnemy	= 0;
	m_resultBattle	= 0;
	m_selectType	= static_cast<int>(GameState::_SELECT_NONE_);
}

//	�X�e�[�g�̏�����
void StateManager::StateInit()
{
	m_beforeState	= STATE_NONE;		///<	�������Ȃ̂ňȑO�̃X�e�[�g�͂������������ׁASTATE_NONE�ɁB
	m_currentState	= _FIRST_SETATE_;///<	�X�e�[�g�̏������Ȃ̂ōŏ��ɓǂݍ��ނł��낤�p�^�[���̒萔������
	m_currentShip	= ShipObject::TYPE_AIRCARRIER;	///<	�����I����͋��Ȃ̂Ő��l�����ɃZ�b�g�B
	ChangeState(m_currentState);	///<	�܂��X�e�[�g�|�C���g�ɂ͉��������Ă��Ȃ��̂ŏ����������˂�
	m_StageFrame.Init( 0.f, -2.f, WIDTH, HEIGHT*(_STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_));
	///<��ʏ㕔����P�P�}�X���ڂ܂ŔՖʃt���[��������̂�11/16�ƂȂ�B
	m_PlayerFrame[0].Init( _POS_PLAYER1FRAME_, _SIZE_PLAYERFRAME_ );
	m_PlayerFrame[1].Init( _POS_PLAYER2FRAME_, _SIZE_PLAYERFRAME_ );

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

	if( stateResult == 1 )	///<	�X�e�[�g�̃��[�`�������̌��ʃV�[�����ς��K�v�������
	{
		switch( m_currentState )	///<	�ύX����X�e�[�g�͏��Ԃ�������x���܂��Ă���̂ŕ���
		{
		case STATE_SET_SHIP:
			ChangeState(STATE_SELECTION);

			break;
		case STATE_SELECTION:
			ChangeState(STATE_RESULT);

			break;
		case STATE_RESULT:
			ChangeState(STATE_STAGE_EFFECT);

			break;
		case STATE_STAGE_EFFECT:
			ChangeState(STATE_SELECTION);
			
			break;
		}
	}
	else if( stateResult == -1 )
	{
		MessageBoxA(0,"�퓬���I�����܂���","�퓬����",MB_OK);
	}

	return stateResult;
}

int StateManager::CheckState()
{
	
	int beforeShip = static_cast<int>(m_currentShip);
	int checkResult = 0;
	int stageResult = 0;

	m_pGameState->SetConnectFlag( m_connectFlag );	//	���t���[���ʐM�̃t���O���X�V
	stageResult = m_pGameState->Control();	///<�@�X�e�[�g���Ƃ̏����Ɉڍs
	SetConnectFlag( m_pGameState->GetConnectFlag() );	//	�X�e�[�g���ł̃t���O�ύX�𔽉f������

	switch( m_currentState )	///<�@�V�[�����ɃX�e�[�g�̌��ʂւ̑Ώ����ς��̂ŕ���
	{
	case STATE_SET_SHIP:
		if( m_currentShip >= ShipObject::TYPE_MAX && !m_connectFlag )	///<�@�S�Ă̋�Z�b�g���ꂽ
			checkResult = 1;
		break;
	case STATE_SELECTION:
		if( stageResult == 1 && !m_connectFlag ){	///<�@���ʂ�1���A�ʐM���������Ă����ꍇ
			Selection* pSelection = dynamic_cast<Selection*>(m_pGameState);	///<Selection�̊֐��ɃA�N�Z�X����K�v������̂ŁA�_�E���L���X�g����B
			m_selectType = pSelection->GetSelectionType();
		
			checkResult = 1;	///<�@�I�����ʂɈڂ�
		}
		break;
	case STATE_RESULT:
		if( stageResult != Result::TYPE_VICTORY || stageResult != Result::TYPE_DEFEAT ){	///<�@���ʂƑI�𒆂̋�Ⴄ���s���I�������Ȃ̂�
			Result* pResult = dynamic_cast<Result*>(m_pGameState);	///<Result�̊֐��ɃA�N�Z�X����K�v������̂ŁA�_�E���L���X�g����B
			pResult->GetResultPlayerAndEnemy( m_resultPlayer, m_resultEnemy );
			pResult->GetResultOfBattle( m_resultBattle );

			checkResult = 1;
		}
		else	//����or�s�kor�퓬�I��
		{
			checkResult = -1;
		}

		break;
	case STATE_STAGE_EFFECT:
		/**
		*@todo	�G�t�F�N�g�������ׂ̈����͉�����
		*/
		if( stageResult == 1 ){	///<�@���ʂ�1(�X�e�[�W�̉��o������)�̏ꍇ
			// Selection�X�e�[�g�Ɉڂ�O�Ɍ��݂̃^�[�����I�������̂Ŏ��̋���w��
			if( m_currentShip < ShipObject::TYPE_SUBMARINE){

				m_currentShip = static_cast< ShipObject::_SHIP_TYPE_NUM_ >( beforeShip+1 );
			}else{
				m_currentShip = ShipObject::TYPE_AIRCARRIER;
			}

			checkResult = 1;
		}
		break;
	}
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
		SetShip* pSetShip;
		Selection* pSelection;
		Result* pResult;
		StageEffect* pStageEffect;

		switch( m_beforeState )
		{
		case STATE_SET_SHIP:
			pSetShip = dynamic_cast<SetShip*>(m_pGameState);
			CLASS_DELETE(pSetShip); 
			
			break;
		case STATE_SELECTION:
			pSelection = dynamic_cast<Selection*>(m_pGameState);
			CLASS_DELETE(pSelection); 
			
			break;
		case STATE_RESULT:
			pResult = dynamic_cast<Result*>(m_pGameState);
			CLASS_DELETE(pResult); 
			
			break;
		case STATE_STAGE_EFFECT:
			pStageEffect = dynamic_cast<StageEffect*>(m_pGameState);
			CLASS_DELETE(pStageEffect); 
			
			break;
		}
	}
	//	�e�X�e�[�g�ʂɃX�e�[�g����
	switch( _stateType )
	{
	case STATE_SET_SHIP:
		m_pGameState = new SetShip( m_currentShip );

		break;
	case STATE_SELECTION:
		m_pGameState = new Selection( m_currentShip );

		break;
	case STATE_RESULT:
		m_pGameState = new Result( m_currentShip );

		break;
	case STATE_STAGE_EFFECT:
		m_pGameState = new StageEffect( m_currentShip );

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
	m_pGameState->SetPlayerID( m_playerID );
	m_pGameState->Init();	///<�Ō�ɃX�e�[�g���̏��������s���i�����͂��̃N���X�������Ă��錻�݂̑I����j

	return true;
}

//	�X�e�[�g�̊�{�`��
void StateManager::StateDraw( CDrawManager* _drawManager)
{
	float tempX, tempY;
	
	//	�Ֆʘg�\���i���j
	m_StageFrame.GetPosition( &tempX, &tempY );
	_drawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		0.f, 0.f, 
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);	///<	�Ֆʂ̍����̕`��

	//	�Ֆʘg�\���i�E�j
	_drawManager->VertexDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*12, tempY, 
		m_StageFrame.GetWidth()*(_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_),  m_StageFrame.GetHeight(),
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 0.f, 
		1.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_,
		180, 220, 220, 220);	///<	�Ֆʂ̉E���̕`��

	//	�Ֆʘg�\���i���j
	_drawManager->VertexDraw( _TEX_STAGEMAP_, tempX+_BLOCK_WIDTH_SIZE_*_STAGE_WIDTH_MAX_, tempY, 
		_BLOCK_WIDTH_SIZE_, HEIGHT,
		_STAGE_WIDTH_MAX_/_BLOCK_WIDTH_MAX_, 0.f,
		(_STAGE_WIDTH_MAX_+1)/_BLOCK_WIDTH_MAX_, 1.f,
		180, 220, 220, 220);	///<	�Ֆʂ̐^�񒆂̕`��

	//	�v���C���[1�g�\��
	m_PlayerFrame[0].GetPosition( &tempX, &tempY );
	_drawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_PlayerFrame[0].GetWidth(),  m_PlayerFrame[0].GetHeight(),
		0.f, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
		11/_BLOCK_WIDTH_MAX_, 1.f,
		180, 255, 100, 100);	///<	�v���C���[1�̘g�`��
	//	�v���C���[2�g�\��
	m_PlayerFrame[1].GetPosition( &tempX, &tempY );
	_drawManager->VertexDraw( _TEX_STAGEMAP_, tempX, tempY, 
		m_PlayerFrame[1].GetWidth(),  m_PlayerFrame[1].GetHeight(),
		12/_BLOCK_WIDTH_MAX_, _STAGE_HEIGHT_MAX_/_BLOCK_HEIGHT_MAX_, 
		1.f, 1.f,
		180, 100, 100, 255);	///<	�v���C���[2�̘g�`��

	//	�X�e�[�W�}�X�ڕ\��
	//	�v���C���[��
	for( int ip=0; ip<_PLAYER_NUM_; ip++ )
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
			if( ip == m_playerID-1 )	///<���͎����̃v���C���[�̋���\�����Ȃ�
			{
				Player* tempPlayer = m_playerID%_PLAYER_NUM_ ? m_pPlayer1:m_pPlayer2;
					ShipObject* tempShip = tempPlayer->GetShip( (ShipObject::_SHIP_TYPE_NUM_)iShip );
					
				if( !tempShip->GetDeadFlag() )
				{
					//	�Ֆʏ�ɒu����Ă��鎩���̋��`��
					m_pDrawManager->VertexTransform( iShip + _TEX_AIRCARRIER_, tempShip->m_vertex, 
						tempShip->GetPositionX(), tempShip->GetPositionY(), 1.f, 1.f, tempShip->GetDirection()*90.f );
					
					if( ip == 0 ){	//	�v���C���[1�̏ꍇ
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
			//else if(  )

		}
		//	�s
		for( int ic=0; ic<_STAGE_COLUMN_MAX_; ic++ )
		{	
			//	��
			for( int il=0; il<_STAGE_LINE_MAX_; il++ )
			{
				m_pStageObject->m_stageBlock[ip][ic][il].GetPosition( &tempX, &tempY );
				
				int tempA = 0, tempR = 200, tempG = 200, tempB = 200;
				int tempArrayData = m_pStageObject->m_stageArray[ip][ic][il];
			
				if( StageObject::ConditionOfData(tempArrayData) != StageObject::_CONDITION_NONE_ )	///<��̂���ꏊ�͓h��Ԃ�
				{
					
					//	������Ԍ��`�F�b�N
					switch( StageObject::ConditionOfData(tempArrayData) )
					{
					case StageObject::_CONDITION_NONE_:
					case StageObject::_CONDITION_NOMAL_:	
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
							tempA = 100, tempR = 0, tempG = 255, tempB = 0;
							break;
						case StageObject::_SEARCH_ALL_:
							tempA = 255, tempR = 0, tempG = 255, tempB = 0;
							break;
						case StageObject::_ACTION_NOMAL_:
							tempA = 100, tempR = 0, tempG = 0, tempB = 255;
							break;
						case StageObject::_ACTION_ALL_:
							tempA = 255, tempR = 0, tempG = 0, tempB = 255;
							break;
						}

						break;
					
					case StageObject::_CONDITION_DAMAGE_:
						tempA = 255, tempR = 255, tempG = 100, tempB = 100;
						break;

					}
					
				_drawManager->VertexDraw( _TEX_BLOCK_, tempX, tempY, 
					m_pStageObject->m_stageBlock[ip][ic][il].GetWidth(), 
					m_pStageObject->m_stageBlock[ip][ic][il].GetHeight(),
					0.f, 0.f, 
					1.f, 1.f,
					tempA, tempR, tempG, tempB);	///<	�}�X�̕`��
				}
				_drawManager->VertexDraw( _TEX_BLOCKFRAME_, tempX, tempY, 
					m_pStageObject->m_stageBlock[ip][ic][il].GetWidth(), 
					m_pStageObject->m_stageBlock[ip][ic][il].GetHeight(),
					0.f, 0.f, 
					1.f, 1.f,
					100, 200, 200, 200);	///<	�}�X�̕`��
			}
		}
		
	}
	//	�X�e�[�g�ʂ̕`��
	m_pGameState->Draw();
}


//	�X�e�[�g�I�u�W�F�N�g�̏���
void StateManager::StateDelete()
{
	SetShip* pSetShip;
	Selection* pSelection;
	Result* pResult;
	StageEffect* pStageEffect;

	switch( m_currentState )
	{
		case STATE_SET_SHIP:
			pSetShip = dynamic_cast<SetShip*>(m_pGameState);
			CLASS_DELETE(pSetShip); 
			
			break;
		case STATE_SELECTION:
			pSelection = dynamic_cast<Selection*>(m_pGameState);
			CLASS_DELETE(pSelection); 
			
			break;
		case STATE_RESULT:
			pResult = dynamic_cast<Result*>(m_pGameState);
			CLASS_DELETE(pResult); 
			
			break;
		case STATE_STAGE_EFFECT:
			pStageEffect = dynamic_cast<StageEffect*>(m_pGameState);
			CLASS_DELETE(pStageEffect); 
			
	}
}

void StateManager::Free()
{
	StateDelete();
}

