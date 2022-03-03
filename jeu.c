//
//  jeu.c
//  jeu
//
#include "jeu.h"

typedef struct { // structure pour notre fonction verification
    int LX;
    int LO;
    int CX;
    int CO;
    int DX;
    int DO;
}compteur;

void videBuffer() // fonction qui vide le buffer pour pouvoir entrer une nouvelle valeur
{
    int vider = 0;
    while (vider != '\n' && vider != EOF)
       vider = getchar();
}

void CopieMatrice (char destmat[][7], char srcmat[][7]) // fonction qui copie une matrice dans une autre
{
  int i, j;
  for (i=0; i<7; i=i+1)
    for (j=0; j<7; j=j+1)
      destmat[i][j] = srcmat[i][j];
}

void init_grille(char grille[][7]){ // initialisation grille, on remplace tout élément par 0
    for (int i=0; i<7;i++){
        for (int j=0; j<7;j++){
            grille[i][j] = '0';
        }
    }
}

void affiche_grille(char grille[][7]){ // fonction qui affiche notre grile
    int c, l;
    printf(" _______________");
    for (l = 0; l < LIGNES; l++){
        printf("\n");
        printf(" %s", B_V);
        for (c = 0; c < COLONNES; c++){
            if (grille[c][l] == '0')
            printf(" %s", B_V);
            else
                printf("%c%s",grille[c][l], B_V);
            }
        }
    printf("\n _______________ \n");
    printf("  1 2 3 4 5 6 7 \n");
}
int max(int num1, int num2) // fonction qui determine le max entre deux nombres
{
    return (num1 > num2 ) ? num1 : num2;
}

int verification(char grille[][7]) // fonction qui vérifie et determine le maximum de jetons alignés
{
    compteur C;
    C.LX = 1;
    C.CX = 1;
    C.LO = 1;
    C.CO = 1;
    C.DX = 1;
    C.DO = 1;
    // COMPTEUR COLONNES 'X'
    for (int i=0; ((i <= 6) && (C.CX < 4));i++){
        for (int j=0; ((j < COLONNES));j++){
            if ((grille[i][j]== 'X') && (grille[i][j+1]== 'X') && (grille[i][j+2]== 'X') && (grille[i][j+3]== 'X')){
                C.CX=4;
            }
        }
    }
    // COMPTEUR COLONNES 'O'
    for (int i=0; ((i <= 6) && (C.CO < 4));i++){
        for (int j=0; ((j < COLONNES));j++){
            if ((grille[i][j]== 'O') && (grille[i][j+1]== 'O') && (grille[i][j+2]== 'O') && (grille[i][j+3]== 'O')){
                C.CO=4;
            }
        }
    }
    // Vérificateur lignes 'X'
    for (int i=0; ((i <= 6) && (C.LX < 4));i++){
        for (int j=0; ((j < LIGNES));j++){
            if ((grille[i][j]== 'X') && (grille[i+1][j]== 'X') && (grille[i+2][j]== 'X') && (grille[i+3][j]== 'X')){
                C.LX=4;
            }
        }
    }
    // Vérificateur lignes 'O'
    for (int i=0; ((i <= 6) && (C.LO < 4));i++){
        for (int j=0; ((j < LIGNES));j++){
            if ((grille[i][j]== 'O') && (grille[i+1][j]== 'O') && (grille[i+2][j]== 'O') && (grille[i+3][j]== 'O')){
                C.LO=4;
            }
        }
    }
    
    // Vérificateur diagonales / 'X'
    for (int i=0; ((i < 7) && (C.DX < 4)); i++){
        for (int j=0;(j < 7);j++){
            if ((grille[i][j]== 'X') && (grille[i+1][j+1]== 'X') && (grille[i+2][j+2]== 'X') && (grille[i+3][j+3]== 'X')){
                C.DX = 4;
             }
        }
    }
    
    // Vérificateur diagonales \ 'X'
    for (int i=6; ((3 <= i) && (C.DX < 4)); i--){
        for (int j=0;(j <= 5);j++){
            if ((grille[i][j]== 'X') && (grille[i-1][j+1]== 'X') && (grille[i-2][j+2]== 'X') && (grille[i-3][j+3]== 'X')){
                C.DX = 4;
             }
        }
    }
    // Vérificateur diagonales / 'O'
    for (int i=0; ((i < 7) && (C.DO < 4)); i++){
        for (int j=0;(j < 7);j++){
            if ((grille[i][j]== 'O') && (grille[i+1][j+1]== 'O') && (grille[i+2][j+2]== 'O') && (grille[i+3][j+3]== 'O')){
                C.DO = 4;
             }
        }
    }
    // Vérificateur diagonales \ 'O'
    for (int i=6; ((3 <= i) && (C.DO < 4)); i--){
        for (int j=0;(j <= 5);j++){
            if ((grille[i][j]== 'O') && (grille[i-1][j+1]== 'O') && (grille[i-2][j+2]== 'O') && (grille[i-3][j+3]== 'O')){
                C.DO = 4;
             }
        }
    }
    
    int n1 = max(C.LX, C.CX); // MAX DE JETONS X LIGNE ET COLONNE
    int n2 = max(C.LO, C.CO); // MAX DE JETONS O LIGNE ET COLONNE
    int maxX = max(n1, C.DX); // MAX X
    int maxO = max(n2, C.DO); // MAX O
    
    if ((maxX == 4) || (maxO == 4)){
        if ((maxX == 4) && (maxO == 4))
            return DRAW;
        else if (maxX > maxO)
            return J1;
        else if (maxO > maxX)
            return J2;
    }
    return OK;
    }

