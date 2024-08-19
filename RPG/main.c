#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.c"

#define MAXLEN 100

#define CLEAR system("cls")
#define LINEBREAK printf("------------\n");

int main(void);
void gameMenu(void);
void diceRollInput(void);
void printMenu(void);
void clearBuffer(void);
void partyMenu(void);

/* Data */
char buffer[MAXLEN]; /* user input line  */
int bufferPos = 0;


void clearBuffer() {
  memset(buffer,0, strlen(buffer));
}

void printMenu() {
  char choices[][15] = {"Game","Quit"};
   for(int i = 0; i < sizeof(choices)/sizeof(choices[0]); i++) {
     printf("%d. %s\n", i, choices[i]);
   }
}

void diceRollInput() {
  int rolls;
  int sides;  
  int mod;
  clearBuffer();
  LINEBREAK; 
  printf("How many rolls?: ");
  rolls = atoi(fgets(buffer, MAXLEN, stdin));
  clearBuffer();
  printf("How many sides?: ");
  sides = atoi(fgets(buffer, MAXLEN, stdin));
  clearBuffer();
  printf("Any roll modifiers? (0 if no): ");
  mod = atoi(fgets(buffer, MAXLEN, stdin));
  clearBuffer();
  CLEAR;
  LINEBREAK;
  diceRoll(rolls, sides, mod);
  LINEBREAK;
  gameMenu();
}

void partyInput(FILE *fp) {
  clearBuffer();
  fgets(buffer,MAXLEN, stdin);
  if (strcmp(buffer, "Add to party\n") == 0) {
    LINEBREAK;
    clearBuffer();
    addParty(fp);
    CLEAR;
    partyMenu();
  }
  if (strcmp(buffer, "Remove from party\n") == 0) {
    LINEBREAK;
    clearBuffer();
    removeParty(fp);
    CLEAR;
    partyMenu();
  }
  if (strcmp(buffer, "Quit\n") == 0) {
    CLEAR;
    gameMenu();
  }
}

/* cant remove or rename file as gameParty is still in an open state from this function below */

void partyMenu() {
  CLEAR;
  printf("Party Menu\n");
  LINEBREAK;

  FILE *fp;
  fp = fopen("gameParty.txt", "r");
  if (fp == NULL) {
    createPartyFile(fp);
  }
  fclose(fp);
  readPartyFile(fp);
  clearBuffer();
  LINEBREAK;
  partyInput(fp);
}

void gameMenu() {
  printf("Game Menu\n");
  LINEBREAK;
  clearBuffer();
  printGameChoices();
  LINEBREAK;
  fgets(buffer, MAXLEN, stdin);
  
  if (strcmp(buffer, "Notes\n") == 0) {
    FILE *fp;
    fp = fopen("gameNotes.txt", "r");
    if (fp == NULL) {
      createNoteFile(fp);
    }
    LINEBREAK;
    if (readNoteFile(fp) == 1) {
      CLEAR;
      gameMenu();
    }
  }

  if (strcmp(buffer, "Party\n") == 0) {
    CLEAR;
    partyMenu();
  }
  
  if (strcmp(buffer, "Dice Roll\n") == 0) {
    diceRollInput();
  }
  
  if (strcmp(buffer, "Quit\n") == 0) {
    main();
  }
}
int main() {
  CLEAR;
  printf("RPG Helper\n");
  LINEBREAK;
  printMenu();
  LINEBREAK;
  
  fgets(buffer, MAXLEN, stdin);
  
  if (strcmp(buffer, "Game\n") == 0) {
    CLEAR;
    gameMenu();
  }
  if (strcmp(buffer, "Quit\n") == 0) {
    CLEAR;
    exit(0);
  }
}

