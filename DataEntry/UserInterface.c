
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Message.h"


void UIAddnew() {
	//êVãKìoò^èàóù
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
			printf("ìoò^èàóùÇåƒÇ—èoÇ∑ÅB\n\n");
		}
	}
	else {
		printf("%s\n\n", MSG_ADDNEW_OVER);
	}
}