#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "IsometricCube.h"

#define SCREEN_W 700
#define SCREEN_H_PSEUDO 500//separe la partie matrice case et matrice élement
#define SCREEN_H 700

//lignes et colonnes pour la matrice case
#define LIGNES 15
#define COLONNES 15
//lignes et colonnes pour la matrice elements
#define LIGNES_E 3
#define COLONNES_E 12
//colonnes pour le tableau de BITMAPS
#define L_C 35




void init_ALLEG() {
    allegro_init();
    set_color_depth(desktop_color_depth());

    if ((set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0)) != 0) {
        allegro_message("Probleme de mode graphique !");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

t_case** matriceCase() {
    int num=1;
    t_case** matriceCase;

    // Allocation dynamique de la matrice des cases
    matriceCase = (t_case**)malloc(LIGNES * sizeof(t_case*));
    if (matriceCase == NULL) {
        printf("\nProbleme d'allocation lignes\n");
    }

    for (int i = 0; i < LIGNES; i++) {
        matriceCase[i] = (t_case*)malloc(COLONNES * sizeof(t_case));
        if (matriceCase[i] == NULL) {
            printf("\nProbleme d'allocation colonnes\n");
        }
    }

    // Remplissage des coordonnées des cases
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            matriceCase[i][j].x1 = j * 32 + 32;
            matriceCase[i][j].y1 = i * 32 + 32;
            matriceCase[i][j].x2 = (j + 1) * 32 + 32;
            matriceCase[i][j].y2 = (i + 1) * 32 + 32;
            matriceCase[i][j].x3 = matriceCase[i][j].x2;
            matriceCase[i][j].y3 = matriceCase[i][j].y2;
            matriceCase[i][j].x4 = matriceCase[i][j].x1;
            matriceCase[i][j].y4 = matriceCase[i][j].y1;
            matriceCase[i][j].num=num;
            matriceCase[i][j].element=0;
            matriceCase[i][j].objet=0;
            num++;
        }
    }

    return matriceCase;
}

// Fonction pour convertir les coordonnées des cases en isométriques
void convertirEnIsometrique(t_case** matrice, int tileWidth, int tileHeight) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            int x = j;
            int y = i;

            int isoX = (x - y) * (tileWidth / 2);
            int isoY = (x + y) * (tileHeight / 2);

            matrice[i][j].x1 = isoX + SCREEN_W / 2;
            matrice[i][j].y1 = isoY + (SCREEN_H_PSEUDO-200) / 4;
            matrice[i][j].x2 = isoX + (tileWidth / 2) + SCREEN_W / 2;
            matrice[i][j].y2 = isoY + (tileHeight / 2) + (SCREEN_H_PSEUDO-200) / 4;
            matrice[i][j].x3 = isoX + SCREEN_W / 2;
            matrice[i][j].y3 = isoY + tileHeight + (SCREEN_H_PSEUDO-200) / 4;
            matrice[i][j].x4 = isoX - (tileWidth / 2) + SCREEN_W / 2;
            matrice[i][j].y4 = isoY + (tileHeight / 2) + (SCREEN_H_PSEUDO-200) / 4;

            matrice[i][j].x6 = matrice[i][j].x1;
            matrice[i][j].y6 = matrice[i][j].y3 + tileHeight;
            matrice[i][j].x5 = matrice[i][j].x2;
            matrice[i][j].y5 = matrice[i][j].y2 + tileHeight;
            matrice[i][j].x7 = matrice[i][j].x4;
            matrice[i][j].y7 = matrice[i][j].y4 + tileHeight;
        }
    }
}

t_ele** matriceElements(){
    int num=1; //a changer
    int x=20, y=520;

    t_ele** matriceElements;

    // Allocation dynamique de la matrice des cases
    matriceElements = (t_ele**)malloc(LIGNES_E * sizeof(t_ele*));
    if (matriceElements == NULL) {
        printf("\nProbleme d'allocation lignes\n");
    }

    for (int i = 0; i < LIGNES_E; i++) {
        matriceElements[i] = (t_ele*)malloc(COLONNES_E * sizeof(t_ele));
        if (matriceElements[i] == NULL) {
            printf("\nProbleme d'allocation colonnes\n");
        }
    }

    // Remplissage des coordonnées des cases
    for (int i = 0; i < LIGNES_E; i++) {
        for (int j = 0; j < COLONNES_E; j++) {
            matriceElements[i][j].x1 = x+5;
            matriceElements[i][j].y1 = y+5;
            matriceElements[i][j].x2 = matriceElements[i][j].x1+50;
            x = matriceElements[i][j].x2;
            matriceElements[i][j].y2 = matriceElements[i][j].y1+50;
            matriceElements[i][j].num=num;
            matriceElements[i][j].choix=0;//booleen mis a 0
            num++;
            if(j==(COLONNES_E-1)){
                x=20;
                y=matriceElements[i][j].y2;
            }
        }
    }

    matriceElements[LIGNES_E-1][COLONNES_E-1].num=0;

    return matriceElements;
}

