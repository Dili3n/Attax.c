/**
 * @file main.c
 * @author OEUVRARD & NGUYEN
 * @brief 
 * @version 1.0
 * @date 2021-12-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#define TAILLE_PLATEAU 7
#define TAILLE_MAX_NOM 20
#define TAILLE_CASE_GRAPH 40
#define TAILLE_MARGE_GRAPH 10

#define PROBA 4

#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <time.h>

// gcc -std=c17 -Wall NGUYE_OEUVR_ATTAXX.c -o NGUYE_OEUVR_ATTAXX -lMLV

// STRUCTURES

typedef struct {
    char nom[TAILLE_MAX_NOM];
    char symbol;
    int score;
} Joueur;


typedef struct {
    char plateau[TAILLE_PLATEAU + 2][TAILLE_PLATEAU + 2];
    Joueur * joueur[2];
} Plateau;

// FONCTIONS 

/**
 * @brief 
 * Fonction de saut de ligne pour éviter
 * que d'avoir des \n par milliers dans le code.
 * 
 * @param nb 
 * Le nombre de ligne à sauter.
 */
void End(int nb){
    int i;
    for (i = 0; i < nb; i++)
        printf("\n");
}

/**
 * @brief 
 * Fonction qui initialise un joueur,
 * avec son nom, son score et symbole.* 
 * 
 * @param j 
 * Effet de bord en modifiant la structure
 * joueur, dans laquelle sera modifié le nom,
 * score et symbole.
 * @param sym 
 * char sym:
 *  il existe deux symboles, pour pouvoir les
 *  disserner on utilise un argument char sym.
 */
void InitJoueur(Joueur * j, char sym){

    printf("Quel est le nom du joueur (symbol %c) : ",sym);
    scanf("%s", j -> nom);
    j -> symbol = sym;
    j -> score = 0;
}

/**
 * @brief 
 * Fonction qui initialise un BOT,
 * comme pour la fonction Joueur.
 * 
 * @param j 
 * Cette fonction est comme la fonction
 * InitJoueur.
 */
void InitBot(Joueur * j){

    int i;
    char nom_ordi[4] = {'B', 'O', 'T', '\0'};
    for (i = 0; nom_ordi[i] != '\0'; i++){
        j -> nom[i] = nom_ordi[i];
    }
    j -> nom[i] = nom_ordi[i];
    j -> symbol = 'x';
    j -> score = 0;
}

/**
 * @brief
 * Fonction qui initialise le plateau
 * grace à sa taille.
 * 
 * @param plat 
 * Effet de bord en modifiant la structure
 * Plateau, dans laquelle sera modifié le 
 * double tableau permettant de créer un 
 * plateau de jeu.
 */
void InitPlateau(Plateau * plat){

    int x, y;
    for (x = 0; x < TAILLE_PLATEAU + 3; x++){
        for (y = 0; y < TAILLE_PLATEAU + 3; y++){
            if (x == 0 || x == TAILLE_PLATEAU + 1 ||
                y == 0 || y == TAILLE_PLATEAU + 1)
                    plat -> plateau[x][y] = '*';
            else if (x == TAILLE_PLATEAU + 2)
                plat -> plateau[x][y] = ' ';
            else
                plat -> plateau[x][y] = '.';
            
        }
    }
    plat -> plateau[1][1] = 'x';
    plat -> plateau[TAILLE_PLATEAU][TAILLE_PLATEAU] = 'x';
    plat -> plateau[1][TAILLE_PLATEAU] = 'o';
    plat -> plateau[TAILLE_PLATEAU][1] = 'o';
    
}

/**
 * @brief 
 * Affiche le plateau grace à un 
 * printf.
 * 
 * @param plat 
 *  Plateau * plat:
 *  lit la structure Plateau, du double tableau plateau. 
 */
void AffichePlateau(Plateau * plat){

    int x, y;
    for (x = 0; x < TAILLE_PLATEAU + 2; x++){
        End(1);
        for (y = 0; y < TAILLE_PLATEAU + 2; y++){
        printf("%c ", plat -> plateau[x][y]);
        }
    }
}

/**
 * @brief 
 * Dans la partie graphique, cette fonction
 * dessine un pion
 * 
 * @param x 
 * les positions à laquelle les pions doivent
 * être placés.
 * @param y 
 * les positions à laquelle les pions doivent
 * être placés.
 * @param couleur 
 * Pour la couleur du pion.
 */
