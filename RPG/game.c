#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LINEBREAK printf("------------\n");
char fileBuffer[255];
char *gameChoices[32] = {"Notes", "Party","Dice Roll","Quit"};

void printGameChoices() {
  for (int i = 0; i < sizeof(gameChoices)/sizeof(gameChoices[0]); i++) {
    if (gameChoices[i] == NULL) {
      return;
    }
    else {
      printf("%d. %s\n",i,  gameChoices[i]);
    }
  }
}

void createPartyFile(FILE *fp) {
  fp = fopen("gameParty.txt", "w");

  fclose(fp);
}

int writePartyFile(FILE *fp, char *fileBuffer) {
  fp = fopen("gameParty.txt", "a");
  memset(fileBuffer, 0, strlen(fileBuffer));
  LINEBREAK;
  return 0;
}

void readPartyFile(FILE *fp) {
  fp = fopen("gameParty.txt", "r");
  int i = 0;

  while (fgets(fileBuffer, 255, fp) != NULL) {
    printf("%d. %s",i, fileBuffer);
    i++;
  }
  
  printf("\n%d. Add to party\n",i++);
  printf("%d. Remove from party\n", i++);
  printf("%d. Quit\n",i++);
  fclose(fp);
}

void removeParty(FILE *fp) {
  FILE *tmp;
  fp = fopen("gameParty.txt", "r");
  tmp = fopen("gamePartyTemp.txt", "w");
  int a;
  int delete_line = 0;
  bool reading = true;
  int current_line = 1;
  
  memset(fileBuffer, 0, strlen(fileBuffer));
  printf("Enter the line number of who you want to remove:\n");

  scanf("%d", &delete_line);

  do {
    fgets(fileBuffer, 255, fp);
    if (feof(fp)) {
      reading = false;
    }
    else if (current_line != delete_line) {
      fputs(fileBuffer, tmp);
    }
    current_line++;
  } while(reading);  
  
  fclose(fp);
  fclose(tmp);

  remove("gameParty.txt");
  rename("gamePartyTemp.txt", "gameParty.txt");

}

void addParty(FILE *fp) {
  fp = fopen("gameParty.txt", "a");
  
  memset(fileBuffer, 0, strlen(fileBuffer));
  printf("Enter who you wish to add to the party:\n");

  do {
    fgets(fileBuffer, 255, stdin);
    if (strcmp(fileBuffer, "\n") == 0) {
      printf("Stop");
      break;
    }
    fputs(fileBuffer, fp);
  } while(true);

  fclose(fp);
}

void createNoteFile(FILE *fp) {
  fp = fopen("gameNotes.txt", "w");  
  /* you must create a pointer to the file you want to create  */
  /* the second argument is the mode, "r" = read, "w" = write ,"a" = append  */
  fclose(fp);
}

int writeNoteFile(FILE *fp, char *fileBuffer) {
  fp = fopen("gameNotes.txt", "a");
  memset(fileBuffer, 0, strlen(fileBuffer)); 
  LINEBREAK;
  printf("Enter 'Quit' to exit.\n");
  
  do {
    fgets(fileBuffer, 255, stdin);
    if (strcmp(fileBuffer, "Quit\n") == 0) {
      return 1;
    }
    fputs(fileBuffer, fp);  
  } while(true);
  
  fclose(fp);
}

int readNoteFile(FILE *fp) {

  fp = fopen("gameNotes.txt", "r");
  
  while (fgets(fileBuffer, 255, fp) != NULL) {
    printf("%s", fileBuffer);
  }
  if (writeNoteFile(fp, fileBuffer) == 1) {
    return 1;
  }
}

int diceRoll(int roll, int side, int mod) {
  srand(time(NULL));
  
  int i;
  int result;

  for (roll; roll > 0; roll--) {
    result = rand() % side + 1;
    result += mod;
    printf("You have rolled a: %d\n", result);
  }
  
  return 0;
}
