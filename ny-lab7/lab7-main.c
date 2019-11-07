#define _CRT_SECURE_NO_WARNINGS
#include "consumption.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define M 30

int main(void) {
	Shoppinglist ShopGrocery;
	char menyval;
	ShopGrocery.count = 0;
	ShopGrocery.foodData = NULL;
	printf("Welcome to the shopping list manager");
	do {
		printf("\n1 - add grocery\n2 - print shopping list\n3 - remove grocery from list\n4 - change grocery in list\n5 - save shopping list to file\n6 - load shopping list from file\n7 - search in list\n8 - exit\nWhat do you want to do?: ");
		scanf("%c", &menyval);
		switch (menyval) {
		case '1':  ShopGrocery.foodData[ShopGrocery.count-1] = newGrocery(&ShopGrocery); break;
		case '2':	printGrocery(ShopGrocery.foodData, ShopGrocery.count); break;
		case '3': removeGrocery(&ShopGrocery); break;
		case '4': changeGrocery(&ShopGrocery); break;
		case '5':	saveGrocery(&ShopGrocery); break;
		case '6': loadGrocery(&ShopGrocery); break;
		case '7': searchGrocery(&ShopGrocery); break;	//UPPGIFT 1
		case '8': break;
		default: break;
		}
	} while (menyval != '8');

	system("pause");
	return 0;
}


