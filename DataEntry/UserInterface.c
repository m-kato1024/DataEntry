
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Message.h"
#include "DataManager.h" 

static char commonProg1(void);
static char commonProg2(void);

/**
*@brief 新規登録処理
*@param resisrationsCount 登録されているデータの数
*@param num   入力された登録番号
*@param kanji 入力された名前(漢字)
*@param kana  入力された名前(読み仮名)
*@retval false 失敗
*@note resistrationsCountが範囲外の時はエラー、
*answerが"Y"または"y"の時、登録処理を呼ぶ。
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
*@brief 一覧表示機能
*@param resistrationsCount 登録されているデータの数
*@param inputKey 入力文字(数字)
*@note 登録されてるデータの一覧を表示する。
*	   登録されていなかったり、削除の際に無関係の
*	   番号を入力するとエラーメッセージが表示される。
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
			commonProg1(resistrationsCount);
			break;
		}
	}
}

void UISearch() {
	//読み仮名検索機能
	int resistrationsCount = DMGetUserCount();
	char kana[DATA_MAX_LENGTH];
	char inputKey = 'a';
	struct data search_result[DATA_MAX_COUNT] = { 0 };

	while (inputKey != 'm' && inputKey != 'M') {
		if (resistrationsCount > 0) {
			printf("%s\n", MSG_UISEARCH_WORNIG);
			scanf("%s", &kana);
			DMSearch(kana, search_result);

			resistrationsCount = DMSearch(kana, search_result);
			for (int i = 0; i < resistrationsCount; i++) {
				printf("%d %s %s", search_result[i].number, search_result[i].name, search_result[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			inputKey = commonProg2();
		}
		else {
			commonProg1(resistrationsCount);
			break;
		}
	}
}

static char commonProg1(void)
{
	printf("%s\n\n", MSG_DISPCAT_WORNIG);
	return 'm';
}

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
			printf("削除処理を呼び出す\n\n");
		}
	}
}