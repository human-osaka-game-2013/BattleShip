/**
*@file	Proc.h
*@author	�T�c
*@brief	Proc�֐��n�̂܂Ƃ�
*/

//----------------------------------------------------------------
//	�v���g�^�C�v�錾
//----------------------------------------------------------------

/**
*@brief	�E�C���h�E����
*/
int CreateWindowProcess ( HINSTANCE, HWND* );

/**
*@brief	�E�C���h�E�v���V�[�W��
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);