//
//  jeu.h
//  jeu
//


#ifndef p4_h
#define p4_h
#define COLONNES (7)
#define LIGNES (7)

#define PIECE1 ('X')
#define PIECE2 ('O')
#define B_V "|"
#define B_H "_"
#define J1 (1)
#define J2 (2)
#define DRAW (3)
#define OK (4)
#define NOT_OK (5)
#define RESTART (99)
#define QUIT (98)
#define CLOSE (97)

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

static char nom[20];

void videBuffer(void);

void CopieMatrice (char destmat[][7], char srcmat[][7]);

void init_grille(char grille[][7]);

void affiche_grille(char grille[][7]);
int max(int num1, int num2);

int verification(char grille[][7]);

int grille_complete(char grille[][7]);

int etat_jeu(char grille[][7]);

void FlipLeft(char grille[][7]);

void FlipRight(char grille[][7]);

void Flip(char grille[][7]);

void sauver(char grille[][7], char nom[50],char m);

int etat_colonne(int i,char grille[][7]);

int action(char grille[][7], char J, char m);

int actionIA(char grille[][7], char J);

int HvIA(char grille[][7]);

int humain(char grille[][7]);

int lecture(char fichier[50]);

int IAvIA(char grille[][7]);

void manuel(void);

int menu(char grille[][7]);

int jeu(void);


#endif /* jeu_h */