void DessinePion(int x, int y, MLV_Color couleur){

    int x_centre, y_centre;
    x_centre = TAILLE_MARGE_GRAPH + (TAILLE_CASE_GRAPH / 2) + (TAILLE_CASE_GRAPH * x) + TAILLE_CASE_GRAPH;
    y_centre = TAILLE_MARGE_GRAPH + (TAILLE_CASE_GRAPH / 2) + (TAILLE_CASE_GRAPH * y) + TAILLE_CASE_GRAPH * 2;
    MLV_draw_filled_circle( x_centre, y_centre, (TAILLE_CASE_GRAPH / 2) - 5, couleur );
}

/**
 * @brief 
 * fait appel à la fonction DessinePion
 * pour dessiner tous les pions de la bonne couleur
 * 
 * @param plat 
 * Lit le symbol qui se trouve à telle 
 * coordonnée.
 */
void AffichePionsGraph(Plateau * plat){

    int x, y;
    MLV_Color couleur;
    for (x = 0; x < TAILLE_PLATEAU + 2; x++){
        for (y = 0; y < TAILLE_PLATEAU + 2; y++){
            if (plat -> plateau[x][y] == 'o'){
                couleur = MLV_COLOR_WHITE;
                DessinePion(x-1, y-1, couleur);
            }
            else if (plat -> plateau[x][y] == 'x'){
                couleur = MLV_COLOR_BLACK;
                DessinePion(x-1, y-1, couleur);
            }
        }
    }
}

/**
 * @brief 
 * Affiche graphiquement le nom du joueur en train de joué.
 * 
 * @param j 
 * lit le nom du joueur j.
 */
void AfficheNomJoueur(Joueur * j){

    int x = TAILLE_MARGE_GRAPH;
    int y = TAILLE_MARGE_GRAPH;
    MLV_draw_adapted_text_box(
        x, y,
        j->nom,
        5,
        MLV_COLOR_WHITE, //contour du rectangle
        MLV_COLOR_WHITE, //mots
        MLV_COLOR_BLACK, //fond
        MLV_TEXT_LEFT
    );
}

/**
 * @brief 
 * Fonction qui initialise les textes 
 * de l'affichage graphique du plateau.
 */
void AfficheTextePlateauGraph(void){

    int coord, i;
    char lettre[2];
    char chiffre[2];
    lettre[1] = 0;
    chiffre[1] = 0;
    for (i = 0; i < TAILLE_PLATEAU; i++){
        coord = TAILLE_MARGE_GRAPH + (TAILLE_CASE_GRAPH * i);
        lettre[0] = 0x61 + i; //0x61 code ASCII de 'a'
        chiffre[0] = 0x31 + i; //0x31 code ASCII de '1'
        MLV_draw_adapted_text_box(
            TAILLE_MARGE_GRAPH, coord + TAILLE_CASE_GRAPH * 2,
            (const char *)&chiffre, 
            10,
            MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK,
            MLV_TEXT_CENTER
        );

        MLV_draw_adapted_text_box(
            coord + TAILLE_CASE_GRAPH, TAILLE_MARGE_GRAPH + TAILLE_CASE_GRAPH,
            (const char*)&lettre,
            10,
            MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_COLOR_BLACK,
            MLV_TEXT_CENTER
        );
    }
}

/**
 * @brief 
 * Fonction qui initialise graphiquement l'affichage du plateau
 * (lignes, fond).
 *
 * @param plat 
 * 
 */
void AffichePlateauGraph(Plateau * plat){

    int coord;
    int i;
    int larg_haut = TAILLE_CASE_GRAPH * TAILLE_PLATEAU;
    MLV_draw_filled_rectangle(TAILLE_MARGE_GRAPH + TAILLE_CASE_GRAPH,
    TAILLE_MARGE_GRAPH + TAILLE_CASE_GRAPH * 2,
    larg_haut, larg_haut, MLV_COLOR_FOREST_GREEN);

    for (i = 0; i < TAILLE_PLATEAU+1; i++){
        coord = TAILLE_MARGE_GRAPH + (TAILLE_CASE_GRAPH * i) + TAILLE_CASE_GRAPH;
        MLV_draw_line(coord, TAILLE_MARGE_GRAPH + TAILLE_CASE_GRAPH * 2,
        coord, TAILLE_MARGE_GRAPH + larg_haut + TAILLE_CASE_GRAPH * 2,
        MLV_COLOR_WHITE);
        MLV_draw_line(TAILLE_MARGE_GRAPH + TAILLE_CASE_GRAPH,
        coord + TAILLE_CASE_GRAPH,
        TAILLE_MARGE_GRAPH + larg_haut + TAILLE_CASE_GRAPH,
        coord + TAILLE_CASE_GRAPH, MLV_COLOR_WHITE);
    }
}

