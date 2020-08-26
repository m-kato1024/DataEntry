
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 
#include "UserInterface.h"

// �萔
static const char* IS_Y_WORD_TABLE[] = { "y", "Y", "��","�x", NULL };
static const char* IS_M_WORD_TABLE[] = { "m", "M", "��","�l", NULL };

// �����֐��v���g�^�C�v�錾
static bool _delete(struct data*, int);
static bool _isYes(char* );
static bool _isGotoMainMenu(char* );
static bool _existNumber(int, struct data*, int);

/**
*@brief �V�K�o�^����
*@note resistrationsCount���͈͊O�̎��̓G���[�A
*answer��"Y"�܂���"y"�̎��A�o�^�������ĂԁB
*/
void UIAddnew() {
	struct data newData = { 0 };
	char answer[3] = { 0 };
	
	//������MAX�̏ꍇ�͐V�K�o�^�s��
	if (DMGetUserCount() == DATA_MAX_COUNT) {
		printf("%s\n\n", MSG_ADDNEW_OVER);
		return;
	}

	//�ԍ�����
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NUMBER, ARROW_TEXT);
	do {		
		UIFflush();
		scanf("%d", &newData.number);
		if (newData.number < 1 || newData.number > DATA_MAX_COUNT ) {
			//�͈͊O�̔ԍ��͓��͂����Ȃ�
			printf("%s\n", MSG_ADDNEW_WORNIG);
			newData.number = 0;
		}
	} while (!newData.number);

	//���O�̓���
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME1, ARROW_TEXT);
	UIFflush();
	scanf("%39s", newData.name);

	//���~�K�i�̓���
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME2, ARROW_TEXT);
	UIFflush();
	scanf("%39s", newData.yomi);

	//�o�^�m�F
	printf("%s%d %s(%s)\n%s\n%s", MSG_ADDNEW_CONFIRMATION1, newData.number, newData.name, newData.yomi, MSG_ADDNEW_CONFIRMATION2, ARROW_TEXT);
	UIFflush();
	scanf("%2s", answer);

	if (_isYes(answer)) {
		if (DMAddNew(&newData) == false) {
			printf("\n%s\n\n", MSG_ADDNEW_ERROR);
		}
	}
	
}

/**
*@brief ������`�F�b�N
*@param targetWord �`�F�b�N�Ώە�����
*@param words ����������e�[�u��
*@retval true ������v
*@retval false ������v���Ă��Ȃ�
*@note	M�L�[�y��Y�L�[���������ꂽ���ۂ��𔻒肷�鏈���B
*		�������Ɏw�肷�镶����e�[�u���̕����ƈ�v�����ꍇ��true��Ԃ��B
*/
static bool _wordCheck(char* targetWord, const char** checkTable) {
	int index = 0;
	while (checkTable[index] != NULL) {
		if (strcmp(targetWord, checkTable[index]) == 0) {
			return true;
		}
		index++;
	}
	return false;
}

/**
*@brief Y�L�[��������
*@param input ���͂��ꂽ������
*@retval true Y�����͂��ꂽ
*@retval false Y�ȊO�����͂��ꂽ
*@note
*/
static bool _isYes(char* input) {
	return _wordCheck(input, IS_Y_WORD_TABLE);
}

/**
*@brief M�L�[��������
*@param input ���͂��ꂽ������
*@retval true M�����͂��ꂽ
*@retval false M�ȊO�����͂��ꂽ
*@note 
*/
static bool _isGotoMainMenu(char* input) {
	return _wordCheck(input, IS_M_WORD_TABLE);
}

/**
*@brief �ꗗ�\���@�\
*@note �o�^����Ă�f�[�^�̈ꗗ��\������B
*	   �o�^����Ă��Ȃ�������A�폜�̍ۂɖ��֌W��
*	   �ԍ�����͂���ƃG���[���b�Z�[�W���\�������B
*/
void UIDisplayList(char* searchWord) {
	int count = 0;
	struct data list[DATA_MAX_COUNT] = { 0 };

	while(1){
		count = DMSearch(searchWord, list);

		if (count > 0) {
			for (int i = 0; i < count; i++) {
				printf("%d. %s %s\n", list[i].number, list[i].name, list[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			if (!_delete(list, count)) {
				break;
			}
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
			break;
		}
	}
	printf("\n");
}

/**
*@brief �ǂ݉��������@�\
*@note ���������ꍇ�ǂ݉����̈ꕔ�ł����͂����
*	   ����ɊY�����镶�����\�������B
*/
void UISearch() {
	char word[DATA_MAX_LENGTH];

	if (DMGetUserCount() == 0) {
		printf("%s\n\n", MSG_DISPCAT_WORNIG);
		return;
	}

	printf("%s\n", MSG_UISEARCH_WORNIG);
	UIFflush();
	scanf("%39s", word);
	UIDisplayList(word);	
}

/**
*@brief �ԍ����݃`�F�b�N
*@param number �ԍ�
*@param list �ꗗ�f�[�^
*@param listCount �ꗗ�f�[�^�̌���
*@retval true  ���݂���
*@retval false ���݂��Ȃ�
*@note �������Ŏw�肳��ԍ�������list���ŗL���Ȕԍ��ł��邩�`�F�b�N����
*/
static bool _existNumber(int number, struct data* list, int listCount) 
{
	if (list == NULL) {
		return false;
	}

	for (int index = 0; index < listCount; index++) {
		if (list[index].number == number) {
			return true;
		}
	}
	return false;
}


/**
*@brief �폜�@�\�y�у��C�����j���[�J��
*@param data �ꗗ�f�[�^
*@retval true  �ꗗ�\���p��
*@retval false ���C�����j���[�ɖ߂�
*@note 
*/
static bool _delete(struct data* list, int listCount)
{
	char inputKey[3] = "";
	int deleteNumber;
	
	while (1) {
		UIFflush();
		scanf("%2s", inputKey);
		if (_isGotoMainMenu(inputKey)) {
			printf("\n");
			return false;
		}

		deleteNumber = atoi(inputKey);
		if (!_existNumber(deleteNumber, list, listCount)) {
			printf("%s\n", MSG_UIDELETE_NOT_FOUND);
			return true;
		}
		else {
			break;
		}
	}

	printf("�u%d. %s�v%s\n%s", deleteNumber, list[deleteNumber - 1].name, MSG_UIDELETE_CHECK1, ARROW_TEXT);
	UIFflush();
	scanf("%2s", inputKey);
	if (_isYes(inputKey)) {
		DMDelete(deleteNumber);
	}
	return true;
}
/**
*@brief stdin�̃L�[�o�b�t�@�̓N���A����
*@note fflush()�ł̓N���A�ł��Ȃ����߁A�Ǝ��ŋ�ɂȂ�܂œǂݔ�΂����̂Ƃ���
*/
void UIFflush(void)
{
	int buffer;
	while ((buffer = getc(stdin)) != EOF && buffer != '\n');
}
