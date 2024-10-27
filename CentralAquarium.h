#include "FreshAquarium.h"
#include "SaltAquarium.h"
#define MAX_NAME_LENGTH 255

typedef struct CentralAquarium 
{

	FreshAquarium* freshAquarium;
	SaltAquarium* saltAquarium;
	char* name;
} CentralAquarium;


CentralAquarium* initCentralAquarium(char* name);

//Txt
CentralAquarium* readCentralAquariumFromTxtFile(char* fileName);
void writeCentralAquariumToTxtFile(CentralAquarium* ca, char* fileName);
//Binary
void writeCentralAquariumToBinaryFile(CentralAquarium* aquarium, char* fileName);
CentralAquarium* readCentralAquariumFromBinaryFile(char* fileName);
void printAllCentralAquariumDetails(CentralAquarium* aquarium);
void freeCentralAquarium(CentralAquarium* ca);