//permet de charger toutes les BITMAPS
void biblio(){
    char nomfichier[50];

    for(int i=0;i<L_C;i++){
        sprintf(nomfichier,"isometricTiles/isometric_pixel_%d.bmp",i+1);
        ele[i]=load_bitmap(nomfichier,NULL);
    }

}

void affichageMatrice(t_case** matrice) {
    // Affiche les parties non achetées de la matrice
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            // Dessiner les losanges pour représenter les tuiles isométriques
            line(buffer, matrice[i][j].x1, matrice[i][j].y1, matrice[i][j].x2, matrice[i][j].y2, makecol(150, 150, 150));
            line(buffer, matrice[i][j].x2, matrice[i][j].y2, matrice[i][j].x3, matrice[i][j].y3, makecol(150, 150, 150));
            line(buffer, matrice[i][j].x3, matrice[i][j].y3, matrice[i][j].x4, matrice[i][j].y4, makecol(150, 150, 150));
            line(buffer, matrice[i][j].x4, matrice[i][j].y4, matrice[i][j].x1, matrice[i][j].y1, makecol(150, 150, 150));

            line(buffer,matrice[i][j].x2,matrice[i][j].y2,matrice[i][j].x5,matrice[i][j].y5,makecol(100, 100, 100));
            line(buffer,matrice[i][j].x3,matrice[i][j].y3,matrice[i][j].x6,matrice[i][j].y6,makecol(100, 100, 100));
            line(buffer,matrice[i][j].x4,matrice[i][j].y4,matrice[i][j].x7,matrice[i][j].y7,makecol(100, 100, 100));
            line(buffer,matrice[i][j].x5,matrice[i][j].y5,matrice[i][j].x6,matrice[i][j].y6,makecol(100, 100, 100));
            line(buffer,matrice[i][j].x6,matrice[i][j].y6,matrice[i][j].x7,matrice[i][j].y7,makecol(100, 100, 100));
        }
    }
}

//affichage de la case au se trouve la souris
void affichagePosition(t_case** matrice, t_ele** matriceE) {
    // Affiche les parties non achetées de la matrice
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if(mouse_x>matrice[i][j].x1 && mouse_x<matrice[i][j].x2 && mouse_y>matrice[i][j].y1 && mouse_y<matrice[i][j].y3){
                // Dessiner les losanges pour représenter les tuiles isométriques
                line(buffer, matrice[i][j].x1, matrice[i][j].y1, matrice[i][j].x2, matrice[i][j].y2, makecol(0, 255, 0));
                line(buffer, matrice[i][j].x2, matrice[i][j].y2, matrice[i][j].x3, matrice[i][j].y3, makecol(0, 255, 0));
                line(buffer, matrice[i][j].x3, matrice[i][j].y3, matrice[i][j].x4, matrice[i][j].y4, makecol(0, 255, 0));
                line(buffer, matrice[i][j].x4, matrice[i][j].y4, matrice[i][j].x1, matrice[i][j].y1, makecol(0, 255, 0));

                line(buffer, matrice[i][j].x1, matrice[i][j].y1, matrice[i][j].x3, matrice[i][j].y3, makecol(0, 255, 0));
                line(buffer, matrice[i][j].x2, matrice[i][j].y2, matrice[i][j].x4, matrice[i][j].y4, makecol(0, 255, 0));
                textprintf_ex(buffer,font,40,SCREEN_H_PSEUDO-20,makecol(100,100,100),-1,"Case:");
                textprintf_ex(buffer,font,85,SCREEN_H_PSEUDO-20,makecol(100,100,100),-1,"%d",matrice[i][j].num);
                if((mouse_b & 1) && matrice[i][j].element==0 && choixDeSelection(matriceE)<(L_C-4) && choixDeSelection(matriceE)!=0){
                    matrice[i][j].element=choixDeSelection(matriceE);//on ne passe pas une BITMAP mais un int qui permet d'attribuer une BITMAP a une case
                }
                else if((mouse_b & 1) && choixDeSelection(matriceE)==0){//si on veux retirer
                    matrice[i][j].element=0;
                    matrice[i][j].objet=0;
                }
                else if((mouse_b & 1) && matrice[i][j].objet==0 && choixDeSelection(matriceE)>=(L_C-4) && choixDeSelection(matriceE)<=L_C){//si on veut ajouter un objet
                    matrice[i][j].objet=choixDeSelection(matriceE);
                }
            }
        }
    }
}

