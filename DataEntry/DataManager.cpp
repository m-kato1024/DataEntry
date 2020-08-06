// DataManager.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "DataManager.h"

struct data {
	int number;
	char name[40];
	char yomi[40];
}list1[10];

int gUserCount;


int DMInitialization(char* path) {

	memset(list1, 0, sizeof(list1));

	FILE *fp;
	fp = fopen(path, "r");
	if (fp == NULL) {
		return 1;
	}
	while (1) {
		fscanf(fp, "%d", &list1->number);
		fscanf(fp, "%s", list1->name);
		fscanf(fp, "%s", list1->yomi);

		if (feof(fp)) {
			break;
		}

	}
	return 0;
}

void DMAddNew(int input_number, char* input_name, char* input_yomi) {

	list1[input_number - 1].number = input_number;

	strcpy(list1[input_number - 1].name, input_name);

	strcpy(list1[input_number - 1].yomi, input_yomi);

	gUserCount++;

}

void DMDelete(int input_number) {
	for (int i = 0; i < 10; i++) {
		if (input_number == list1[i].number) {
			list1[i - 1].number = { 0 };
			strcpy(list1[i - 1].name, '\0');
			strcpy(list1[i - 1].yomi, '\0');

			gUserCount--;

		}

	}
}

void DMListFetch(char display_Num, char* display_Name) {


	for (int i = 0; i < 10; i++) {
		display_Num = list1[i].number;
		display_Name = list1[i].name;
	}
}

void DMSearch(char* input_yomi, char search_result) {

	char tem[40];

	for (int i = 0; i < 10; i++) {
		strcpy(tem, strstr(list1[i].yomi, input_yomi));

	}
}


int DMEnd(char* path) {
	FILE *fp;
	fp = fopen(path, "w");

	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%d\t%s\t%s\n", list1[i].number, list1[i].name, list1[i].yomi);
	}

	fclose(fp);
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
