
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 


static char UIDelete(void);
static void UIFflush(void);

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
		if (strcmp(answer, "Y") || strcmp(answer, "y") || strcmp(answer, "ｙ") || strcmp(answer, "Ｙ")) {
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
*@brief 一覧表示機能
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
			inputKey = UIDelete();
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
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
*@brief 削除機能及びメインメニュー遷移
*@retval inputAll	resistrationsNumと一致しないとき 入力内容を返す
*@note				一覧表示または検索機能を使用時に登録データ
*					表示後の入力された内容毎の処理
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
*@brief stdinのキーバッファはクリアする
*@note fflush()ではクリアできないため、独自で空になるまで読み飛ばすものとする
*/
static void UIFflush(void)
{
	int buffer;
	while ((buffer = getc(stdin)) != EOF && buffer != '\n');
}

/**
*@brief インポート機能
*@note 　ファイルパスを指定すると
*	   　データを読み取り内部データに登録する。
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
*@brief エクスポート機能
*@note 　ファイル指定すると登録されているデータを
*	   　ファイルにcsv形式で出力する。
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
