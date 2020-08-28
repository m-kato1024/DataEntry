
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 
#include "UserInterface.h"


static char UIDelete(struct data* data);

/**
*@brief 新規登録処理
*@note resistrationsCountが範囲外の時はエラー、
*answerが"Y"または"y"の時、登録処理を呼ぶ。
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
		if (strcmp(answer, "Y") == 0 || strcmp(answer, "y")  == 0 || strcmp(answer, "ｙ") == 0 || strcmp(answer, "Ｙ") == 0) {
			bool ret;
			ret = DMAddNew(num, kanji, kana);
			printf("\n");
			if (ret == false) {
				printf("%s\n\n", MSG_ADDNEW_ERROR);
			}
		}
		printf("\n");
	}
	else {
		printf("%s\n", MSG_ADDNEW_OVER);
	}
}

/**
*@brief 一覧表示機能
*@note 登録されてるデータの一覧を表示する。
*	   登録されていなかったり、削除の際に無関係の
*	   番号を入力するとエラーメッセージが表示される。
*/
void UIDispCat() {
	int resistrationsCount = DMGetUserCount();
	char inputKey[3] = "";
	struct data result[DATA_MAX_COUNT] = { 0 };

	while(1){
		resistrationsCount = DMListFetch(result);
		if (resistrationsCount > 0) {
			for (int i = 0; i < resistrationsCount; i++) {
				printf("%d. %s %s\n", result[i].number, result[i].name, result[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			if (UIDelete(result) == 0) {
				break;
			}
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNING);
			break;
		}
	}
}

/**
*@brief 読み仮名検索機能
*@note 検索した場合読み仮名の一部でも入力すると
*	   それに該当する文字が表示される。
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
					break;
				}
			}
			else {
				printf("%s\n\n", MSG_DISPCAT_WORNING);
				break;
			}
		}
	}
	else {
		printf("%s\n\n", MSG_DISPCAT_WORNING);
	}
}




/**
*@brief		削除機能及びメインメニュー遷移
*@retval	0 メインメニューに戻る
*@retval	1 処理を行う
*@note		一覧表示または検索機能を使用時に登録データ
*			表示後の入力された内容毎の処理
*/
static char UIDelete(struct data* data)
{
	char inputAll[3] = "";
	struct data _entryList[DATA_MAX_COUNT] = { 0 };
	
	UIFflush();
	scanf("%2s", inputAll);
	if (strcmp(inputAll, "m") == 0 || strcmp(inputAll, "M") == 0 || strcmp(inputAll, "Ｍ") == 0 || strcmp(inputAll, "ｍ") == 0) {
		printf("\n");
		return 0;
	}
	int input = atoi(inputAll);

	bool result = false;
	for (int i = 0; i < DATA_MAX_COUNT; i++) {
		if (input == data[i].number && input != 0) {
			printf("「%d. %s」%s\n%s", data[i].number, data[i].name, MSG_UIDELETE_CHECK1, ARROW_TEXT);
			char inputChar[3];
			UIFflush();
			scanf("%2s", &inputChar);
			if (strcmp(inputChar, "Y") == 0 || strcmp(inputChar, "y") == 0 || strcmp(inputChar, "Ｙ") == 0 || strcmp(inputChar, "ｙ") == 0) {
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
*@brief stdinのキーバッファはクリアする
*@note fflush()ではクリアできないため、独自で空になるまで読み飛ばすものとする
*/
void UIFflush(void)
{
	int buffer;
	while ((buffer = getc(stdin)) != EOF && buffer != '\n');
}
