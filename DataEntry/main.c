
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
		printf("%s\n", MSG_MAIN_MENU_INPORT);
		printf("%s\n", MSG_MAIN_MENU_EXPORT);
		printf("%s\n", MSG_MAIN_MENU_END);
		printf("%s\n", MSG_MAIN_MENU_SAVE);
		printf("%s", ARROW_TEXT);
		
		scanf("%d", &selectNumber);	

		switch (selectNumber)
		{
		case 0:
			UISave();
			break;
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
			UIInport();
			break;
		case 5:
			UIExport();
			break;
		case 6:
			break;
		default:
			UIFflush();
			break;
		}
	} while (selectNumber != 6);


	if (!DMTerminate("savedata.txt")) {
		//Debug
		printf("DMTerminate Error\n");
		return -1;
	}

	return 0;
}