int grille_complete(char grille[][7]){ // retourne OK si la grille n'est pas complète, 0 sinon
    for (int i=0; (i < 7); i++){
        for (int j=0;(j < 7);j++){
            if (grille[i][j]=='0'){
                return OK;
            }
        }
        
    }
    return 0;
}

int etat_jeu(char grille[][7]){ // ve
    if ((grille_complete(grille) == OK)){ // si grille pas complete
        if (verification(grille) == OK) // pas de gagnant déclaré on retourne OK
            return OK;
        else if (verification(grille) == J1) // si gagnant J1 on le retourne
            return J1;
        else if (verification(grille) == J2) // si gagnant J2 on le retourne
            return J2;
        else if (verification(grille) == DRAW) // si égalité on retourne égalité
            return DRAW;
    } else if (grille_complete(grille) == 0){ // si grille complete on reinitialise
        return RESTART;
    }
    return 0;
}

void FlipLeft(char grille[][7]) {// rotation à gauche
    char temp[7][7];
    for (int i=6; i>=0;i--){
        for (int j=6; j>=0;j--){
            temp[j][6-i] = grille[i][j];
        }
    }
    for (int k=0;k<7;k++){ // 3eme boucle pour faire descendre tous les elements
        for (int i=0;i<7;i++){
            for (int j=5;j>=0;j--){
                char cle = temp[i][j];
                if (temp[i][j+1] == '0'){
                    temp[i][j+1] = cle;
                    temp[i][j] = '0';
                }
            }
        }
    }
    CopieMatrice(grille, temp);
}

void FlipRight(char grille[][7]) { // rotation a droite
    char temp[7][7];
    for (int i=6; i>=0;i--){
        for (int j=6; j>=0;j--){
            temp[6-j][i] = grille[i][j];
        }
    }
    for (int k=0;k<7;k++){ // 3eme boucle pour faire descendre tous les elements
        for (int i=0;i<7;i++){
            for (int j=5;j>=0;j--){
                char cle = temp[i][j];
                if (temp[i][j+1] == '0'){
                    temp[i][j+1] = cle;
                    temp[i][j] = '0';
                }
            }
        }
    }
    CopieMatrice(grille, temp);
}

void Flip(char grille[][7]) { // retourner la grille
    char temp[7][7];
    CopieMatrice(temp, grille);
    for (int i=6; i>=0;i--){
        for (int j=6; j>=0;j--){
            temp[i][6-j] = grille[i][j];
        }
    }
    for (int k=0;k<7;k++){ // 3eme boucle pour faire descendre tous les elements
        for (int i=0;i<7;i++){
            for (int j=5;j>=0;j--){
                char cle = temp[i][j];
                if (temp[i][j+1] == '0'){
                    temp[i][j+1] = cle;
                    temp[i][j] = '0';
                }
            }
        }
    }
    CopieMatrice(grille, temp);
}

void sauver(char grille[][7], char nom[50],char m){ // prend le nom du fichier et le mode de jeu en paramètre
    FILE *fp = fopen(nom, "w+");
    if (fp == NULL) {
        printf("Erreur de sauvegarde.\n");
    }
    fprintf(fp, "%d", m);
    for (int i=0; i<7; i++){
        for(int j=0; j<7; j++){
                fprintf(fp, "%c",grille[i][j]);
            }
        }
    fclose(fp);
}

int etat_colonne(int i,char grille[][7]){ // verifie si colonne est pleine
    char temp[7][7];
    CopieMatrice(temp, grille);
    for (int j=6; j>=0;j--){
        if (temp[i][j] == '0')
            return OK;
        }
    return NOT_OK;
}

