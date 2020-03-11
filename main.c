#include "contact.h"

void Menu()
{
	printf("###############################################\n");
	printf("##   1. ADD         2. Del          3. Mod   ##\n");
	printf("##   4. Search      5. Show         6. clear ##\n");
	printf("##   7. Sort        8. Save         0. Exit  ##\n");
	printf("###############################################\n");
	printf("Please Select# ");
}

int main()
{
	contact_p contact = NULL;
	InitContact(&contact);// 注意，我传入的是一个二级指针

	int quit = 0;
	while (!quit){
		int select = 0;
		Menu();
		scanf("%d", &select);
		switch (select){
		case 1:
			AddPersonToContact(&contact);
			break;
		case 2:
			DelPersonFromContact(contact);//用姓名删除
			break;
		case 3:
			break;
		case 4:
			SearchPersonFromContact(contact);//用姓名查找
			break;
		case 5:
			ShowContact(contact);
			break;
		case 6:
			ClearContact(contact);
			break;
		case 7:
			SortContact(contact);
			break;
		case 8:
		    SaveContact(contact);
			break;
		case 0:
			quit = 1;
			break;
		}

	}
//	system("pause");
	return 0;
}