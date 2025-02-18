#pragma once
#include <stdio.h>
#include <ctype.h>

#define PRINTALLDOLPHIND(Fish) {\
    if (Fish) {\
        printf("Name: {%c}, ", Fish->nameByChar);\
        printf("Length: {%.2lf}, ", Fish->length);\
        printf("Friendship Value: {%d}\n", Fish->friendshipValue);\
    } else {\
        printf("Dolphin is NULL\n");\
    }\
}

typedef struct Dolphin {
    int friendshipValue;
    double length;
    struct Dolphin* next;
    struct Dolphin* prev;
    char nameByChar;
} Dolphin;

int countDolphinsInList(const Dolphin* head);
Dolphin* getDolphinFromUser(Dolphin* head);
Dolphin* searchDolphinByName(const char tav, const Dolphin* head);
void printDolphin(const Dolphin* dolphin);
void printDolphinList(const Dolphin* head);
//int removeByFriendshipValue(Dolphin** head, int friendShipValue);
int removeByFriendshipValue(Dolphin** head, const int friendShipValue);
Dolphin* createDolphin(const int friendshipValue, const double length, const char nameByChar);
void removeAndPrintChangesInDolphinsList(Dolphin** head);
void friendshipValueRiseByOne(Dolphin* head);
void friendshipValueDecreaseByRemovedDolphins(Dolphin** head, const int removedDolphinsCount);
int readFriendshipIntegerFromUser();
double getDolphinLength();
char getDolphinName(Dolphin* head);


//Files
void writeDolphinToBinaryFile(Dolphin* dolphin, FILE* file);
void writeDolphinToFile(Dolphin* dolphin, FILE* file);
Dolphin* readDolphinFromFile(FILE* file);
Dolphin* readDolphinFromBinFile(FILE* file);