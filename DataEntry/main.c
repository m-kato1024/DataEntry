
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Message.h"
#include "UserInterface.h"
#include "DataManager.h"

int main()
{
	int selectNumber;

	if (!DMInitialization("savedata.txt")) {
		//Debug
		printf("DMInitialization Error\n");
		return -1;
	}

	do {
		printf("%s\n", MSG_MAIN_MENU_TITLE);
		printf("%s\n", MSG_MAIN_MENU_ADDNEW);
		printf("%s\n", MSG_MAIN_MENU_LIST);
		printf("%s\n", MSG_MAIN_MENU_SEARCH);
		printf("%s\n", MSG_MAIN_MENU_END);
		printf("%s", ARROW_TEXT);
		scanf("%d", &selectNumber);

		switch (selectNumber)
		{
		case 1:	
			UIAddnew();
			break;
		case 2:
			UIDispCat();
			break;
		case 3:
			UISearch();
			break;
		case 4:
			break;
		default:
			break;
		}
	} while (selectNumber != 4);


	if (!DMTerminate("savedata.txt")) {
		//Debug
		printf("DMTerminate Error\n");
		return -1;
	}

	return 0;
}

