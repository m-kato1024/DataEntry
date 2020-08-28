
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 
#include "UserInterface.h"


static char UIDelete(struct data* data);
char UICharCheck(char mode, char answer[3]);

/**
*@brief �V�K�o�^����
*@note resistrationsCount���͈͊O�̎��̓G���[�A
*answer��"Y"�܂���"y"�̎��A�o�^�������ĂԁB
*/
void UIAddnew() {
	int resistrationsCount = DMGetUserCount();

	int num = 0;
	char kanji[DATA_MAX_LENGTH];
	char kana[DATA_MAX_LENGTH];
	char answer[3] = { 0 };
	
	if (resistrationsCount <= DATA_MAX_COUNT) {
		do {
			printf("%s\n%s", MSG_ADDNEW_RESISTER_NUMBER, ARROW_TEXT);
			UIFflush();
			scanf("%d", &num);
			if (num < 1 || num > DATA_MAX_COUNT ) {
				printf("%s\n", MSG_ADDNEW_WORNING);
			}
		} while (num < 1 || num > DATA_MAX_COUNT);

		printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME1, ARROW_TEXT);
		UIFflush();
		scanf("%39s", kanji);

		printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME2, ARROW_TEXT);
		UIFflush();
		scanf("%39s", kana);

		printf("%s%d %s(%s)\n%s\n%s", MSG_ADDNEW_CONFIRMATION1, num, kanji, kana, MSG_ADDNEW_CONFIRMATION2, ARROW_TEXT);

		UIFflush();
		scanf("%3s", answer);
		if (UICharCheck('Y', answer) == true) {
			bool ret;
			ret = DMAddNew(num, kanji, kana);
			printf("\n");
			if (ret == false) {
				printf("%s\n\n", MSG_ADDNEW_ERROR);

			}
		}
	}
	else {
		printf("%s\n\n", MSG_ADDNEW_OVER);
	}
	UIClear();
}

/**
*@brief �ꗗ�\���@�\
*@note �o�^����Ă�f�[�^�̈ꗗ��\������B
*	   �o�^����Ă��Ȃ�������A�폜�̍ۂɖ��֌W��
*	   �ԍ�����͂���ƃG���[���b�Z�[�W���\�������B
*/
void UIDispCat() {
	int resistrationsCount = DMGetUserCount();
	char inputKey[3] = "a";
	struct data result[DATA_MAX_COUNT] = { 0 };

	while(1){
		resistrationsCount = DMListFetch(result);
		if (resistrationsCount > 0) {
			for (int i = 0; i < resistrationsCount; i++) {
				printf("%d. %s %s\n", result[i].number, result[i].name, result[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			if (UIDelete(result) == 0) {
				UIClear();
				break;
			}
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNING);
			UIClear();
			break;
		}
	}
}

/**
*@brief �ǂ݉��������@�\
*@note ���������ꍇ�ǂ݉����̈ꕔ�ł����͂����
*	   ����ɊY�����镶�����\�������B
*/
void UISearch() {
	int resistrationsCount = DMGetUserCount();
	char kana[DATA_MAX_LENGTH];
	char inputKey[3] = "a";
	struct data search_result[DATA_MAX_COUNT] = { 0 };

	if (resistrationsCount > 0) {
		printf("%s\n", MSG_UISEARCH_WORNING);
		scanf("%s", &kana);
		while (1) {
			resistrationsCount = DMSearch(kana, search_result);
			for (int i = 0; i < resistrationsCount; i++) {
				printf("%d. %s %s\n", search_result[i].number, search_result[i].name, search_result[i].yomi);
			}
			if (resistrationsCount > 0) {
				printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
				if (UIDelete(search_result) == 0) {
					UIClear();
					break;
				}
			}
			else {
				printf("%s\n\n", MSG_DISPCAT_WORNING);
				UIClear();
				break;
			}
		}
	}
	else {
		printf("%s\n\n", MSG_DISPCAT_WORNING);
		UIClear();
	}
}





/**
*@brief		�폜�@�\�y�у��C�����j���[�J��
*@retval	0 ���C�����j���[�ɖ߂�
*@retval	1 Y/y�I���@�������s��
*@retval	2 N/n�I���@�ꗗ�\���ɖ߂�
*@note		�ꗗ�\���܂��͌����@�\���g�p���ɓo�^�f�[�^
*			�\����̓��͂��ꂽ���e���̏���
*/
static char UIDelete(struct data* data)
{
	char inputAll[3] = "";
	struct data _entryList[DATA_MAX_COUNT] = { 0 };
	
	UIFflush();
	scanf("%2s", inputAll);
	if (UICharCheck('M', inputAll) == true) {
		return 0;
	}
	int input = atoi(inputAll);

	bool result = false;
	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (input == data[i].number && input != 0) {
			printf("�u%d. %s�v%s\n%s", data[i].number, data[i].name, MSG_UIDELETE_CHECK1, ARROW_TEXT);
			char inputChar[3];
			UIFflush();
			scanf("%2s", &inputChar);
			if (UICharCheck('Y', inputChar) == true) {
				result = DMDelete(data[i].number);
				if (result == false) {
					printf("%s\n", MSG_ADDNEW_ERROR);
					return 0;
				}
				else {
					return 1;
				}
			}
			else {
				return 2;
			}
		}
	}
	printf("%s\n", MSG_DISPCAT_WORNING2);
	return 1;
}

/**
*@brief		�ۑ��@�\
*@note		�I�������Ƃ��ۑ����\
**/
void UISave() 
{
	char saveCheck[3] = "";

	printf("%s\n%s", MSG_SAVE_CHECK, ARROW_TEXT);
	scanf("%s", saveCheck);
	if (UICharCheck('Y', saveCheck) == true) {
		DMTerminate("savedata.txt");
		printf("%s\n", MSG_SAVE_SUCCESS);
	}
	else {
		printf("%s\n", MSG_SAVE_STOP);
	}
	printf("\n");
	UIClear();
}

/**
*@brief	UICharCheck
*@note	�S�p���p�啶�������������f�ł���
*/
char UICharCheck(char mode, char answer[3])
{
	char* yTable[4] = { "y" , "Y", "��", "�x" };
	char* mTable[4] = { "m" , "M", "��", "�l" };
	char** tblPtr;

	if (mode == 'Y') {
		tblPtr = yTable;
	}
	else {
		tblPtr = mTable;
	}

	for (int i = 0; i < 4; i++) {
		if (strcmp(answer, tblPtr[i]) == 0) {
			printf("\n");
			return true;
		}
	}
	return false;
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

/**
*@brief	�����N���A�@�\
*@note	�N���A�O�Ɉꎞ��~�����
*/
void UIClear(void)
{
	system("pause");
	system("cls");
}