/**
 * @brief 
 * Fonction d'appel pour la fonction
 * InitJoueur ou InitBot.
 * @param j1 
 * @param j2 
 * @param bot 
 */
void InitJeu(Joueur * j1, Joueur * j2, int bot){

    InitJoueur(j1, 'o');
    if (bot == 0)
        InitJoueur(j2, 'x');
    else
        InitBot(j2);
    
}

/**
 * @brief 
 * Fonction qui affiche le score en ASCII.
 * 
 * @param plat 
 * Pour lire les symbols sur le plateau.
 * @param j 
 * Effet de bord en modifiant le score d'un joueur.
 * @param ascii 
 * Mode ascii 1 ou 0.
 */
void Score(Plateau * plat, Joueur * j, int ascii){

    int x, y;
    j -> score = 0;
    for (x = 0; x < TAILLE_PLATEAU + 2; x++){
        for (y = 0; y < TAILLE_PLATEAU + 2; y++){
            if (plat -> plateau[x][y] == j -> symbol)
                j -> score ++;
        }
    }

    if (ascii == 1){
        if (j -> symbol == 'o')
            printf("\nScore actuel : ");
        printf("%s(%c) %d", j -> nom, j -> symbol, j -> score);
        if (j -> symbol == 'o')
            printf(" - ");
    }
}

/**
 * @brief 
 * Affiche graphiquement le score des joueurs.
 * 
 * @param j1 
 * lit le nom du joueur j1 et son score.
 * @param j2 
 * lit le nom du joueur j2 et son score.
 */
void AfficheScoreGraph(Joueur * j1, Joueur * j2){

    int larg_haut = (TAILLE_CASE_GRAPH * TAILLE_PLATEAU) + (TAILLE_MARGE_GRAPH * 2) + TAILLE_CASE_GRAPH;
    int taille = TAILLE_MAX_NOM * 3;
    char score[taille];
    int x;
    int y;
    int width_box, height_box;
    sprintf(score, "%s: %d\n%s: %d", j1->nom, j1->score, j2->nom, j2->score);

    MLV_get_size_of_adapted_text_box(
		score,
		5,
		&width_box, &height_box
	);

    x = larg_haut - width_box - TAILLE_MARGE_GRAPH;
    y = TAILLE_MARGE_GRAPH;

    MLV_draw_adapted_text_box(
            x, y,
            score,
            5,
            MLV_COLOR_BLACK, //contour du rectangle
            MLV_COLOR_WHITE, //mots
            MLV_COLOR_BLACK, //fond
            MLV_TEXT_RIGHT
    );
}

/**
 * @brief 
 * Fonction qui vérifie s'il il est possible
 * de poser un piont à tel point. 
 * 
 * @param plat 
 * Utile pour lire quel symbol est sur telle case
 * @param j 
 * Pour récupérer le symbol du joueur
 * @param x 
 * les coordonnées du clic.
 * @param y 
 * les coordonnées du clic.
 * @return int 
 */
int VerifCoo(Plateau * plat, Joueur * j, int x , int y){

    int i, k;
    if (TAILLE_PLATEAU < x || x < 0){
        return 0;
    }
    if (TAILLE_PLATEAU < y || y < 0){
        return 0;
    }

    if (plat -> plateau[x][y] == '.') 
        for (i = -1; i < 2; i++){
            for (k = -1; k < 2; k++){

            if (plat -> plateau[i + x][k + y] != '.' && plat -> plateau[i + x][k + y] != '*' &&
                plat -> plateau[i + x][k + y] != j -> symbol)
                return 1;
            }
        }
    return 0;
}

/**
 * @brief 
 * Change le symbole des pions voisins 
 * en fonction des coordonnés entrées en paramètre 
 * après avoir vérifié si c'était possible.
 * 
 * @param plat 
 * Effet de bord : changement de telle coordonnée
 * par le symbole d'un joueur. 
 * @param j 
 * @param x 
 * @param y 
 * @param prop 
 */
