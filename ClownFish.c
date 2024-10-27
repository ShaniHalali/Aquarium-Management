#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClownFish.h"

#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WARNINGS


void getClownFishFromUser(ClownFish* fish) {
    printf("Enter name: ");
    scanf("%49s", fish->name);

    fish->seaCreature.age = getValidAge();

    fish->seaCreature.lifeSpan = getValidLifeSpan(fish->seaCreature.age);

    getValidColors(&fish->seaCreature);
}



ClownFish* createClownFish(const char* name, int age, int lifeSpan, eSeaCreatureColor color1, eSeaCreatureColor color2) {
    ClownFish* result = (ClownFish*)calloc(1, sizeof(ClownFish));
    if (!result) {
        printf("Memory allocation failed for ClownFish.\n");
        return NULL;
    }

    strncpy(result->name, name, sizeof(result->name) - 1);
    result->name[sizeof(result->name) - 1] = '\0';

    result->seaCreature.age = age;
    result->seaCreature.lifeSpan = lifeSpan;
    result->seaCreature.color1 = color1;
    result->seaCreature.color2 = color2;

    return result;
}

void writeClownFishToFile(ClownFish* fish, FILE* file) {

    fprintf(file, "%s,%d,%d,%d,%d\n",  fish->name,fish->seaCreature.age, fish->seaCreature.lifeSpan, fish->seaCreature.color1, fish->seaCreature.color2);
}

ClownFish* readClownFishFromFile(FILE* file) {

    ClownFish* clownFish = (ClownFish*)calloc(1, sizeof(ClownFish));
    if (clownFish == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    if (fscanf(file, "%49[^,],%d,%d,%d,%d\n",  clownFish->name, &clownFish->seaCreature.age, &clownFish->seaCreature.lifeSpan, (int*)&clownFish->seaCreature.color1, (int*)&clownFish->seaCreature.color2) != 5) {

    }
    return clownFish;
}
void writeCompressedClownFishToBinaryFile(ClownFish* fish, FILE* file) {
    if (!fish || !file) {
        printf("Invalid ClownFish or file pointer\n");
        return;
    }

    unsigned short packedData = 0;  // 16-bit to hold packed data
    packedData |= (fish->seaCreature.age & 0x1F);  // Age uses the first 5 bits
    packedData |= (fish->seaCreature.lifeSpan & 0x1F) << 5;  // LifeSpan next 5 bits
    packedData |= (fish->seaCreature.color1 & 0x07) << 10;  // color1 next 3 bits
    packedData |= (fish->seaCreature.color2 & 0x07) << 13;  // color2 last 3 bits

    fwrite(&packedData, sizeof(unsigned short), 1, file);

    unsigned char nameLength = (unsigned char)strlen(fish->name);
    fwrite(&nameLength, sizeof(unsigned char), 1, file);
    fwrite(fish->name, sizeof(char), nameLength, file);
}

ClownFish* readCompressedClownFishFromBinaryFile(FILE* file) {
    if (!file) {
        printf("Invalid file pointer\n");
        return NULL;
    }

    ClownFish* fish = (ClownFish*)calloc(1, sizeof(ClownFish));
    if (!fish) {
        printf("Memory allocation failed for ClownFish\n");
        return NULL;
    }

    unsigned short packedData = 0;
    fread(&packedData, sizeof(unsigned short), 1, file);


    fish->seaCreature.age = packedData & 0x1F;  // Extract the first 5 bits for age
    fish->seaCreature.lifeSpan = (packedData >> 5) & 0x1F;  // Next 5 bits for lifespan
    fish->seaCreature.color1 = (packedData >> 10) & 0x07;  // Next 3 bits for color1
    fish->seaCreature.color2 = (packedData >> 13) & 0x07;  // Last 3 bits for color2


    unsigned char nameLength = 0;
    fread(&nameLength, sizeof(unsigned char), 1, file);
    fread(fish->name, sizeof(char), nameLength, file);
    fish->name[nameLength] = '\0';

    return fish;
}