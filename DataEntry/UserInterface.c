
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Message.h"

void commonProg1(int *a);
char commonProg2(void);

void UIAddnew() {
	//新規登録処理
	int resi = 10;

	int num = 0;
	char kanji[20];
	char kana[20];
	char yn;
	
	if (resi <= 10) {
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
		scanf("%*c%c", &yn);
		if (yn == 'Y' || yn == 'y') {
			printf("登録処理を呼び出す。\n\n");
		}
	}
	else {
		printf("%s\n\n", MSG_ADDNEW_OVER);
	}
}

void UIDispCat() {
	int resi = 0;
	char z = 'a';

	while(z != 'm' && z != 'M'){
		commonProg1(resi);
		if (resi > 0) {
			printf("一覧取得処理を呼び出す\n\n");
			printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);

			z = commonProg2();
		}
		commonProg1(&z);
	}
}

void UISerch() {
	int resi = 0;
	char kana;
	char z = 'a';

	while (z != 'm' && z != 'M') {
		commonProg1(resi);
		scanf("%s", &kana);

		
		printf("検索処理を呼び出す\n");
		printf("%s\n%s", MSG_DISPCAT_EXPL, ARROW_TEXT);

		z = commonProg2();
	}
}

void commonProg1(int *a)
{
	char x;
	if (&a <= 0) {
		printf("%s\n\n", MSG_DISPCAT_WORNIG);
		x = 'm';
		return x;
	}
}

char commonProg2(void)
{
	char x = '1';
	char a = 'w';

	while (a != x) {
		scanf("%*c%c", &a);
		if (a == 'm' || a == 'M') {
			printf("\n");
			return a;
		}
		else if (a != x) {
			printf("%s\n%s", MSG_DISPCAT_WORNIG2, ARROW_TEXT);
		}
		else if (a == x) {
			printf("削除処理を呼び出す\n\n");
		}
	}
}