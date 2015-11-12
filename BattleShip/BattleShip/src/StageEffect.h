/**
*@file	StageEffect.h
*@author	�T�c
*/

#ifndef _STAGEEFFECT_H_
#define _STAGEEFFECT_H_

#include "GameState.h"

#define _END_COUNT_OF_EFFECT_	60*10

class StageEffect : public GameState
{
public:
	enum _STAGE_EFFECT_TIME_
	{
		TIME_END_ACTION_EFFECT =20,

		TIME_CHANGE_EFFECT = 10+TIME_END_ACTION_EFFECT,

		TIME_END_RUSULT_EFFECT = 20+TIME_CHANGE_EFFECT,
	};

private:
	_SELECT_NUM_ m_selectType;	///< �I�������s���̎��
	_SELECT_NUM_ m_enemyType;	///< ����̑I�������s��
	int m_actionShipPosColumn;	///< �s�����鎩��̍s���W
	int m_actionShipPosLine;	///< �s�����鎩��̗���W
	std::vector<BoardOfFrame> m_playerSelect;///< �������G�ɑ΂��Ďw�肵���}�X�̃R�s�[�p
	std::vector<BoardOfFrame> m_enemySelect; ///< �G�������ɑ΂��Ďw�肵���}�X�̃R�s�[�p
	BoardOfFrame m_myShipBlock;

public:
	/**
	*@brief	�R���X�g���N�^
	*@param	_type	���ݑI�����Ă���͂̎��
	*/
	StageEffect( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ): GameState( _type, _pGameLog ){
		
	}

	~StageEffect()
	{
		m_playerSelect.clear();
		m_enemySelect.clear();
	};

	/**
	*@brief	�퓬�G�t�F�N�g�ł̏�����
	*/
	bool Init();

	/**
	*@brief	�퓬�G�t�F�N�g�ł̃T�u���[�`������
	*/
	int Control();
	
	/**
	*@brief	�퓬�G�t�F�N�g�ł̕`��
	*/
	void Draw();
	
	/**
	*@brief	�퓬�G�t�F�N�g�ł̒ʐM�ҋ@����
	*/
	bool ComStandby();

	/**
	*@brief	�I�������s���̎�ނ��X�V
	*@details	Selection�X�e�[�g����StateManager���s���̑I������������Ă���̂ŁA
				StageEffect�X�e�[�g���ǂ̍s���̃G�t�F�N�g������΂��������f���邽�߂ɁA�K�v���ƍl���܂����B
	*/
	void SetSelectionType( int _selectType )
	{ 
		m_selectType = static_cast<_SELECT_NUM_>(_selectType); 
	}

private:
	/**
	@brief	���˃G�t�F�N�g����
	*/
	bool FireEffect();

	/**
	*@brief	���G�J�n�G�t�F�N�g����
	*/
	bool SearchStratEffect();

	/**
	*@brief	���e�G�t�F�N�g����
	*@param[in]	_playerIndex	�ǂ���̃v���C���[�����G������̂��𔻒f���邽��
	*/
	bool HitEffect( const int _playerID );

	/**
	*@brief	���G���ʃG�t�F�N�g����
	*@param[in]	_playerID	�ǂ���̃v���C���[�����G������̂��𔻒f���邽��
	*/
	bool SearchResultEffect( const int _playerID );

private:

	/**
	*@brief	�X�e�[�W�̑I���󋵂̃`�F�b�N
	*/
	void CheckSelectOfStage();

	/**
	*@brief	����̍��W�`�F�b�N
	*/
	void CheckOfMyShipPos();

private:
	/**
	*@brief	�\�i�[�G�t�F�N�g
	*/
	void SonarEffect();

};

#endif