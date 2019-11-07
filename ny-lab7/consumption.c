
#define _CRT_SECURE_NO_WARNINGS
#include "consumption.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define M 30


void searchGrocery(Shoppinglist *search) { //UPPGIFT 1
	while (getchar() != '\n');
	char searchName[M];
	foodstuff *browse = search->foodData;
	int rows = 0, found = 0;
	printf("Enter product name to search for:");
	gets(searchName);

	for (int i = 0; i < search->count; i++) {
		rows++;
		if (strcmp(searchName, (browse + i)->name) == 0) {
			printf("\n");
			printf("%d name: %-32s", rows, browse[rows - 1].name);
			printf("amount: %-32.1f", browse[rows - 1].amount);
			printf("unit: %-32s\n", browse[rows - 1].unit);
			found++;
		}
			
	}
	if (found == 0)
		printf("\n%s can not be found in the list\n", searchName);
}

void loadGrocery(Shoppinglist *load) {
	FILE *fp;
	char filename[M];

	while (getchar() != '\n');
	printf("name of textfile?");
	gets(filename);
	strcat(filename, ".txt");

	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("File could not be opened\n");
		return;
	}
	char ch, cp[5] = { 0,0,0,0,0 };
	int count = 0;

	while (ch = fgetc(fp)) { //läser in första nummret i textdokumentet vilket representerar antalet artiklar.
		if (ch == '\n') {
			putchar('\n');
			break;
		}
		cp[count] = ch;
		putchar(ch);
		count++;
	}
	count = atoi(cp);

	free(load->foodData);	//om aktuellt minne just nu finns allokerat så frigörs det
	load->count = 0;

	for (int i = 0; i < count; i++) {     //allokerar nytt minne baserat på första nummret i textdokumentet.
		allocateMemory(load);
	}
	foodstuff *read = load->foodData;
	for (int i = 0; i < count; i++) {

		int j = 0;							//Läs in namn från textdokument till programmet
		char c;
		while (c = fgetc(fp)) {
			if (c == '\t') {
				putchar('\t');
				break;
			}
			read[i].name[j] = c;
			++j;
			putchar(c);
		}
		read[i].name[j] = '\0';				//


		j = 0;								//Läs in antal från dokument till programmet	
		char d, f[5] = { 0,0,0,0,0 };
		while (d = fgetc(fp)) {
			if (d == '\t') {
				putchar('\t');
				break;
			}
			f[j] = d;
			putchar(d);
			j++;
		}
		float num = atof(f);
		read[i].amount = num;				//

		j = 0;								//Läs in enhet från dokument till programmet
		char e;
		while (e = fgetc(fp)) {
			if (e == '\t') {
				putchar('\t');
				break;
			}
			read[i].unit[j] = e;
			++j;
			putchar(e);
		}
		read[i].unit[j] = '\0';				//
											//UPPGIFT 2
		j = 0;								//Läs in pris från dokument till programmet	
		char h, g[5] = { 0,0,0,0,0 };
		while (h = fgetc(fp)) {
			if (h == '\n') {
				putchar('\n');
				break;
			}
			g[j] = h;
			putchar(d);
			j++;
		}
		float num2 = atof(g);
		read[i].price = num2;

	}

	fclose(fp);
}

void saveGrocery(Shoppinglist *save) {
	FILE *fp;
	foodstuff *write = save->foodData;
	char filename[M];

	if (save->count < 1) {
		printf("\nYOU CANNOT SAVE AN EMPTY LIST!!");
		while (getchar() != '\n');
		return;
	}

	while (getchar() != '\n');
	printf("name of textfile?");
	gets(filename);
	strcat(filename, ".txt");

	fp = fopen(filename, "w");  //<---skrivtest
	if (fp == NULL) {
		printf("File could not be opened\n");
		return;
	}
	fprintf(fp, "%d\n", save->count);

	for (int i = 0; i < save->count; i++) {
		fprintf(fp, "%s\t", write[i].name);
		fprintf(fp, "%.1f\t", write[i].amount);
		fprintf(fp, "%s\t", write[i].unit);
		fprintf(fp, "%.1f\n", write[i].price);                        //<-----------------UPPGIFT2
	}

	fclose(fp);
}

void changeGrocery(Shoppinglist *change) {
	int which, foodNumber = change->count;

	printf("Which item do you want to change?");
	scanf("%d", &which);
	which = which - 1;

	if (foodNumber < which + 1 || which < 0) {
		printf("\nITEM %d DOES NOT EXIST", foodNumber);
		while (getchar() != '\n');
		return;
	}

	change->foodData[which].amount = AddAmount();
	while (getchar() != '\n');
}

