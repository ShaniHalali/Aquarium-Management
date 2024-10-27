#include <stdio.h>
#include <stdlib.h>
#include "Dolphin.h"
#include "ClownFish.h"
#include "generalFunctions.h"
#include "SeaCreatures.h"
#include "Shark.h"
#include "CentralAquarium.h"
#include "SaltAquarium.h"


void displayMainMenu();
void displayAquariumMenu(CentralAquarium* aquarium);
void displaySaltyWaterAquariumMenu(SaltAquarium* saltAquarium);
void displayFreshAquariumMenu(FreshAquarium* freshAquarium);

// we used this function to save data for the restart files

//CentralAquarium* createOurAquarium() {
//    CentralAquarium* myAquarium = initCentralAquarium("Our Aquarium");
//    Dolphin* dolphin1 = createDolphin(0, 5.3, 'A');
//    Dolphin* dolphin2 = createDolphin(1, 6.1, 'B');
//    Dolphin* dolphin3 = createDolphin(2, 4.9, 'C');
//    Dolphin* dolphin4 = createDolphin(3, 7.22, 'D');
//    insertDolphinLinkedList(myAquarium->freshAquarium, dolphin1);
//    insertDolphinLinkedList(myAquarium->freshAquarium, dolphin2);
//    insertDolphinLinkedList(myAquarium->freshAquarium, dolphin3);
//    insertDolphinLinkedList(myAquarium->freshAquarium, dolphin4);
//
//
//    FreshFish* freshFish1 = createFreshFish(10, 11, "fresh1");
//    addFreshFish(myAquarium->freshAquarium, freshFish1);
//    FreshFish* freshFish2 = createFreshFish(7, 8, "fresh2");
//    addFreshFish(myAquarium->freshAquarium, freshFish2);
//
//    addRandomFish(myAquarium->freshAquarium, createRandomFish());
//    addRandomFish(myAquarium->freshAquarium, createRandomFish());
//    addRandomFish(myAquarium->freshAquarium, createRandomFish());
//
//    SeaCreature* seaCreature1 = createSeaCreature(8, 10, 1, 2);
//    SeaCreature* seaCreature2 = createSeaCreature(3, 8, 3, 4);
//    addSeaCreature(myAquarium->saltAquarium, seaCreature1);
//    addSeaCreature(myAquarium->saltAquarium, seaCreature2);
//
//    Shark* shark1 = createShark("MommyShark", 700.0, 7, 12, 2, 4);
//    Shark* shark2 = createShark("DaddyShark", 1500.0, 10, 30, 0, 3);
//    addShark(myAquarium->saltAquarium, shark1);
//    addShark(myAquarium->saltAquarium, shark2);
//
//    ClownFish* clownFish1 = createClownFish("Nemo1", 2, 4, 1, 2);
//    ClownFish* clownFish2 = createClownFish("Nemo2", 5, 8, 3, 4);
//    addClownFish(myAquarium->saltAquarium, clownFish1);
//    addClownFish(myAquarium->saltAquarium, clownFish2);
//
//
//
//
//    return myAquarium;
//}

int main() {
    //CentralAquarium* aquarium = createOurAquarium();
    CentralAquarium* aquarium ;

   
    int choice;
    displayMainMenu();

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            aquarium = readCentralAquariumFromTxtFile("starter_aquarium.txt");
            printAllCentralAquariumDetails(aquarium);
            displayAquariumMenu(aquarium);
            break;
        case 2:
            aquarium = readCentralAquariumFromBinaryFile("starter_aquarium.bin");
            if (aquarium) {
                printf("Aquarium data loaded from binary file successfully.\n");
                printAllCentralAquariumDetails(aquarium);
                displayAquariumMenu(aquarium);
            }
            else {
                printf("Failed to load data from the binary file.\n");
            }
            
            break;
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    }
    return 0;
}

void displayMainMenu() {
    printf("====== STARTER MENU ======\n");
    printf("1. Load starter aquarium data from text file\n");
    printf("2. Load starter aquarium data from binary file\n");
    printf("========================\n");
}



