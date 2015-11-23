/**
*@file	StageEffect.h
*@author	�T�c
*/

#ifndef _STAGEEFFECT_H_
#define _STAGEEFFECT_H_

#include "GameState.h"

#define _MOVE_SPEED_RECON_	35.f
#define _DIVISON_OF_EFFECT_TIME_	1.5


class StageEffect : public GameState
{
public:
	/**
	*@brief	�X�e�[�W��̉��o�̎���
	*/
	enum _STAGE_EFFECT_TIME_
	{
		TIME_END_ACTION_EFFECT = 30,

		TIME_CHANGE_EFFECT = 10+TIME_END_ACTION_EFFECT,

		TIME_END_RUSULT_EFFECT = 30+TIME_CHANGE_EFFECT,
	};

private:
	_SELECT_NUM_ m_plyaerSelectType;	///< �I�������s���̎��
	_SELECT_NUM_ m_enemySelectType;	///< ����̑I�������s��
	
	std::vector<BoardOfFrame> m_playerSelect;///< �������G�ɑ΂��Ďw�肵���}�X�̃R�s�[�p
	std::vector<BoardOfFrame> m_enemySelect; ///< �G�������ɑ΂��Ďw�肵���}�X�̃R�s�[�p
	
	int m_actionShipPosColumn;	///< �s�����鎩��̍s���W
	int m_actionShipPosLine;	///< �s�����鎩��̗���W
	
	float m_plTargetPointX;	///< ���g�I���������WX
	float m_plTargetPointY;	///< ���g�I���������WY
	D3DXVECTOR2	m_plTargetVector;	///< ����̍��W����^�[�Q�b�g�ւ̃x�N�g���i�q��@�̈ړ��ȂǂɎg���j
	
	float m_enTargetPointX;	///< �G���I���������WX
	float m_enTargetPointY;	///< �G���I���������WY
	D3DXVECTOR2	m_enTargetVector;	///< �G���q��@���΂��ۂ̃x�N�g��
	BoardOfFrame m_myShipBlock;	///< ����̒��S�u���b�N
	
	/*bool m_plSoundFlag;	///< SE���t���O�i�v���C���[�j
	bool m_enSoundFlag;	///< SE���t���O�i�G�j
*/
public:
	/**
	*@brief	�R���X�g���N�^
	*@param	_type	���ݑI�����Ă���͂̎��
	*/
	StageEffect( ShipObject::_SHIP_TYPE_NUM_& _type, GameLog* _pGameLog ): GameState( _type, _pGameLog ){
		m_plyaerSelectType = _SELECT_NONE_;
		m_enemySelectType = _SELECT_NONE_;
		m_plTargetPointX = 0.f;
		m_plTargetPointY = 0.f;
		m_enTargetPointX = 0.f;
		m_enTargetPointY = 0.f;
		m_actionShipPosColumn	= -1;
		m_actionShipPosLine		= -1;
		/*m_plSoundFlag = false;
		m_enSoundFlag = false;*/
	}
	/**
	*@brief	�f�X�g���N�^
	*/
	~StageEffect()
	{
		m_playerSelect.clear();
		m_enemySelect.clear();
	};

//	�������n
private:

	/**
	*@brief	�X�e�[�W�̑I���󋵂̃`�F�b�N
	*/
	void CheckSelectOfStage();

	/**
	*@brief	����̍��W�`�F�b�N
	*/
	void CheckOfMyShipPos();

//	��{����
public:
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

//	�O���擾�n
public:
	/**
	*@brief	�I�������s���̎�ނ��X�V
	*@details	Selection�X�e�[�g����StateManager���s���̑I������������Ă���̂ŁA
				StageEffect�X�e�[�g���ǂ̍s���̃G�t�F�N�g������΂��������f���邽�߂ɁA�K�v���ƍl���܂����B
	*/
	void SetSelectionType( int _selectType )
	{ 
		m_plyaerSelectType = static_cast<_SELECT_NUM_>(_selectType); 
	}

//	�G�t�F�N�g�̃T�E���h�̏���
private:
	void EffectSoundControl();

//	�G�t�F�N�g�̕`�敪�򏈗�
private:
	/**
	*@brief	�U���J�n�G�t�F�N�g����
	*/
	void AttackStartControl();

	/**
	*@brief	���G�J�n�G�t�F�N�g����
	*/
	void SearchStartControl();

	/**
	*@brief	���e�G�t�F�N�g����
	*@param[in]	_playerIndex	�ǂ���̃v���C���[�����G������̂��𔻒f���邽��
	*/
	void HitEffectControl();

	/**
	*@brief	���G���ʃG�t�F�N�g����
	*@param[in]	_playerID	�ǂ���̃v���C���[�����G������̂��𔻒f���邽��
	*/
	void SearchResultControl();


//	�G�t�F�N�g�ʕ`��
private:
	/**
	@brief	���˃G�t�F�N�g����
	*/
	void FireEffect( BoardOfFrame& _block );

	/**
	*@brief	�\�i�[�G�t�F�N�g
	*/
	void SonarEffect( BoardOfFrame& _block );

	/**
	*@brief	�q��@�G�t�F�N�g
	*@details _appearanceInvisibility	����͑ΐ푊�肪�퓬�@�Ȃǂ��΂����ɏ��X�ɃA���t�@�l��������B
										�`����W�Ȃǂ�����Flag��true�̎��͓G�̃f�[�^�im_enTargetVector�Ȃǁj��ƂȂ�B
	*@param[in] _block	�o���ʒu�����߂�u���b�N
	*@param[in] _aircraftType	0�F�U���@�A1�F���G�@
	*@param[in]	_appearanceInvisibility	�o���ʒu�������Ȃ�������t���O
	*/
	void AircraftEffect( BoardOfFrame& _block, int _aircraftType, bool _appearanceInvisibility = false );

	/**
	*@brief	�����G�t�F�N�g
	*/
	void ExplosionEffect( BoardOfFrame& _block );

//	���̑�
private:
	/**
	*@brief	2�����x�N�g���̐��K��
	*/
	int Vec2Normalize( D3DXVECTOR2& _vec2 );

};

#endif