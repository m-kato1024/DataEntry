
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Message.h"
#include "DataManager.h" 
#include "UserInterface.h"

// 定数
static const char* IS_Y_WORD_TABLE[] = { "y", "Y", "ｙ","Ｙ", NULL };
static const char* IS_M_WORD_TABLE[] = { "m", "M", "ｍ","Ｍ", NULL };

// 内部関数プロトタイプ宣言
static bool _delete(struct data*, int);
static bool _isYes(char* );
static bool _isGotoMainMenu(char* );
static bool _existNumber(int, struct data*, int);

/**
*@brief 新規登録処理
*@note resistrationsCountが範囲外の時はエラー、
*answerが"Y"または"y"の時、登録処理を呼ぶ。
*/
void UIAddnew() {
	struct data newData = { 0 };
	char answer[3] = { 0 };
	
	//件数がMAXの場合は新規登録不可
	if (DMGetUserCount() == DATA_MAX_COUNT) {
		printf("%s\n\n", MSG_ADDNEW_OVER);
		return;
	}

	//番号入力
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NUMBER, ARROW_TEXT);
	do {		
		UIFflush();
		scanf("%d", &newData.number);
		if (newData.number < 1 || newData.number > DATA_MAX_COUNT ) {
			//範囲外の番号は入力させない
			printf("%s\n", MSG_ADDNEW_WORNIG);
			newData.number = 0;
		}
	} while (!newData.number);

	//名前の入力
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME1, ARROW_TEXT);
	UIFflush();
	scanf("%39s", newData.name);

	//ヨミガナの入力
	printf("%s\n%s", MSG_ADDNEW_RESISTER_NAME2, ARROW_TEXT);
	UIFflush();
	scanf("%39s", newData.yomi);

	//登録確認
	printf("%s%d %s(%s)\n%s\n%s", MSG_ADDNEW_CONFIRMATION1, newData.number, newData.name, newData.yomi, MSG_ADDNEW_CONFIRMATION2, ARROW_TEXT);
	UIFflush();
	scanf("%2s", answer);

	if (_isYes(answer)) {
		if (DMAddNew(&newData) == false) {
			printf("\n%s\n\n", MSG_ADDNEW_ERROR);
		}
	}
	
}

/**
*@brief 文字列チェック
*@param targetWord チェック対象文字列
*@param words 検査文字列テーブル
*@retval true 文字一致
*@retval false 文字一致していない
*@note	Mキー及びYキーが押下されたか否かを判定する処理。
*		第二引数に指定する文字列テーブルの文字と一致した場合はtrueを返す。
*/
static bool _wordCheck(char* targetWord, const char** checkTable) {
	int index = 0;
	while (checkTable[index] != NULL) {
		if (strcmp(targetWord, checkTable[index]) == 0) {
			return true;
		}
		index++;
	}
	return false;
}

/**
*@brief Yキー押下判定
*@param input 入力された文字列
*@retval true Yが入力された
*@retval false Y以外が入力された
*@note
*/
static bool _isYes(char* input) {
	return _wordCheck(input, IS_Y_WORD_TABLE);
}

/**
*@brief Mキー押下判定
*@param input 入力された文字列
*@retval true Mが入力された
*@retval false M以外が入力された
*@note 
*/
static bool _isGotoMainMenu(char* input) {
	return _wordCheck(input, IS_M_WORD_TABLE);
}

/**
*@brief 一覧表示機能
*@note 登録されてるデータの一覧を表示する。
*	   登録されていなかったり、削除の際に無関係の
*	   番号を入力するとエラーメッセージが表示される。
*/
void UIDisplayList(char* searchWord) {
	int count = 0;
	struct data list[DATA_MAX_COUNT] = { 0 };

	while(1){
		count = DMSearch(searchWord, list);

		if (count > 0) {
			for (int i = 0; i < count; i++) {
				printf("%d. %s %s\n", list[i].number, list[i].name, list[i].yomi);
			}
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);
			if (!_delete(list, count)) {
				break;
			}
		}
		else {
			printf("%s\n\n", MSG_DISPCAT_WORNIG);
			break;
		}
	}
	printf("\n");
}

/**
*@brief 読み仮名検索機能
*@note 検索した場合読み仮名の一部でも入力すると
*	   それに該当する文字が表示される。
*/
void UISearch() {
	char word[DATA_MAX_LENGTH];

	if (DMGetUserCount() == 0) {
		printf("%s\n\n", MSG_DISPCAT_WORNIG);
		return;
	}

	printf("%s\n", MSG_UISEARCH_WORNIG);
	UIFflush();
	scanf("%39s", word);
	UIDisplayList(word);	
}

/**
*@brief 番号存在チェック
*@param number 番号
*@param list 一覧データ
*@param listCount 一覧データの件数
*@retval true  存在する
*@retval false 存在しない
*@note 第一引数で指定され番号が引数list内で有効な番号であるかチェックする
*/
static bool _existNumber(int number, struct data* list, int listCount) 
{
	if (list == NULL) {
		return false;
	}

	for (int index = 0; index < listCount; index++) {
		if (list[index].number == number) {
			return true;
		}
	}
	return false;
}


/**
*@brief 削除機能及びメインメニュー遷移
*@param data 一覧データ
*@retval true  一覧表示継続
*@retval false メインメニューに戻る
*@note 
*/
static bool _delete(struct data* list, int listCount)
{
	char inputKey[3] = "";
	int deleteNumber;
	
	while (1) {
		UIFflush();
		scanf("%2s", inputKey);
		if (_isGotoMainMenu(inputKey)) {
			printf("\n");
			return false;
		}

		deleteNumber = atoi(inputKey);
		if (!_existNumber(deleteNumber, list, listCount)) {
			printf("%s\n", MSG_UIDELETE_NOT_FOUND);
			return true;
		}
		else {
			break;
		}
	}

	printf("「%d. %s」%s\n%s", deleteNumber, list[deleteNumber - 1].name, MSG_UIDELETE_CHECK1, ARROW_TEXT);
	UIFflush();
	scanf("%2s", inputKey);
	if (_isYes(inputKey)) {
		DMDelete(deleteNumber);
	}
	return true;
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