void ChangeCoo(Plateau * plat, Joueur * j, int x , int y, int prop){

    int i, k;
    srand(time(NULL));

    for (i = -1; i < 2; i++){
        for (k = -1; k < 2; k++){
            if (prop == 1){
                int random = rand() % PROBA;
                if (plat -> plateau[i + x][k + y] != '.' && plat -> plateau[i + x][k + y] != '*' && random < 3)
                plat -> plateau[i + x][k + y] = j -> symbol;
            } else {
                if (plat -> plateau[i + x][k + y] != '.' && plat -> plateau[i + x][k + y] != '*')
                plat -> plateau[i + x][k + y] = j -> symbol;
            }
        }
    }
}

/**
 * @brief 
 * Fonction qui calcule LA PUISSSSANCE d'un bot
 * et prend la position qui l'avantage le plus.
 * 
 * @param plat 
 * Lire le symbole à tel point.
 * @param x 
 * Coordonnées.
 * @param y 
 * Coordonnées.
 * @param puissance 
 * indice de la puissance de X, Y
 * @return int 
 */
int BotPuissance(Plateau * plat, int x, int y, int puissance){

    int i, k;
    for (i = -1; i < 2; i++){
        for (k = -1; k < 2; k++){
            if (plat -> plateau[i + x][k + y] == 'o')
                puissance ++;
        }
    }
    return puissance;

}

/**
 * @brief 
 * Fonction qui crée les messages en
 * cas de victoire.
 * 
 * @param j1 
 * Lit les scores des duex joueurs pour les comparer.
 * @param j2 
 * Lit les scores des duex joueurs pour les comparer.
 * @return int 
 * 0 si tout c'est bien passé.
 */
int Gagnant(Joueur * j1, Joueur * j2){

    if (j1 -> score > j2 -> score || j2 -> score == 0)
        printf(" %s, vous avez gagné %d à %d.\n", j1 -> nom, j1 -> score, j2 -> score);
    else if (j1 -> score < j2 -> score || j1 -> score == 0)
        printf("Bravo %s, vous avez gagné %d à %d.\n", j2 -> nom, j2 -> score, j1 -> score);
    else
        printf("égalité ! Personne gagne !\n");
    return 0;
}

/**
 * @brief 
 * Fonction qui vérifie si il est encore
 * possible de jouer
 * 
 * @param plat_jeu 
 * vérifie si le plateau de jeu.
 * @param j 
 * pour le symbol du joueur j.
 * @return int 
 */
int VerifFin(Plateau * plat_jeu, Joueur * j){

    int x, y;
    int i, k;

    for (x = 1; x < TAILLE_MAX_NOM + 1; x++){
        for (y = 1; y < TAILLE_MAX_NOM + 1; y++){  
            if (plat_jeu -> plateau[x][y] == '.'){
                for (i = -1; i < 2; i++){
                    for (k = -1; k < 2; k++){
                        if (plat_jeu ->  plateau[x + i][y + k] != j -> symbol &&
                        plat_jeu ->  plateau[x + i][y + k] != '.' &&
                        plat_jeu ->  plateau[x + i][y + k] != '*')
                            return 0;
                    }
                }
            }
        }
    }
    return 1;
} 

/**
 * @brief 
 * Fonction qui lit la coordonnée des joueurs.
 * 
 * @param plat 
 * @param j 
 * @param j2 
 * @param prop 
 * @return int 
 */
int LireCoo(Plateau * plat, Joueur * j, Joueur * j2, int prop){

    int x, y;

    do{
        if (VerifFin(plat, j) || VerifFin(plat, j2)){
            Gagnant(j, j2);
            return 1;
        }
        printf("%s(%c), veuillez saisir les coordonnées où joueur (entre 1 et %d) : ",j -> nom, j -> symbol,TAILLE_PLATEAU);
        scanf("%d", &x);
        scanf("%d", &y);
    } while (VerifCoo(plat, j, x, y) == 0 || y > TAILLE_PLATEAU ||
            1 > y || 1 > x || x > TAILLE_PLATEAU);
    plat -> plateau[x][y] = j -> symbol;
    ChangeCoo(plat, j, x, y, prop);
    return 0;
}

