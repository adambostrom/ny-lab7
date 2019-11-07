#ifndef _CONSUMPTION_H_
#define _CONSUMPTION_H_
#define M 30

typedef struct {
	char name[M];
	float amount;
	char unit[M];
	float price; //<---- UPPGIFT2
}foodstuff;

typedef struct {
	foodstuff *foodData;
	int count;
}Shoppinglist;

foodstuff newGrocery(Shoppinglist *mem);
void AddName(foodstuff *FoodName);
float AddAmount();
void AddUnit(foodstuff *FoodUnit);
float AddPrice(); //<------ UPPGIFT2

void printGrocery(foodstuff *PrintList, int rakna);

void allocateMemory(Shoppinglist *temp);
void removeGrocery(Shoppinglist *remove);
void changeGrocery(Shoppinglist *change);

void saveGrocery(Shoppinglist *save);
void loadGrocery(Shoppinglist *load);

void searchGrocery(Shoppinglist *search); //UPPGIFT1
#endif
