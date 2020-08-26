
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 
#include "UserInterface.h"

#define IS_YES(a)				(_wordCheck(a, IS_Y_WORD_TABLE))
#define IS_GOTO_MAIN_MENU(a)	(_wordCheck(a, IS_M_WORD_TABLE))

// 定数
static const char* IS_Y_WORD_TABLE[] = { "y", "Y", "ｙ","Ｙ", NULL };
static const char* IS_M_WORD_TABLE[] = { "m", "M", "ｍ","Ｍ", NULL };

// 内部関数プロトタイプ宣言
static bool _wordCheck(char*, const char**);
static bool _deleteUi(User*, int);
static User* _findUser(int, User*, int);

/**
*@brief 新規登録処理
*@note resistrationsCountが範囲外の時はエラー、
*answerが"Y"または"y"の時、登録処理を呼ぶ。
*/
void UIAddnew() {
	User newData = { 0 };
	char answer[3] = { 0 };
	
	//件数がMAXの場合は新規登録不可
	if (DMGetUserCount() == DATA_MAX_COUNT) {
		printf("%s\n\n", MSG_ADDNEW_OVER);
		return;
	}

	//番号入力
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NUMBER, ARROW_TEXT);
	do {		
		UIKeyBufferClear();
		scanf("%d", &newData.number);
		if (newData.number < 1 || newData.number > DATA_MAX_COUNT ) {
			//範囲外の番号は入力させない
			printf("%s\n\n", MSG_ADDNEW_WORNIG);
			newData.number = 0;
		}
	} while (!newData.number);

	//名前の入力
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME1, ARROW_TEXT);
	UIKeyBufferClear();
	scanf("%39s", newData.name);

	//ヨミガナの入力
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME2, ARROW_TEXT);
	UIKeyBufferClear();
	scanf("%39s", newData.reading);

	//登録確認
	printf("%s%d %s(%s)\n%s\n%s", MSG_ADDNEW_CONFIRMATION1, newData.number, newData.name, newData.reading, MSG_ADDNEW_CONFIRMATION2, ARROW_TEXT);
	UIKeyBufferClear();
	scanf("%2s", answer);

	if (IS_YES(answer)) {
		if (DMAddNew(&newData) == false) {
			printf("\n%s\n\n", MSG_ADDNEW_ERROR);
		}
	}
	
}

/**
*@brief 一覧表示機能
*@note 登録されてるデータの一覧を表示する。
*	   登録されていなかったり、削除の際に無関係の
*	   番号を入力するとエラーメッセージが表示される。
*/
void UIDisplayList(char* searchWord) {
	int count = 0;
	User list[DATA_MAX_COUNT] = { 0 };

	do{
		count = DMSearch(searchWord, list);
		if (count > 0) {
			printf("-----------------------\n");
			for (int i = 0; i < count; i++) {
				printf("%d. %s %s\n", list[i].number, list[i].name, list[i].reading);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			if (!_deleteUi(list, count)) {
				break;
			}
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
		}
	} while (count > 0);

	printf("\n");
}

/**
*@brief 読み仮名検索機能
*@note 検索した場合読み仮名の一部でも入力すると
*	   それに該当する文字が表示される。
*/
void UISearch() {
	char word[DATA_FIELD_MAX_LENGTH];

	if (DMGetUserCount() == 0) {
		printf("%s\n\n", MSG_DISPCAT_WORNIG);
		return;
	}

	printf("%s\n", MSG_UISEARCH_WORNIG);
	UIKeyBufferClear();
	scanf("%39s", word);
	UIDisplayList(word);	
}

/**
*@brief キーバッファはクリアする
*@note fflush()ではクリアできないため、独自で空になるまで読み飛ばすものとする
*/
void UIKeyBufferClear(void)
{
	int buffer;
	while ((buffer = getc(stdin)) != EOF && buffer != '\n');
}

/**
*@brief ユーザー存在チェック
*@param number 番号
*@param list 一覧データ
*@param listCount 一覧データの件数
*@retval NULL以外  存在する
*@retval NULL 存在しない
*@note 引数listの中にnumberに該当するユーザーが存在するか調べる
*/
static User* _findUser(int number, User* list, int listCount)
{
	for (int index = 0; index < listCount; index++) {
		if (list[index].number == number) {
			return &list[index];
		}
	}
	return NULL;
}

/**
*@brief 削除機能及びメインメニュー遷移
*@param data 一覧データ
*@param listCount 一覧データの件数
*@retval true  一覧表示継続
*@retval false メインメニューに戻る
*@note 
*/
static bool _deleteUi(User* list, int listCount)
{
	char inputKey[3];
	int deleteNumber;
	
	UIKeyBufferClear();
	scanf("%2s", inputKey);
	if (IS_GOTO_MAIN_MENU(inputKey)) {
		printf("\n");
		return false;
	}

	deleteNumber = atoi(inputKey);
	User* user = _findUser(deleteNumber, list, listCount);
	if (user == NULL) {
		printf("%s\n\n", MSG_UIDELETE_NOT_FOUND);
		return true;
	}

	printf("「%d. %s」%s\n%s", user->number, user->name, MSG_UIDELETE_CHECK1, ARROW_TEXT);
	UIKeyBufferClear();
	scanf("%2s", inputKey);
	if (IS_YES(inputKey)) {
		DMDelete(deleteNumber);
	}
	return true;
}

/**
*@brief 文字列チェック
*@param targetWord チェック対象文字列
*@param checkTable 検査文字列テーブル
*@retval true 文字一致
*@retval false 文字一致していない
*@note	Mキー及びYキーが押下されたか否かを判定する処理。
*		第二引数に指定する文字列テーブルの文字と一致した場合はtrueを返す。
*/
static bool _wordCheck(char* targetWord, const char** checkTable) {
	for (int index = 0; checkTable[index] != NULL; index++) {
		if (strcmp(targetWord, checkTable[index]) == 0) {
			return true;
		}
	}
	return false;
}