void displayAquariumMenu(CentralAquarium* aquarium) {
    int choice;
    //Restart the last user changes
      writeCentralAquariumToBinaryFile(aquarium, "user_binary_changes.bin");
      writeCentralAquariumToTxtFile(aquarium, "user_text_changes.txt");

      while (1) {
          printf("\n====== SL AQUA-LAND MENU ======\n");
          printf("1.  Display Central Aquarium details\n");
          printf("2.  Save aquarium details to text file and to Binary file\n");
          printf("3.  Load aquarium details from text file\n");
          printf("4.  Load aquarium details from binary file\n");
          printf("5.  Sort sharks\n");
          printf("6.  Search sharks\n");
          printf("7.  Salty Water Aquarium Menu\n");
          printf("8.  Fresh Aquarium Menu\n");
          printf("9.  Remove dolphins by friendship value\n");
          printf("10. Increase age of saltwater creatures\n");
          printf("11. Find the oldest Fresh Fish\n");
          printf("12. Search dolphin by character\n");
          printf("13. Exit\n");
          printf("==================================\n");

          printf("Enter your choice: ");
          scanf("%d", &choice);

          switch (choice) {
          case 1:
              printAllCentralAquariumDetails(aquarium);
              break;
          case 2:
              writeCentralAquariumToTxtFile(aquarium, "user_text_changes.txt");
              printf("Write to file successfully\n");
              if (aquarium) {
                  writeCentralAquariumToBinaryFile(aquarium, "user_binary_changes.bin");
                  printf("Write to binary file successfully.\n");
              }
              else {
                  printf("No aquarium data to save.\n");
              }
              break;
          case 3:
              aquarium = readCentralAquariumFromTxtFile("user_text_changes.txt");
              printAllCentralAquariumDetails(aquarium);
              break;
          case 4:
              aquarium = readCentralAquariumFromBinaryFile("user_binary_changes.bin");
              if (aquarium) {
                  printf("Aquarium data loaded from binary file successfully.\n");
                  printAllCentralAquariumDetails(aquarium);
                  displayAquariumMenu(aquarium);
              }
              else {
                  printf("Failed to load data from the binary file.\n");
              }
              break;
          case 5:
              sortSharksMenu(aquarium->saltAquarium);
              break;
          case 6:
              sharkSearchMenu(aquarium->saltAquarium);
              break;
          case 7:
              displaySaltyWaterAquariumMenu(aquarium->saltAquarium);
              break;
          case 8:
              displayFreshAquariumMenu(aquarium->freshAquarium);
              break;
          case 9:
              removeAndPrintChangesInDolphinsList(&(aquarium->freshAquarium->dolphinDoublyLinkedList));
              break;
          case 10:
              ageAllSeaCreatures(aquarium->saltAquarium);
              ageAllSharks(aquarium->saltAquarium);
              ageAllClownFishes(aquarium->saltAquarium);
              break;
          case 11:
              findOldestFish(aquarium->freshAquarium->freshFish, aquarium->freshAquarium->freshFishSize);
              break;
          case 12:
              clearInputBuffer();
              char tav;
              printf("Please enter one Char\n");
              scanf(" %c", &tav); // Notice the space before %c to skip any leftover newline characters
              Dolphin* result = searchDolphinByName(tav, aquarium->freshAquarium->dolphinDoublyLinkedList);
              if (result == NULL) {
                  printf("No dolphin found\n");
              }
              else {
                  printDolphin(result);
              }
              break;
          case 13:
              printf("Exiting the system...\n");
              freeCentralAquarium(aquarium);
              exit(0);
          default:
              printf("Invalid choice! Please try again.\n");
              break;
          }
      }


}

void displaySaltyWaterAquariumMenu(SaltAquarium* saltAquarium) {
    int choice;

    while (1) {
        printf("====== SALTY WASTER AQUARIUM MENU ======\n");
        printf("1. Add Shark\n");
        printf("2. Add Sea Creature\n");
        printf("3. Add Clown Fish\n");
        printf("4. Exit to Aquarium Menu\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
        {
            Shark* newShark = (Shark*)malloc(sizeof(Shark));
            if (newShark != NULL) {
                getSharkFromUser(newShark);

                addShark(saltAquarium, newShark);

                printf("Shark added successfully!\n");
            }
            else {
                printf("Failed to create shark.\n");
            }
            break;
        }
        case 2:
        {
            SeaCreature* newSeaCreature = getSeaCreatureFromUser();
            if (newSeaCreature != NULL) {
                addSeaCreature(saltAquarium, newSeaCreature);
                printf("Sea creature added successfully!\n");
            }
            else {
                printf("Failed to create sea creature.\n");
            }
            break;
        }
        case 3:
        {
            ClownFish* newClownFish = (ClownFish*)malloc(sizeof(ClownFish));
            if (newClownFish != NULL) {
                getClownFishFromUser(newClownFish);

                addClownFish(saltAquarium, newClownFish);
                printf("Clown fish added successfully!\n");
            }
            else {
                printf("Failed to create clown fish.\n");
            }
            break;
        }
        case 4:
            printf("Exiting to central Aquarium Menu...\n");
            return;  // back to the main menu
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    }
}

void displayFreshAquariumMenu(FreshAquarium* freshAquarium)
{
    int choice;
    do {
        printf("====== FRESH WATER AQUARIUM MENU =======\n");
        printf("1. Add Fresh Fish\n");
        printf("2. Add Dolphin\n");
        printf("3. Add Random Fish\n");
        printf("4. Exit to Main Menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
        {
            FreshFish* newFreshFish1 = createFreshFishFromUser();

            if (newFreshFish1 != NULL) {
                addFreshFish(freshAquarium, newFreshFish1);
                printf("Fresh fish added successfully!\n");
            }
            else {
                printf("Failed to create Fresh fish.\n");
            }
            break;
        }
        case 2:
        {
            // Update dolphin list with the returned value from getDolphinFromUser
            freshAquarium->dolphinDoublyLinkedList = getDolphinFromUser(freshAquarium->dolphinDoublyLinkedList);
            break;
        }
        case 3:
        {
            RandomFish* newRandomFish = createRandomFish();
            if (newRandomFish != NULL) {
                addRandomFish(freshAquarium, newRandomFish);
                printf("Random fish added successfully!\n");
            }
            else {
                printf("Failed to create random fish.\n");
            }
            break;
        }
        case 4:
            // Exit to Main Menu
            printf("Returning to Main Menu...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);
}