/**
 * @brief 
 * Fonction qui retourne le pion correspondant à la coordonnée 
 * du clic graphique entrée.
 *
 * @param a 
 * coordonnée entrée.
 * @return int 
 */
int TrouverCooPion(int a){

    int pion, coordx, coordy;
    for (pion = 0; pion < TAILLE_PLATEAU + 2; pion++){
        coordx = TAILLE_MARGE_GRAPH + (TAILLE_CASE_GRAPH * pion) + TAILLE_CASE_GRAPH;
        coordy = TAILLE_MARGE_GRAPH + (TAILLE_CASE_GRAPH * pion) + TAILLE_CASE_GRAPH * 2;
        if (coordx <= a && a < coordy) {
            return pion;
        }
    }
    return 0;
}

/**
 * @brief 
 * Detecte les coordonnées du joueur et met à jour l'affichage en fonction.
 * 
 * @param plat 
 * @param j 
 * @param j2 
 * @param prop 
 * @return int 
 */
int DetecterCoo(Plateau * plat, Joueur * j, Joueur * j2, int prop){

    int x, y, x_pion, y_pion;

    do{
        if (VerifFin(plat, j) || VerifFin(plat, j2)){
            Gagnant(j, j2);
            return 1;
        }
        MLV_wait_mouse(&x, &y);
        MLV_clear_window(MLV_COLOR_BLACK);

        AffichePlateauGraph(plat);
        AfficheTextePlateauGraph();
        AffichePionsGraph(plat);
        AfficheNomJoueur(j2);
        x_pion = TrouverCooPion(x) +1;
        y_pion = TrouverCooPion(y);  

    } while (VerifCoo(plat, j, x_pion, y_pion) == 0);
    plat -> plateau[x_pion][y_pion] = j -> symbol; 
    ChangeCoo(plat, j, x_pion, y_pion, prop);
    return 0;
}

/**
 * @brief 
 * Cherche les coordonnées du bot avec des boucles
 * for et ensuite vérifié par BotPuissance.
 * 
 * @param plat 
 * @param j 
 * @param prop 
 */
void BotCoo(Plateau * plat, Joueur * j, int prop){

    int x, y, puissance_max = 0;
    int x_max, y_max;
    printf("\nL'ordinateur est en train de calculer son coup !\n");
    for (x = 1; x < TAILLE_MAX_NOM + 1; x++){
        for (y = 1; y < TAILLE_MAX_NOM + 1; y++){   
            if (VerifCoo(plat, j, x, y) == 1){
                int puissance = 0;
                puissance = BotPuissance(plat , x, y,puissance);
                if (puissance > puissance_max){
                    puissance_max = puissance;
                    x_max = x;
                    y_max = y;
                }
            }
        }
    }
    plat -> plateau[x_max][y_max] = j -> symbol;
    ChangeCoo(plat, j, x_max ,y_max, prop);
}

/**
 * @brief 
 * Fonction main_ascii
 * qui permet de faire fonctionner le jeu
 * de façon ascii.
 * 
 * @param plat_jeu 
 * @param joueur_un 
 * @param joueur_deux 
 * @param bot
 * 1 ou 0 
 * @param prop 
 * 1 ou 0
 * @return int 
 */
int Ascii(Plateau * plat_jeu, Joueur * joueur_un, Joueur * joueur_deux, int bot, int prop){

    int jeu = 1, fin = 0, ascii = 1;
    while(jeu == 1){
        AffichePlateau(plat_jeu);

        Score(plat_jeu, joueur_un, ascii);
        Score(plat_jeu, joueur_deux, ascii);
        End(2);
        if (jeu == 0)
            break;

        fin = LireCoo(plat_jeu, joueur_un, joueur_deux, prop);
        if (fin){
            jeu = 0;
            break;
        }
        AffichePlateau(plat_jeu);
        Score(plat_jeu, joueur_un, ascii);
        Score(plat_jeu, joueur_deux, ascii);
        End(2);
        if (joueur_un -> score + joueur_deux -> score == TAILLE_PLATEAU * TAILLE_PLATEAU)
            jeu = Gagnant(joueur_un, joueur_deux);
        if (jeu == 0)
            break;
        End(1);
        if (bot == 0){
            fin = LireCoo(plat_jeu, joueur_deux, joueur_un, prop);
            if (fin){
            jeu = 0;
            break;
            }
        }else
            BotCoo(plat_jeu, joueur_deux, prop);
        
    }

    return 0;

}

