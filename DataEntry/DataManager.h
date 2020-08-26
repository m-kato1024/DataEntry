#pragma once
#include <stdbool.h>

//--------------------------------------------------------------------
//define��`
//--------------------------------------------------------------------
//�f�[�^�o�^�̍ő匏��
#define DATA_MAX_COUNT (10)
//���O�A�ǂ݉����̍ő�o�C�g��
#define DATA_FIELD_MAX_LENGTH (40)

//--------------------------------------------------------------------
//�^��`
//--------------------------------------------------------------------
typedef struct _user{
	int number;
	char name[DATA_FIELD_MAX_LENGTH];
	char reading[DATA_FIELD_MAX_LENGTH];
}User;

//--------------------------------------------------------------------
// �O�����J�֐��錾
//--------------------------------------------------------------------
bool DMLoad(const char*);
bool DMAddNew(User*);
void DMDelete(int);
int DMSearch(char*, User*);
bool DMSave(const char*);
int DMGetUserCount(void);

