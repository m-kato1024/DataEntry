
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 
#include "UserInterface.h"

#define IS_YES(a)				(_wordCheck(a, IS_Y_WORD_TABLE))
#define IS_GOTO_MAIN_MENU(a)	(_wordCheck(a, IS_M_WORD_TABLE))

// �萔
static const char* IS_Y_WORD_TABLE[] = { "y", "Y", "��","�x", NULL };
static const char* IS_M_WORD_TABLE[] = { "m", "M", "��","�l", NULL };

// �����֐��v���g�^�C�v�錾
static bool _wordCheck(char*, const char**);
static bool _deleteUi(User*, int);
static User* _findUser(int, User*, int);

/**
*@brief �V�K�o�^����
*@note resistrationsCount���͈͊O�̎��̓G���[�A
*answer��"Y"�܂���"y"�̎��A�o�^�������ĂԁB
*/
void UIAddnew() {
	User newData = { 0 };
	char answer[3] = { 0 };
	
	//������MAX�̏ꍇ�͐V�K�o�^�s��
	if (DMGetUserCount() == DATA_MAX_COUNT) {
		printf("%s\n\n", MSG_ADDNEW_OVER);
		return;
	}

	//�ԍ�����
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NUMBER, ARROW_TEXT);
	do {		
		UIKeyBufferClear();
		scanf("%d", &newData.number);
		if (newData.number < 1 || newData.number > DATA_MAX_COUNT ) {
			//�͈͊O�̔ԍ��͓��͂����Ȃ�
			printf("%s\n\n", MSG_ADDNEW_WORNIG);
			newData.number = 0;
		}
	} while (!newData.number);

	//���O�̓���
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME1, ARROW_TEXT);
	UIKeyBufferClear();
	scanf("%39s", newData.name);

	//���~�K�i�̓���
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME2, ARROW_TEXT);
	UIKeyBufferClear();
	scanf("%39s", newData.reading);

	//�o�^�m�F
	printf("%s%d %s(%s)\n%s\n%s", MSG_ADDNEW_CONFIRMATION1, newData.number, newData.name, newData.reading, MSG_ADDNEW_CONFIRMATION2, ARROW_TEXT);
	UIKeyBufferClear();
	scanf("%2s", answer);

	if (IS_YES(answer)) {
		if (DMAddNew(&newData) == false) {
			printf("\n%s\n\n", MSG_ADDNEW_ERROR);
		}
	}
	
}

/**
*@brief �ꗗ�\���@�\
*@note �o�^����Ă�f�[�^�̈ꗗ��\������B
*	   �o�^����Ă��Ȃ�������A�폜�̍ۂɖ��֌W��
*	   �ԍ�����͂���ƃG���[���b�Z�[�W���\�������B
*/
void UIDisplayList(char* searchWord) {
	int count = 0;
	User list[DATA_MAX_COUNT] = { 0 };

	do{
		count = DMSearch(searchWord, list);
		if (count > 0) {
			printf("-----------------------\n");
			for (int i = 0; i < count; i++) {
				printf("%d. %s %s\n", list[i].number, list[i].name, list[i].reading);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			if (!_deleteUi(list, count)) {
				break;
			}
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
		}
	} while (count > 0);

	printf("\n");
}

/**
*@brief �ǂ݉��������@�\
*@note ���������ꍇ�ǂ݉����̈ꕔ�ł����͂����
*	   ����ɊY�����镶�����\�������B
*/
void UISearch() {
	char word[DATA_FIELD_MAX_LENGTH];

	if (DMGetUserCount() == 0) {
		printf("%s\n\n", MSG_DISPCAT_WORNIG);
		return;
	}

	printf("%s\n", MSG_UISEARCH_WORNIG);
	UIKeyBufferClear();
	scanf("%39s", word);
	UIDisplayList(word);	
}

/**
*@brief �L�[�o�b�t�@�̓N���A����
*@note fflush()�ł̓N���A�ł��Ȃ����߁A�Ǝ��ŋ�ɂȂ�܂œǂݔ�΂����̂Ƃ���
*/
void UIKeyBufferClear(void)
{
	int buffer;
	while ((buffer = getc(stdin)) != EOF && buffer != '\n');
}

/**
*@brief ���[�U�[���݃`�F�b�N
*@param number �ԍ�
*@param list �ꗗ�f�[�^
*@param listCount �ꗗ�f�[�^�̌���
*@retval NULL�ȊO  ���݂���
*@retval NULL ���݂��Ȃ�
*@note ����list�̒���number�ɊY�����郆�[�U�[�����݂��邩���ׂ�
*/
static User* _findUser(int number, User* list, int listCount)
{
	for (int index = 0; index < listCount; index++) {
		if (list[index].number == number) {
			return &list[index];
		}
	}
	return NULL;
}

/**
*@brief �폜�@�\�y�у��C�����j���[�J��
*@param data �ꗗ�f�[�^
*@param listCount �ꗗ�f�[�^�̌���
*@retval true  �ꗗ�\���p��
*@retval false ���C�����j���[�ɖ߂�
*@note 
*/
static bool _deleteUi(User* list, int listCount)
{
	char inputKey[3];
	int deleteNumber;
	
	UIKeyBufferClear();
	scanf("%2s", inputKey);
	if (IS_GOTO_MAIN_MENU(inputKey)) {
		printf("\n");
		return false;
	}

	deleteNumber = atoi(inputKey);
	User* user = _findUser(deleteNumber, list, listCount);
	if (user == NULL) {
		printf("%s\n\n", MSG_UIDELETE_NOT_FOUND);
		return true;
	}

	printf("�u%d. %s�v%s\n%s", user->number, user->name, MSG_UIDELETE_CHECK1, ARROW_TEXT);
	UIKeyBufferClear();
	scanf("%2s", inputKey);
	if (IS_YES(inputKey)) {
		DMDelete(deleteNumber);
	}
	return true;
}

/**
*@brief ������`�F�b�N
*@param targetWord �`�F�b�N�Ώە�����
*@param checkTable ����������e�[�u��
*@retval true ������v
*@retval false ������v���Ă��Ȃ�
*@note	M�L�[�y��Y�L�[���������ꂽ���ۂ��𔻒肷�鏈���B
*		�������Ɏw�肷�镶����e�[�u���̕����ƈ�v�����ꍇ��true��Ԃ��B
*/
static bool _wordCheck(char* targetWord, const char** checkTable) {
	for (int index = 0; checkTable[index] != NULL; index++) {
		if (strcmp(targetWord, checkTable[index]) == 0) {
			return true;
		}
	}
	return false;
}
