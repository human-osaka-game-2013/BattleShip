/**
*@file	StageDefineList.h
*@author	�T�c
*/
#ifndef _STAGEDEFINELIST_H_
#define _STAGEDEFINELIST_H_

#include "Window.h"

#define _STAGE_COLUMN_MAX_ 10	///<	�X�e�[�W�̍s��
#define _STAGE_LINE_MAX_	10	///<	�X�e�[�W�̗�

#define _BLOCK_WIDTH_SIZE_	WIDTH/_BLOCK_WIDTH_MAX_
#define _BLOCK_HEIGHT_SIZE_	HEIGHT/_BLOCK_HEIGHT_MAX_

#define _BLOCK_WIDTH_MAX_	(float)23	///<�Ֆʂ̉����̍ő�u���b�N��
#define _BLOCK_HEIGHT_MAX_	(float)16	///<�Ֆʂ̏c���̍ő�u���b�N��
#define _STAGE_HEIGHT_MAX_	(float)11	///<�X�e�[�W�����̏c���̍ő�u���b�N��
#define _STAGE_WIDTH_MAX_ _STAGE_HEIGHT_MAX_

#define _BOARD_OF_SHIPDATA_LINE_P1_	(float)8	///<����̏ڍ׃f�[�^�̕\����ʒu�i�v���C���[1�j
#define _BOARD_OF_SHIPDATA_LINE_P2_ (float)14	///<����̏ڍ׃f�[�^�̕\����ʒu�i�v���C���[2�j
#define _BOARD_OF_SHIPDATA_COLUMN_	(float)_STAGE_HEIGHT_MAX_	///<����̏ڍ׃f�[�^�̕\���s�ʒu

#endif