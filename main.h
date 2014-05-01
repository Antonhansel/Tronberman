#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <fmod.h>
 
#define LARGEUR_FENETRE         512 /* DOIT rester à 512 impérativement car il y a 512 barres (correspondant aux 512 floats) */
#define HAUTEUR_FENETRE         400 /* Vous pouvez la faire varier celle-là par contre */
#define RATIO                   (HAUTEUR_FENETRE / 255.0)
#define DELAI_RAFRAICHISSEMENT  25 /* Temps en ms entre chaque mise à jour du graphe. 25 ms est la valeur minimale. */
#define TAILLE_SPECTRE          4096
#define REF_FREQ 1000 /* Fréquence de référence */
#define REF_FREQ_EQ 171 /* Equivalent de REF_FREQ via FMOD_getSpectrum() */
 
typedef struct {
  int indice;
  float value;
} TABMAX ;
 
TABMAX o(float tableau[], float tailleTableau);
float getFreq(TABMAX tabMax);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