void removeGrocery(Shoppinglist *remove) {

	int vara, foodNumber = remove->count;

	printf("which grocery do you want to remove?: ");
	scanf("%d", &vara);
	vara = vara - 1;

	if (foodNumber < vara + 1 || vara < 0) {
		printf("\nTHIS ARTICLE DOESN'T EXIST!");
		while (getchar() != '\n');
		return;
	}

	int i;
	if (foodNumber >= vara + 1) {
		for (i = vara; i < foodNumber - 1; i++) {
			remove->foodData[i] = remove->foodData[i + 1];
		}
		Shoppinglist *temp = remove;
		temp->foodData = (foodstuff*)realloc(remove->foodData, (remove->count - 1) * sizeof(foodstuff));
		if (temp->foodData != NULL) {
			remove->count = temp->count;
		}
		remove->count--; //<------ går ej att sätta inuti if-satsen ovanför, blir något fel vid print av tom lista då. spaghettikod?.... fråga ngn kanske
		while (getchar() != '\n');
	}
}

void allocateMemory(Shoppinglist *add) {
	if (add->count == 0) {											//om inget minne allokerats tidigare
		add->foodData = (foodstuff*)calloc(1, sizeof(foodstuff));	//allokera minne med calloc, 1 plats med storlekten foodstuff

		if (add->foodData == NULL) {								//om det inte fungerade, informera och return.
			printf("could not c-allocate memory");
			return;
		}
		else
			add->count++;
	}

	else if (add->count > 0) {										//om minne allokerats tidigare
		Shoppinglist *temp = add;									//skapa temorär listpekare
		temp->foodData = (foodstuff*)realloc(add->foodData, (add->count + 1) * sizeof(foodstuff));
		if (temp->foodData != NULL) {
			add->count = temp->count;
			add->count++;
		}
	}
}

foodstuff newGrocery(Shoppinglist *mem) {
	allocateMemory(mem);
	foodstuff GroceryList;
	printf("\n\n\tADD GROCERY\n");
	printf("----------------------------------------------------------------------------------------------------------------\n");

	AddName(&GroceryList);
	GroceryList.amount = AddAmount();
	AddUnit(&GroceryList);
	GroceryList.price = AddPrice();						//<------------------------- UPPG 2

	return GroceryList;
}


void AddName(foodstuff *FoodName) {
	while (getchar() != '\n');
	printf("name: ");
	fgets(FoodName->name, M - 1, stdin);

	int length = strlen(FoodName->name);

	if (FoodName->name[length - 1] == '\n') {			//om sista inlästa tecken är newline
		FoodName->name[length - 1] = '\0';			    //nollställ det elementet
		length--;										//minska längden med 1
	}
	else {
		while (getchar() != '\n');						//annars, rensa inläsningsbuffert(alltså om antal tecken(M-1) överskridits i fgets och lästs in i nästa minne)
	}
}

float AddPrice() {											//<----------------------------- UPPG2
	float tempTal;
	printf("price: ");

	while (scanf("%f", &tempTal) == 0 || tempTal < 0)
	{
		printf("Please enter a float equal to or above zero: ");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');
	return tempTal;
}

float AddAmount() {
	float tempTal;
	printf("amount: ");

	while (scanf("%f", &tempTal) == 0 || tempTal < 0)
	{
		printf("Please enter a float equal to or above zero: ");
		while (getchar() != '\n');
	}

	return tempTal;
}


void AddUnit(foodstuff *FoodUnit) {
	while (getchar() != '\n');
	printf("unit: ");
	fgets(FoodUnit->unit, M - 1, stdin);

	int length = strlen(FoodUnit->unit);

	if (FoodUnit->unit[length - 1] == '\n') {			//om sista inlästa tecken är newline
		FoodUnit->unit[length - 1] = '\0';			    //nollställ det elementet
		length--;										//minska längden med 1
	}
	else {
		while (getchar() != '\n');						//annars, rensa inläsningsbuffert(alltså om antal tecken(M-1) överskridits i fgets och lästs in i nästa minne)
	}
}


void printGrocery(foodstuff *printList, int rakna) {
	while (getchar() != '\n');
	printf("\n\n\tGROCERYLIST\n");
	printf("----------------------------------------------------------------------------------------------------------------\n");
	if (rakna > 0)
	{
		printf("Your list contains %d items", rakna);
		for (int i = 0; i < rakna; i++) {
			printf("\n%d: ", i + 1);
			printf("name: %-25s", printList[i].name);
			printf("amount: %-25.1f", printList[i].amount);
			printf("unit: %.2fkr/%-25s", printList[i].price, printList[i].unit);  //<-------------UPPG2
			printf("(%.2fkr)", (printList[i].price*printList[i].amount));			//<----------------UPPG2
		}
	}
	else
		printf("\nYour shopping list is empty.\n");
	printf("\n");
}