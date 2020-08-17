
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Message.h"
#include "DataManager.h" 

void commonProg1(int *resistrationsCount);
char commonProg2(void);

void UIAddnew() {
	//�V�K�o�^����
	int resistrationsCount = DMGetUserCount;

	int num = 0;
	char kanji[DATA_MAX_LENGTH];
	char kana[DATA_MAX_LENGTH];
	char answer;
	
	if (resistrationsCount <= 10) {
		do {
			printf("%s\n%s", MSG_ADDNEW_RESISTER_NUMBER, ARROW_TEXT);
			fflush(stdin);
			scanf("%d", &num);
			if (num < 1 || num > 10) {
				printf("%s\n", MSG_ADDNEW_WORNIG);
			}
		} while (num < 1 || num > 10);

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
			printf("�o�^�������Ăяo���B\n\n");
		}
	}
	else {
		printf("%s\n\n", MSG_ADDNEW_OVER);
	}
}

void UIDispCat() {
	//�ꗗ�\���@�\
	int resistrationsCount = DMGetUserCount;
	char inputKey = 'a';

	while(inputKey != 'm' && inputKey != 'M'){
		if (resistrationsCount > 0) {
			printf("�ꗗ�擾�������Ăяo��\n\n");
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);

			inputKey = commonProg2();
		}
		else {
			commonProg1(resistrationsCount);
			break;
		}
		commonProg1(&inputKey);
	}
}

void UISearch() {
	//�ǂ݉��������@�\
	int resistrationsCount = DMGetUserCount;
	char kana[20];
	char inputKey = 'a';

	while (inputKey != 'm' && inputKey != 'M') {
		if (resistrationsCount > 0) {
			printf("%s\n", MSG_UISEARCH_WORNIG);
			scanf("%s", &kana);


			printf("�����������Ăяo��\n");
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);

			inputKey = commonProg2();
		}
		else {
			commonProg1(resistrationsCount);
			break;
		}
	}
}

void commonProg1(int *resistrationsCount)
{
	char x;
	if (resistrationsCount <= 0) {
		printf("%s\n\n", MSG_DISPCAT_WORNIG);
		x = 'm';
		return x;
	}
}

char commonProg2(void)
{
	char resistrationsNum = '1';
	char inputNum = 'w';

	while (inputNum != resistrationsNum) {
		scanf("%*c%c", &inputNum);
		if (inputNum == 'm' || inputNum == 'M') {
			printf("\n");
			return inputNum;
		}
		else if (inputNum != resistrationsNum) {
			printf("%s\n%s", MSG_DISPCAT_WORNIG2, ARROW_TEXT);
		}
		else if (inputNum == resistrationsNum) {
			printf("�폜�������Ăяo��\n\n");
		}
	}
}