
#include "Dolphin.h"
#include <stdlib.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)

int countDolphinsInList(const Dolphin* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

Dolphin* searchDolphinByName(const char tav, const Dolphin* head) {
    Dolphin* temp = head;
    while (temp != NULL) {
        if (temp->nameByChar == tav) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
Dolphin* getDolphinFromUser(Dolphin* head) {
    char tav = getDolphinName(head);
    // Increase friendship value for existing dolphins
    friendshipValueRiseByOne(head);

    Dolphin* newDolphin = (Dolphin*)calloc(1, sizeof(Dolphin));
    if (newDolphin == NULL) {
        printf("Error creating new dolphin\n");
        return head;
    }
    newDolphin->length = getDolphinLength();
    // The new Dolphin friendshipValue is equal to the num of Dolphins in the list before adding the new one
    newDolphin->friendshipValue = countDolphinsInList(head);
    newDolphin->nameByChar = tav;
    newDolphin->next = NULL;
    newDolphin->prev = NULL; // Initialize prev to NULL

    // Add new dolphin to the end of the list
    if (head == NULL) {
        return newDolphin; // New dolphin is the head of the list
    }
    Dolphin* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = newDolphin;
    newDolphin->prev = tail;

    printf("\nNew Dolphin added successfully! Its details are:\n");
    printDolphin(newDolphin);
    return head;
}

char getDolphinName(Dolphin* head)
{
    char tav;
    while (fgetchar() != '\n'); // Clear input buffer before starting

    printf("Enter the dolphin name by capital letter: ");
    do {
        tav = getchar();
        while (fgetchar() != '\n'); // Clear input buffer after getting character

        if (!isupper(tav) || searchDolphinByName(tav, head) != NULL) {
            if (searchDolphinByName(tav, head) != NULL) {
                printf("This name = %c is already taken\n", tav);
            }
            else {
                printf("Invalid input. \n");
            }
            printf("Enter the dolphin name by capital letter: ");
        }
    } while (!isupper(tav) || searchDolphinByName(tav, head) != NULL);
    return tav;
}

double getDolphinLength()
{
    double minLength = 10.0;
    double length = 0.0;
    printf("Enter the dolphin length (at least %.1lf): ", minLength);

    int validInput;
    do {
        validInput = scanf("%lf", &length);
        while (fgetchar() != '\n'); // Clear input buffer after reading number

        if (validInput != 1) {
            printf("Invalid input. ");
            printf("Please enter the dolphin length (at least %.1lf): ", minLength);
        }
        else if (length < minLength) {
            printf("%.2lf is smaller than the minimum length\n", length);
            printf("Please enter the dolphin length (at least %.1lf): ", minLength);
        }
    } while (length < minLength || validInput != 1);
    return length;
}


void printDolphin(const Dolphin* dolphin) {
    PRINTALLDOLPHIND(dolphin);
}

int removeByFriendshipValue(Dolphin** head,const int friendShipValue) {
    Dolphin* current = *head;
    Dolphin* prev = NULL;
    int removedCount = 0;

    while (current != NULL) {
        if (current->friendshipValue <= friendShipValue) {
            // Match found, remove the dolphin
            if (prev == NULL) { // The head needs to be removed
                *head = current->next;
                if (*head != NULL) {
                    (*head)->prev = NULL;
                }
            }
            else { // Removing a middle or last dolphin
                prev->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = prev;
                }
            }

            Dolphin* temp = current;
            current = current->next;
            free(temp); // Free the memory of the removed dolphin
            removedCount++;
        }
        else {
            prev = current;
            current = current->next;
        }
    }

    return removedCount;
}




Dolphin* createDolphin(const int friendshipValue, const double length, const char nameByChar) {
    Dolphin* newDolphin = (Dolphin*)malloc(sizeof(Dolphin));
    if (newDolphin == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newDolphin->friendshipValue = friendshipValue;
    newDolphin->length = length;
    newDolphin->nameByChar = nameByChar;
    newDolphin->next = NULL;
    newDolphin->prev = NULL; // Initialize prev to NULL
    return newDolphin;
}

void writeDolphinToBinaryFile(Dolphin* dolphin, FILE* file) {
    if (dolphin == NULL || file == NULL) {
        printf("Invalid input parameters!\n");
        return;
    }
    fwrite(&dolphin->friendshipValue, sizeof(int), 1, file);
    fwrite(&dolphin->length, sizeof(double), 1, file);
    fwrite(&dolphin->nameByChar, sizeof(char), 1, file);
}

void writeDolphinToFile(Dolphin* dolphin, FILE* file) {
    if (dolphin == NULL || file == NULL) {
        printf("Invalid input parameters!\n");
        return;
    }
    fprintf(file, "%c,%d,%.2f\n", dolphin->nameByChar, dolphin->friendshipValue, dolphin->length);
}
Dolphin* readDolphinFromFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    Dolphin* dolphin = (Dolphin*)calloc(1, sizeof(Dolphin));
    if (dolphin == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // Read dolphin data from file
    if (fscanf(file, " %c,%d,%lf", &dolphin->nameByChar, &dolphin->friendshipValue, &dolphin->length) != 3) {
        printf("Failed to read Dolphin details from file!\n");
        free(dolphin);
        return NULL;
    }

    dolphin->next = NULL;
    dolphin->prev = NULL;
    return dolphin;
}


Dolphin* readDolphinFromBinFile(FILE* file) {
    if (file == NULL) {
        printf("Invalid file!\n");
        return NULL;
    }

    Dolphin* dolphin = (Dolphin*)calloc(1, sizeof(Dolphin));
    if (dolphin == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    fread(&dolphin->friendshipValue, sizeof(int), 1, file);
    fread(&dolphin->length, sizeof(double), 1, file);
    fread(&dolphin->nameByChar, sizeof(char), 1, file);

    dolphin->next = NULL;
    dolphin->prev = NULL;
    return dolphin;
}

void removeAndPrintChangesInDolphinsList(Dolphin** head) {
    printf("================BEFORE==============\n");
    printDolphinList(*head);
    // Read and validate user input for friendship value
    int friendshipValue = readFriendshipIntegerFromUser();
    // Remove dolphins with friendshipValue less than or equal to the user input
    int removed = removeByFriendshipValue(head, friendshipValue);
    printf("================AFTER==============\n");
    if (removed > 0) {
        printf("%d dolphins removed. \nUpdated list after decrease each Dolphin friendshipValue :\n", removed);
        //Decrease Each Dolphin friendshipValue by the num of removed Dolphins
        friendshipValueDecreaseByRemovedDolphins(head, removed);
        printDolphinList(*head);
    }
    else {
        printf("No dolphins were removed.\n");
    }
}



void friendshipValueRiseByOne(Dolphin* head) {
    Dolphin* current = head;
    while (current != NULL) {
        current->friendshipValue++;
        current = current->next;
    }
}

void friendshipValueDecreaseByRemovedDolphins(Dolphin** head, const int removedDolphinsCount) {
    Dolphin* current = *head;
    while (current != NULL) {
        if (current->friendshipValue > removedDolphinsCount) {
            current->friendshipValue = current->friendshipValue - removedDolphinsCount;
        }
        else {
            current->friendshipValue = 0; // Ensure friendship value does not go negative
        }
        current = current->next;
    }
}


int readFriendshipIntegerFromUser() {
    int value;
    printf("Enter the friendship value from which and below the Dolphins will be deleted: ");
    while (scanf("%d", &value) != 1 || value < 0) {
        printf("Invalid input. Please enter a positive integer: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    return value;
}

void searchDolphin(const Dolphin* head)
{
    clearInputBuffer();
    char tav;
    printf("Please enter one Char\n");
    scanf("%c", &tav);
    Dolphin* result = searchDolphinByName(tav, head);
    if (result == NULL) {
        printf("No dolphin found\n");
    }
    else {
        printDolphin(result);
    }
}