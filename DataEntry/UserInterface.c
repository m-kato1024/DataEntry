
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Message.h"
#include "DataManager.h" 

static char commonProg2(void);

/**
*@brief �V�K�o�^����
*@param resisrationsCount �o�^����Ă���f�[�^�̐�
*@param num   ���͂��ꂽ�o�^�ԍ�
*@param kanji ���͂��ꂽ���O(����)
*@param kana  ���͂��ꂽ���O(�ǂ݉���)
*@retval false ���s
*@note resistrationsCount���͈͊O�̎��̓G���[�A
*answer��"Y"�܂���"y"�̎��A�o�^�������ĂԁB
*/
void UIAddnew() {
	int resistrationsCount = DMGetUserCount();

	int num = 0;
	char kanji[DATA_MAX_LENGTH];
	char kana[DATA_MAX_LENGTH];
	char answer;
	
	if (resistrationsCount <= DATA_MAX_COUNT) {
		do {
			printf("%s\n%s", MSG_ADDNEW_RESISTER_NUMBER, ARROW_TEXT);
			fflush(stdin);
			scanf("%d", &num);
			if (num < 1 || num > DATA_MAX_COUNT) {
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
		scanf("%*c%c", &answer);
		if (answer == 'Y' || answer == 'y') {
			bool ret;
			ret = DMAddNew(num, kanji, kana);
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
*@param resistrationsCount �o�^����Ă���f�[�^�̐�
*@param inputKey ���͕���(����)
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
			inputKey = commonProg2();
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
			break;
		}
	}
}

/**
*@brief �ǂ݉��������@�\
*@param resistrationsCount �o�^����Ă���f�[�^�̐�
*@param kana ��������ǂ݉���
*@param inputKey commonProg2����Ăяo�������e
*@param search_result ��������
*@note ���������ꍇ�ǂ݉����̈ꕔ�ł����͂����
*@	   ����ɊY�����镶�����\�������B
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
			inputKey = commonProg2();
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
			break;
		}
	}
}



/**
*@brief �폜�@�\�y�у��C�����j���[�J��
*@param resistrationsNum	�o�^���ꂽ�f�[�^�̔ԍ�
*@param inputNum			���͂��ꂽ�����܂��͐�����ێ�����
*@note						�ꗗ�\���܂��͌����@�\���g�p���ɓo�^�f�[�^
*							�\����̓��͂��ꂽ���e���̏���
*/
static char commonProg2(void)
{
	char resistrationsNum = '1';
	char inputNum = 'w';

	while (inputNum != resistrationsNum) {
		scanf("%*c%c\n", &inputNum);
		if (inputNum == 'm' || inputNum == 'M') {
			printf("\n");
			return inputNum;
		}
		else if (inputNum != resistrationsNum) {
			printf("%s\n%s", MSG_DISPCAT_WORNIG2, ARROW_TEXT);
		}
		else if (inputNum == resistrationsNum) {
			DMDelete(inputNum);
		}
	}
}