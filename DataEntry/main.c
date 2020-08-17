
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Message.h"
#include "UserInterface.h"

int main()
{
	int selectNumber;



	do {
		printf("%s\n", MSG_MAIN_MENU_TITLE);
		printf("%d.%s\n", 1, MSG_MAIN_MENU_ADDNEW);
		printf("%d.%s\n", 2, MSG_MAIN_MENU_LIST);
		printf("%d.%s\n", 3, MSG_MAIN_MENU_SEARCH);
		printf("%d.%s\n", 4, MSG_MAIN_MENU_END);
		printf("->");
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



	return 1;
}