int action(char grille[][7], char J, char m){ // J = Jeton, m = mode de jeu
    char coup;
    scanf("%c", &coup);
    if (coup == 'g'){
        printf("Grille tournée de 90° sur la gauche par J(%c)\n",J);
        FlipLeft(grille);
    }else if (coup == 'd'){
        printf("Grille tournée de 90° sur la droite par J(%c)\n",J);
        FlipRight(grille);
    }else if (coup == 'r'){
        printf("Grille retournée par J(%c)\n",J);
        Flip(grille);
    }else if (coup == 'q')
        return QUIT;
    else if (coup == 's'){
        printf("Nom du fichier de sauvegarde:");
        scanf("%s", nom);
        sauver(grille, nom, m);
        printf("Partie sauvegardée. \n");
        videBuffer();
        return action(grille,J,m);
    }else {
        int i = 6;
        while ((i>=0)){
            if (etat_colonne(atoi(&coup)-1, grille) == OK) {
                if (grille[atoi(&coup)-1][i] == '0'){
                    grille[atoi(&coup)-1][i] = J;
                    break;
                }
            }
            else if (etat_colonne(atoi(&coup)-1, grille) == NOT_OK)
                return NOT_OK;
            i--;
        }
    }
    return OK;
}

int actionIA(char grille[][7], char J){
    char coups[10] = {'1','2','3','4','5','6','7','g','d','r'}; // coups possibles par l'IA
    time_t t;
    srand((unsigned) time(&t));
    char k = coups[rand() % 9]; // coup aléatoire
    if (k == 'g'){
        printf("Grille tournée de 90° sur la gauche par IA(%c)\n",J);
        FlipLeft(grille);
    }else if (k == 'd'){
        printf("Grille tournée de 90° sur la droite par IA(%c)\n",J);
        FlipRight(grille);
    }else if (k == 'r'){
        printf("Grille retournée par IA\n");
        Flip(grille);
    }else {
        int i = 6;
        while ((i>=0)){
            if (etat_colonne(atoi(&k)-1, grille) == OK) {
                if (grille[atoi(&k)-1][i] == '0'){
                    grille[atoi(&k)-1][i] = J;
                    break;
                }
            }
            else if (etat_colonne(atoi(&k)-1, grille) == NOT_OK)
                return NOT_OK;
            i--;
        }
    }
    return OK;
}

int HvIA(char grille[][7]){
    int joueur, c;
    printf("1 pour jouer avec X, 2 pour O \n");
    scanf("%d", &c);
    videBuffer();
    char pionH, pionIA, m=2;
    if (c == 1){
        joueur=1;pionH='X';pionIA='O';
    }
    else{
        joueur=2;pionH='O';pionIA='X';
    }
    while (etat_jeu(grille) == OK){
        affiche_grille(grille);
                printf("Joueur %d c'est votre tour \n", joueur);
                int o = action(grille,pionH,m);
                if (o == OK){
                    videBuffer();
                    joueur--;
                }else if(o  == NOT_OK){
                    printf("Coup invalide, rejouez \n");
                    videBuffer();
                }else if(o == QUIT){
                    videBuffer();
                    return QUIT;
            }
                int x = actionIA(grille,pionIA);
                if (x == OK){
                    joueur++;
                }else if(x  == NOT_OK){
                    x = actionIA(grille,pionIA);
                    x = 0;
            }
        }
    affiche_grille(grille);
    
    if (etat_jeu(grille) == J1){
        printf("Joueur 1 a gagné\n");
        printf("\n");
        return J1;
    }else if (etat_jeu(grille) == J2){
        printf("Joueur 2 a gagné\n");
        printf("\n");
        return J2;
    }else if (etat_jeu(grille) == DRAW){
        printf("Égalité.. retour au menu \n");
        printf("\n");
        return DRAW;
    }else if (etat_jeu(grille) == RESTART){
        printf("Grille complète.. reinitialisation");
        return NOT_OK;
    }
    return OK;
}

int humain(char grille[][7]){ // fonction qui gère le mode Humain vs Humain
    int joueur;
    printf("1 pour jouer avec X, 2 pour O \n");
    int c;
    scanf("%d", &c);
    videBuffer();
    if (c == 1)
        joueur=1;
    else
        joueur=2;
    
    while (etat_jeu(grille) == OK){
        affiche_grille(grille);
            if (joueur%2 == 0){
                printf("Joueur %d c'est votre tour \n", joueur);
                int o = action(grille,'O',1);
                if (o == OK){
                    videBuffer();
                    joueur--;
                }else if(o  == NOT_OK){
                    printf("Coup invalide, rejouez \n");
                    videBuffer();
                }else if(o == QUIT){
                    videBuffer();
                    return QUIT;
                }
            }
            else{
                printf("Joueur %d c'est votre tour \n", joueur);
                int x = action(grille,'X',1);
                if (x == OK){
                    videBuffer();
                    joueur++;
                }else if(x  == NOT_OK){
                    printf("Coup invalide, rejouez \n");
                    videBuffer();
                }else if(x == QUIT){
                    videBuffer();
                    return QUIT;
                }
        }
    }
    affiche_grille(grille);
    
    if (etat_jeu(grille) == J1){
        printf("Joueur 1 a gagné \n");
        printf("\n");
        return J1;
    }else if (etat_jeu(grille) == J2){
        printf("Joueur 2 a gagné \n");
        printf("\n");
        return J2;
    }else if (etat_jeu(grille) == DRAW){
        printf("Égalité.. retour au menu \n");
        printf("\n");
        return DRAW;
    }else if (etat_jeu(grille) == RESTART){
        printf("Grille complète.. reinitialisation");
        return NOT_OK;
    }
    return OK;
}

