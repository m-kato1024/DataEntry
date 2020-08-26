
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 


static char UIDelete(void);
static void UIFflush(void);

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
			fflush(stdin);
			scanf("%d", &num);
			if (num < 1 || num > DATA_MAX_COUNT ) {
				printf("%s\n", MSG_ADDNEW_WORNIG);
			}
		} while (num < 1 || num > DATA_MAX_COUNT);

		printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME1, ARROW_TEXT);
		fflush(stdin);
		scanf("%s", &kanji);

		printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME2, ARROW_TEXT);
		fflush(stdin);
		scanf("%s", &kana);

		printf("%s%d %s(%s)\n%s\n%s", MSG_ADDNEW_CONFIRMATION1, num, kanji, kana, MSG_ADDNEW_CONFIRMATION2, ARROW_TEXT);

		fflush(stdin);
		scanf("%2s", answer);
		if (strcmp(answer, "Y") || strcmp(answer, "y") || strcmp(answer, "��") || strcmp(answer, "�x")) {
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
				printf("%d %s %s\n", result[i].number, result[i].name, result[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			inputKey = UIDelete();
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
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
	char inputKey = 'a';
	struct data search_result[DATA_MAX_COUNT] = { 0 };

	while (inputKey != 'm' && inputKey != 'M') {
		if (resistrationsCount > 0) {
			printf("%s\n", MSG_UISEARCH_WORNIG);
			scanf("%s", &kana);

			resistrationsCount = DMSearch(kana, search_result);
			for (int i = 0; i < resistrationsCount; i++) {
				printf("%d %s %s\n", search_result[i].number, search_result[i].name, search_result[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			inputKey = UIDelete();
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
			break;
		}
	}
}



/**
*@brief �폜�@�\�y�у��C�����j���[�J��
*@retval inputAll	resistrationsNum�ƈ�v���Ȃ��Ƃ� ���͓��e��Ԃ�
*@note				�ꗗ�\���܂��͌����@�\���g�p���ɓo�^�f�[�^
*					�\����̓��͂��ꂽ���e���̏���
*/
static char UIDelete(void)
{
	char resistrationsNum = DMGetUserCount();
	char inputAll[4] = "";
	
	UIFflush();
	scanf("%3s", inputAll);
	if (strcmp(inputAll, "m") == 0 || strcmp(inputAll, "M") == 0) {
		printf("\n");
		return inputAll[0];
	}

	bool result = false;
	int input = atoi(inputAll);
	printf("%s%s", MSG_UIDELETE_CHECK1, ARROW_TEXT);
	char inputChar[3];

	UIFflush();
	scanf("%2s", inputChar);
	if (strcmp(inputChar, "Y") == 0 || strcmp(inputChar, "y") == 0) {
		result = DMDelete(input);
		if (result == false) {
			printf("%s\n%s", MSG_DISPCAT_WORNIG2, ARROW_TEXT);
		}
	}
	return inputAll[0];
}
/**
*@brief stdin�̃L�[�o�b�t�@�̓N���A����
*@note fflush()�ł̓N���A�ł��Ȃ����߁A�Ǝ��ŋ�ɂȂ�܂œǂݔ�΂����̂Ƃ���
*/
static void UIFflush(void)
{
	int buffer;
	while ((buffer = getc(stdin)) != EOF && buffer != '\n');
}

/**
*@brief �C���|�[�g�@�\
*@note �@�t�@�C���p�X���w�肷���
*	   �@�f�[�^��ǂݎ������f�[�^�ɓo�^����B
*/
void UIInport() {
	
	char filename[50];
	int line;

	
		printf("%s\n%s", MSG_UIINPORT_WORNIG, ARROW_TEXT);
		scanf("%s", filename);

		bool ret = DMImport(filename);
		if (ret == true) {
			line = DMLine();
			printf("%s\n", MSG_UIINPORT_COMPLETED);
			printf("(%d%s)\n", line, MSG_UIINPORT_COMPLETED2);
			
		}
		else {
			printf("%s\n", MSG_UIINPORT_ERROR);
		}
		
		
	
}

/**
*@brief �G�N�X�|�[�g�@�\
*@note �@�t�@�C���w�肷��Ɠo�^����Ă���f�[�^��
*	   �@�t�@�C����csv�`���ŏo�͂���B
*/
void UIExport() {
	char filename[50];
	printf("%s\n%s", MSG_UIEXPORT_WORNIG, ARROW_TEXT);
	scanf("%s", filename);

	int ret = DMExport(filename);
	if (ret == 0) {
		printf("%s\n", MSG_UIEXPORT_COMPLETED);
	}
	else if(ret == 1) {
		printf("%s\n", MSG_UIEXPORT_ERROR);
	}
	else {
		printf("%s\n", MSG_UIEXPORT_ERROR2);
	}
}
