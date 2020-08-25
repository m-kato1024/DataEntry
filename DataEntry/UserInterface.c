
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 
#include "UserInterface.h"


static char UIDelete(struct data* data);

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
		scanf("%2s", answer);
		if (strcmp(answer, "Y") == 0 || strcmp(answer, "y")  == 0 || strcmp(answer, "��") == 0 || strcmp(answer, "�x") == 0) {
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
}

/**
*@brief �ꗗ�\���@�\
*@note �o�^����Ă�f�[�^�̈ꗗ��\������B
*	   �o�^����Ă��Ȃ�������A�폜�̍ۂɖ��֌W��
*	   �ԍ�����͂���ƃG���[���b�Z�[�W���\�������B
*/
void UIDispCat() {
	int resistrationsCount = DMGetUserCount();
	char inputKey = 'a';
	struct data result[DATA_MAX_COUNT] = { 0 };

	while(inputKey != 'm' && inputKey != 'M'){
		resistrationsCount = DMListFetch(result);
		if (resistrationsCount > 0) {
			for (int i = 0; i < resistrationsCount; i++) {
				printf("%d. %s %s\n", result[i].number, result[i].name, result[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			inputKey = UIDelete(result);
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
	int resistrationsCount = DMGetUserCount();
	char kana[DATA_MAX_LENGTH];
	char inputKey = 'a';
	struct data search_result[DATA_MAX_COUNT] = { 0 };

	while (inputKey != 'm' && inputKey != 'M') {
		if (resistrationsCount > 0) {
			printf("%s\n", MSG_UISEARCH_WORNING);
			scanf("%s", &kana);

			resistrationsCount = DMSearch(kana, search_result);
			for (int i = 0; i < resistrationsCount; i++) {
				printf("%d. %s %s\n", search_result[i].number, search_result[i].name, search_result[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			inputKey = UIDelete(search_result);
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
			break;
		}
	}
	printf("\n");
}



/**
*@brief �폜�@�\�y�у��C�����j���[�J��
*@retval inputAll	resistrationsNum�ƈ�v���Ȃ��Ƃ� ���͓��e��Ԃ�
*@note				�ꗗ�\���܂��͌����@�\���g�p���ɓo�^�f�[�^
*					�\����̓��͂��ꂽ���e���̏���
*/
static char UIDelete(struct data* data)
{
	char resistrationsNum = DMGetUserCount();
	char inputAll[3] = "";
	struct data _entryList[DATA_MAX_COUNT] = { 0 };
	
	UIFflush();
	scanf("%2s", inputAll);
	if (strcmp(inputAll, "m") == 0 || strcmp(inputAll, "M") == 0 || strcmp(inputAll, "M") == 0 || strcmp(inputAll, "��") == 0) {
		printf("\n");
		return inputAll[0];
	}

	int input = atoi(inputAll);

	//while (1) {
	//	if (data[input - 1].number == ) {
	//		printf("%s\n%s", MSG_DISPCAT_WORNING2, ARROW_TEXT);
	//	}
	//	else {
	//		break;
	//	}
	//}

	bool result = false;

	printf("�u%d. %s�v%s\n%s", input, data[input - 1].name, MSG_UIDELETE_CHECK1, ARROW_TEXT);
	char inputChar[3];
	UIFflush();
	scanf("%2s", &inputChar);
	if (strcmp(inputChar, "Y") == 0 || strcmp(inputChar, "y") == 0 || strcmp(inputChar, "Y") == 0 || strcmp(inputChar, "��") == 0) {
		result = DMDelete(input);
		if (result == false) {
			printf("%s\n", MSG_DISPCAT_WORNING2);
		}
	}
	return inputAll[0];
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