int lecture(char fichier[50]){ // lecture de la sauvegarde
    char matrice[7][7];
    int i, j;
    char m;
    FILE *fp = fopen(fichier,"r");
    if (fp == NULL){
        printf("Sauvegarde inexistante. \n");
        return NOT_OK;
    }
    fscanf(fp, "%c", &m); // 1er caractère du fichier = mode de jeu qu'on stocke dans la var m
    while (!feof(fp)){
        for (i=0; i<7;i++){
            for (j=0; j<7; j++){
                fscanf(fp, "%c", &matrice[i][j]);
            }
        }
    }
    fclose(fp);
    if (m == '1'){ // on evalue le premier caractère
        affiche_grille(matrice);
        return humain(matrice);
    }else if (m == '2'){
        affiche_grille(matrice);
        return HvIA(matrice);
    }
    affiche_grille(matrice);
    return OK;
}

int IAvIA(char grille[][7]){
    int joueur = 1;
    char c;
    printf("Appuyez sur une touche pour lancer la partie\n");
    scanf("%c", &c);
    videBuffer();
    char pionIA1 = 'X';
    char pionIA2 = 'O';
    while (etat_jeu(grille) == OK){
        affiche_grille(grille);
        printf("Tour de %d - appuyez pour jouer \n", joueur);
        scanf("%c",&c);
        if (c == 'q'){
            videBuffer();
            return QUIT;
        }
        else if (joueur%2 == 0){
            int o = actionIA(grille,pionIA2);
            if (o == OK){
                joueur--;
            }else if(o  == NOT_OK){
                o = actionIA(grille,pionIA2);
            }
            o = 0;
        }
        else{
            int x = actionIA(grille,pionIA1);
            if (x == OK){
                joueur++;
            }else if(x  == NOT_OK){
                x = actionIA(grille,pionIA1);
            }
            x=0;
        }
    }
    affiche_grille(grille);
    
    if (etat_jeu(grille) == J1){
        printf("Joueur 1 a gagné");
        return J1;
    }else if (etat_jeu(grille) == J2){
        printf("Joueur 2 a gagné");
        return J2;
    }else if (etat_jeu(grille) == DRAW){
        printf("Égalité.. retour au menu");
        return DRAW;
    }else if (etat_jeu(grille) == RESTART){
        printf("Grille complète.. reinitialisation");
        return NOT_OK;
    }
    return OK;
}

void manuel(){ // fonction manuel
    printf("\n1 à 7 pour placer dans une colonne");
    printf("\n'd' pour tourner la grille 90° à droite \n'g' pour tourner la grille 90° à gauche");
    printf("\n'r' pour retourner la grille\n's' sauvegarder partie \n'q' pour quitter \n");
}

int menu(char grille[][7]) {
    printf("\n1 pour Humain vs Humain \n2 pour Humain vs IA\n3 pour IA vs IA \n");
    printf("4 pour charger sauvegarde\n");
    printf("m pour manuel\n");
    printf("Réponse:");
    
    int choix = getchar();
    if(choix == '1')
       return humain(grille);
    else if (choix == '2')
       return HvIA(grille);
    else if (choix == '3')
       return IAvIA(grille);
    else if (choix == '4')
       return lecture(nom);
    else if (choix == 'q'){
        videBuffer();
       printf("Merci d'avoir joué\n");
        return 0;
    }
    else if (choix == 'm'){
        manuel();
        videBuffer();
    }else
        printf("Erreur de saisie du choix\n");
    return OK;
}

int jeu(){
    char grille[7][7] = {{'0','0','0','0','0','0','0'},{'0','0','0','0','0','0','0'}, {'0','0','0','0','0','0','0'}, {'0','0','0','0','0','0','0'}, {'0','0','0','0','0','0','0'}, {'0','0','0','0','0','0','0'}, {'0','0','0','0','0','0','0'}};
    int partie = menu(grille);
    if (partie == 0)
        return 0;
    else{
        init_grille(grille);
        jeu();
    }
    return OK;
}
