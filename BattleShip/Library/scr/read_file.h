

class CReadFile
{
private:


public:
	//	�t�@�C���ǂݍ��݊֐�
	//	�J���Ȃ��t�@�C���������false��Ԃ��A���߂�ꂽ�t�@�C����S�ēǂݍ��ނ�true��Ԃ�
	bool ReadFile();
	
	//	�u���b�N�̎�ނ�������n��
	//	������1�F�Z�b�g�ԍ� 2�F���(eTYPE)������(eDirection)������ 3�F�s��(STAGE_WIDTH), 4�F��(STAGE_HEIGHT)
	int	PassStageBlock( int iSetNum, int iInfoType, int iWidth, int iHeight );
	
	//	�u���b�N�̎�ނ�������n��
	//	������1�F�Z�b�g�ԍ� 2�F���(eTYPE)������(eDirection)������ 3�F�s��(STAGE_WIDTH), 4�F��(STAGE_HEIGHT)
	int	PassAddBlock( int iSetNum, int iInfoType, int iWidth, int iHeight );

};