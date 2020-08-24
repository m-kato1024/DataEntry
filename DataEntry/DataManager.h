#pragma once
#include <stdbool.h>

//--------------------------------------------------------------------
//define��`
//--------------------------------------------------------------------
//�f�[�^�o�^�̍ő匏��
#define DATA_MAX_COUNT (10)
//���O�̍ő�o�C�g��
#define DATA_MAX_LENGTH (40)
//�t�@�C��1�s�̍ő�T�C�Y�@10���ȏ�i�[����ꍇ�͐擪�̂Q�̐����ɒ��ӂ���
#define READ_LINE_BUFFER_SIZE (3+1+DATA_MAX_LENGTH+1+DATA_MAX_LENGTH+1)
#define END_OF_TEST (0x03)
//--------------------------------------------------------------------
//�^��`
//--------------------------------------------------------------------
struct data {
	int number;
	char name[DATA_MAX_LENGTH];
	char yomi[DATA_MAX_LENGTH];
};

//--------------------------------------------------------------------
//�֐��錾
//--------------------------------------------------------------------
bool DMInitialization(char* path);
bool DMAddNew(int input_number, char* input_name, char* input_yomi);
bool DMDelete(int input_number);
int DMListFetch(struct data result[]);
int DMSearch(char* input_yomi, struct data search_result[]);
bool DMTerminate(char* path);
int DMGetUserCount();