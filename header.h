#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define L_C 35
// Buffer
BITMAP* buffer;
BITMAP* ele[L_C];


// Structure pour les cases
typedef struct cases {
    int x1, y1; // Coordonnées du sommet supérieur
    int x2, y2; // Coordonnées du sommet droit
    int x3, y3; // Coordonnées du sommet inférieur
    int x4, y4; // Coordonnées du sommet gauche
    int x5, y5; // Coordonnées en bas à droite
    int x6, y6; // Coordonnées en bas au milieu
    int x7, y7; // Coordonnées en bas à gauche
    int num;
    int element;
    int objet;
} t_case;

typedef struct elements {
    int x1, x2;
    int y1, y2;
    int num;
    int choix;
} t_ele;

// Prototypes de fonctions
void init_ALLEG();
t_case** matriceCase();
t_ele** matriceElements();
void biblio();
void affichageMatrice(t_case** matrice);
void convertirEnIsometrique(t_case** matrice, int tileWidth, int tileHeight);
void affichageMap(t_case** matrice, t_ele** matriceE);
void affichagePosition(t_case** matrice, t_ele** matriceE);
void reinitialiserChoix(t_ele** matrice);
void elementSelection(t_ele** matrice);
int choixDeSelection(t_ele** matrice);
void menu(t_ele** matriceE);

#endif // HEADER_H_INCLUDED
