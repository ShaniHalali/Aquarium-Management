#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define MAX_ITEMS 20

#define PRINT(Fish){\
				printf("name : %s ,",Fish->name);\
				printf("lifeSpan : %d , ", Fish->lifeSpan); \
				printf("age : %d \n",Fish->age);\
}

struct ChildFish;

typedef struct
{
	int age;
	int lifeSpan;
	char* name;
}FreshFish;


void printFreshFish(FreshFish* fish);
FreshFish* createFreshFish(const int age, const int lifeSpan, const char* name);
FreshFish* createFreshFishFromUser();
void writeFreshFishToBinaryFile(FreshFish* fish, FILE* file);
void writeFreshFishToTxtFile(FreshFish* fish, FILE* file);
FreshFish* readFreshFishFromBinaryFile(FILE* file);
FreshFish* readFreshFishFromFile(FILE* file);
void freeFreshFish(FreshFish* fish);