/**
 * @brief 
 * Fonction main_graphique
 * qui permet de faire fonctionner le jeu
 * de façon graphique.
 * @param plat_jeu 
 * @param joueur_un 
 * @param joueur_deux 
 * @param bot 
 * @param prop 
 * @return int 
 */
int Graphique(Plateau * plat_jeu, Joueur * joueur_un, Joueur * joueur_deux, int bot, int prop){

    int jeu = 1, fin = 0, ascii = 0;

    while(jeu == 1){
        AffichePlateauGraph(plat_jeu);
        AfficheTextePlateauGraph();
        AffichePionsGraph(plat_jeu);
        AfficheNomJoueur(joueur_un);
        Score(plat_jeu, joueur_un, ascii);
        Score(plat_jeu, joueur_deux, ascii);
        AfficheScoreGraph(joueur_un, joueur_deux);
        MLV_actualise_window();
        if (joueur_un -> score + joueur_deux -> score == TAILLE_PLATEAU * TAILLE_PLATEAU)
            jeu = Gagnant(joueur_un, joueur_deux);
        if (jeu == 0)
            break;

        fin = DetecterCoo(plat_jeu, joueur_un, joueur_deux, prop);
        if (fin){
            jeu = 0;
            break;
        }
        AffichePionsGraph(plat_jeu);
        Score(plat_jeu, joueur_un, ascii);
        Score(plat_jeu, joueur_deux, ascii);
        AfficheScoreGraph(joueur_un, joueur_deux);
        MLV_actualise_window();
        if (joueur_un -> score + joueur_deux -> score == TAILLE_PLATEAU * TAILLE_PLATEAU)
            jeu = Gagnant(joueur_un, joueur_deux);
        if (jeu == 0)
            break;

        if (bot == 0) {
            fin = DetecterCoo(plat_jeu, joueur_deux, joueur_un, prop);
            if (fin){
                jeu = 0;
                break;
            }
        }else{
            MLV_wait_seconds(1);
            BotCoo(plat_jeu, joueur_deux, prop);
        } 
    }
    return 0;
}

/**
 * @brief 
 * Instructions pour apprendre à utiliser le programme.
 * 
 * @param name 
 */
void usage(char *name){

    printf("Usage : %s [-aohgp]\nh non compatible avec o\na non compatible avec g\n", name);
    printf("\na : Ascii | g : graphique\nh : 1 contre 1 | o : 1 contre ordinateur");
    printf("\nModes supplémantaire :\np : Prograpagation différente\n");
}

int main(int argc, char * argv[]){

    int i = 1, genre = 0;
    int ascii = 0, ordinateur = 0;
    int propagation = 0;

    Joueur joueur_un, joueur_deux;
    Plateau plat_jeu;

    if (argc > 1){
        if (argv[1][0] == '-'){
            while (argv[1][i] != '\0'){
                if (argv[1][i] == 'g'){
                    genre += 1;
                } else if(argv[1][i] == 'o'){
                    genre += 2;
                    ordinateur = 1;
                } else if(argv[1][i] == 'a'){
                    genre += 1;
                    ascii = 1;
                } else if(argv[1][i] == 'h'){
                    genre += 2;
                } else if(argv[1][i] == 'p'){
                    propagation = 1;
                }
                i++;
            }
        }
    }

    if (genre != 3){

        usage("main");
        return -1;
    }
    if (ascii == 1){

        InitPlateau(&plat_jeu);
        InitJeu(&joueur_un, &joueur_deux, ordinateur);

        Ascii(&plat_jeu, &joueur_un, &joueur_deux, ordinateur, propagation);

    }else{

        int larg_haut;

        InitPlateau(&plat_jeu);
        InitJeu(&joueur_un, &joueur_deux, ordinateur);
        larg_haut = (TAILLE_CASE_GRAPH * TAILLE_PLATEAU) + (TAILLE_MARGE_GRAPH * 2) + TAILLE_CASE_GRAPH;
        MLV_create_window("Attaxx", "Attaxx", larg_haut, larg_haut + TAILLE_CASE_GRAPH);
        Graphique(&plat_jeu, &joueur_un, &joueur_deux, ordinateur, propagation);
        MLV_wait_seconds(10);
        MLV_free_window();
    }


    return 0;
}