void affichageMap(t_case** matrice, t_ele** matriceE) {
    // Affiche les parties non achetées de la matrice
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if((matrice[i][j].element-1)>=0){
                masked_blit(ele[matrice[i][j].element-1],buffer,4,1,matrice[i][j].x4, matrice[i][j].y1, SCREEN_W, SCREEN_H);
            }
        }
    }

    //affiche les objets sur la map
    for (int i = 0; i < LIGNES; i++) {
        for(int j=0; j< COLONNES; j++){
            if(matrice[i][j].objet!=0){
                masked_blit(ele[matrice[i][j].objet-1],buffer,4,1,matrice[i][j].x4, matrice[i][j].y1-24, SCREEN_W, SCREEN_H);
            }
        }
    }
}

//permet de mettre tous les elements en non-choisi
void reinitialiserChoix(t_ele** matrice){
    for(int i=0; i<LIGNES_E; i++){
        for(int j=0; j<COLONNES_E; j++){
            matrice[i][j].choix=0;
        }
    }
}

//permet de mettre un booleen sur l'élément de la matrice d'elements selectionné
void elementSelection(t_ele** matrice){
    for(int i=0; i<LIGNES_E; i++){
        for(int j=0; j<COLONNES_E; j++){
            if((mouse_b & 1) && mouse_x>matrice[i][j].x1 && mouse_x<matrice[i][j].x2 && mouse_y>matrice[i][j].y1 && mouse_y<matrice[i][j].y2){
                rect(buffer,matrice[i][j].x1,matrice[i][j].y1,matrice[i][j].x2,matrice[i][j].y2,makecol(255,255,255));
                reinitialiserChoix(matrice);
                matrice[i][j].choix=1;
            }
        }
    }
}

//retourne le numero de l'element choisi
int choixDeSelection(t_ele** matrice){
    for(int i=0; i<LIGNES_E; i++){
        for(int j=0; j<COLONNES_E; j++){
            if(matrice[i][j].choix == 1){
                return matrice[i][j].num;
            }
        }
    }
}

//affihe le menu d'élements disponibles
void menu(t_ele** matriceE){
    int indice=0;

    textprintf_ex(buffer,font,20,20,makecol(255,255,255),-1,"WORLD MAP");
    rect(buffer,10,10,SCREEN_W-10,SCREEN_H_PSEUDO,makecol(50,50,50));
    rect(buffer,10,510,690,SCREEN_H-10,makecol(50, 50, 50));

    //affichage des boites individuelles
    for(int i=0; i<LIGNES_E; i++){
        for(int j=0; j<COLONNES_E; j++){
            rectfill(buffer,matriceE[i][j].x1,matriceE[i][j].y1,matriceE[i][j].x2,matriceE[i][j].y2,makecol(50,50,50));
            if(i==(LIGNES_E-1) && j==(COLONNES_E-1)){
                rectfill(buffer,matriceE[i][j].x1+3,matriceE[i][j].y1+3,matriceE[i][j].x2-3,matriceE[i][j].y2-3,makecol(255,255,255));
                textprintf_ex(buffer,font,matriceE[LIGNES_E-1][COLONNES_E-1].x1+10,matriceE[LIGNES_E-1][COLONNES_E-1].y2-25,makecol(0,0,0),-1,"Edit");
            }
        }
    }

    //affichage des bitmap
    for(int i=0; i<LIGNES_E; i++){
        for(int j=0; j<COLONNES_E; j++){
            if(indice<(LIGNES_E*COLONNES_E)-1){
                masked_blit(ele[indice],buffer,0,0,matriceE[i][j].x1,matriceE[i][j].y1,SCREEN_W,SCREEN_H);
                indice++;
            }
        }
    }

}

int main() {
    //initialisation des variables
    t_case** matrice;
    matrice = matriceCase();
    t_ele** matriceElement;
    matriceElement=matriceElements();

    init_ALLEG(); // Initialisation

    //initialisation de chaque BITMAPs
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    biblio();


    // Installation du clavier et de la souris
    install_keyboard();
    install_mouse();
    // Affichage de la souris sur l'écran
    show_mouse(screen);

    // Convertir les coordonnées des cases en isométriques
    convertirEnIsometrique(matrice,41, 24);

    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);//efface le buffer precedent

        menu(matriceElement);
        elementSelection(matriceElement);

        affichageMatrice(matrice);
        affichageMap(matrice,matriceElement);
        affichagePosition(matrice,matriceElement);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    allegro_exit();
    destroy_bitmap(buffer);

    // Libération de la mémoire
    for (int i = 0; i < 9; i++) {
        free(matrice[i]);
    }
    free(matrice);

    return 0;
}END_OF_MAIN();
