
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
*@brief		削除機能及びメインメニュー遷移
*@retval	0 メインメニューに戻る
*@retval	1 Y/y選択　処理を行う
*@retval	2 N/n選択　一覧表示に戻る
*@note		一覧表示または検索機能を使用時に登録データ
*			表示後の入力された内容毎の処理
*/
static char UIDelete(struct data* data)
{
	char inputAll[4] = "";
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
			printf("「%d. %s」%s\n%s", data[i].number, data[i].name, MSG_UIDELETE_CHECK1, ARROW_TEXT);
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
*@brief		保存機能
*@note		終了せずとも保存が可能
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
*@note	全角半角大文字小文字が判断できる
*/
char UICharCheck(char mode, char answer[3])
{
	char* yTable[4] = { "y" , "Y", "ｙ", "Ｙ" };
	char* mTable[4] = { "m" , "M", "ｍ", "Ｍ" };
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
*@brief stdinのキーバッファはクリアする
*@note fflush()ではクリアできないため、独自で空になるまで読み飛ばすものとする
*/
void UIFflush(void)
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
	
	
		printf("%s\n", MSG_UIINPORT_WORNIG);
		printf("%s\n%s", MSG_UIINPORT_EXPL, ARROW_TEXT);
		scanf("%s", filename);
		while (strcmp(filename, "m") != 0 && strcmp(filename, "M") != 0) {
			int ret = DMImport(filename);
			if (ret >= 0) {
				printf("%s\n", MSG_UIINPORT_COMPLETED);
				printf("(%d%s)\n", ret, MSG_UIINPORT_COMPLETED2);
				printf("%s\n%s", MSG_UIINPORT_EXPL, ARROW_TEXT);
				scanf("%s", filename);
				

			}
			else {
				printf("%s\n", MSG_UIINPORT_ERROR);
				break;
			}

		}
	
}

/**
*@brief エクスポート機能
*@note 　ファイル指定すると登録されているデータを
*	   　ファイルにcsv形式で出力する。
*/
void UIExport() {
	char filename[50];
	printf("%s\n", MSG_UIEXPORT_WORNIG);
	printf("%s\n%s", MSG_UIINPORT_EXPL, ARROW_TEXT);
	scanf("%s", filename);
	while (strcmp(filename, "m") != 0 && strcmp(filename, "M") != 0) {

		int ret = DMExport(filename);
		if (ret > 0) {
			printf("%s\n", MSG_UIEXPORT_COMPLETED);
			printf("%s\n%s", MSG_UIINPORT_EXPL, ARROW_TEXT);
			scanf("%s", filename);
			
		}
		else if (ret == 0) {
			printf("%s\n", MSG_UIEXPORT_ERROR);
			break;
		}
		else {
			printf("%s\n", MSG_UIEXPORT_ERROR2);
			break;
		}
	}
}

/**
*@brief 履歴クリア機能
*@note クリア前に一時停止される
*/
void UIClear(void)
{
	system("pause");
	system("cls");
}
