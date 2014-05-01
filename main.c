#include "main.h"
 
int main(int argc, char *argv[])
{
  SDL_Surface *ecran = NULL;
  SDL_Event event;
  int continuer = 1, hauteurBarre = 0, tempsActuel = 0, tempsPrecedent = 0, i = 0, j = 0;
  float spectre[TAILLE_SPECTRE]; 
  FMOD_SYSTEM *system;
  FMOD_SOUND *musique;
  FMOD_CHANNEL *canal;
  FMOD_RESULT resultat;

  FMOD_System_Create(&system);
  FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
 
  resultat = FMOD_System_CreateSound(system, "intro.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
 
  if (resultat != FMOD_OK)
    {
      fprintf(stderr, "Impossible de lire le fichier mp3\n");
      exit(EXIT_FAILURE);
    }
 
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
 
  FMOD_System_GetChannel(system, 0, &canal);
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("INTRO", NULL);

  while (continuer)
    {
      SDL_PollEvent(&event); // On doit utiliser PollEvent car il ne faut pas attendre d'évènement de l'utilisateur pour mettre à jour la fenêtre
      switch(event.type)
        {
        case SDL_QUIT:
	  continuer = 0;
	  break;
        }
 
      /* On efface l'écran à chaque fois avant de dessiner le graphe (fond noir) */
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
 
      /* Gestion du temps
           -----------------
           On compare le temps actuel par rapport au temps précédent (dernier passage dans la boucle)
           Si ça fait moins de 25 ms (DELAI_RAFRAICHISSEMENT)
           Alors on attend le temps qu'il faut pour qu'au moins 25 ms se soient écoulées.
           On met ensuite à jour tempsPrecedent avec le nouveau temps */
 
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent < DELAI_RAFRAICHISSEMENT)
        {
	  SDL_Delay(DELAI_RAFRAICHISSEMENT - (tempsActuel - tempsPrecedent));
        }
      tempsPrecedent = SDL_GetTicks();
 
      /* Dessin du spectre sonore
           ------------------------
 
           C'est la partie la plus intéressante. Il faut réfléchir un peu à la façon de dessiner pour y arriver, mais c'est tout à fait faisable (la preuve).
 
           On remplit le tableau de 512 floats via FMOD_Channel_GetSpectrum()
           On travaille ensuite pixel par pixel sur la surface ecran pour dessiner les barres.
           On fait une première boucle pour parcourir la fenêtre en largeur.
           La seconde boucle parcourt la fenêtre en hauteur pour dessiner chaque barre.
      */
 
      /* On remplit le tableau de 512 floats. J'ai choisi de m'intéresser à la sortie gauche */
      FMOD_Channel_GetSpectrum(canal, spectre, TAILLE_SPECTRE, 0, FMOD_DSP_FFT_WINDOW_RECT);
 
      /* Trie le tableau */
      TABMAX p = o(spectre, TAILLE_SPECTRE);
      /* Affiche les composantes de l'échantillon */
      printf("%d/%f => frequence : %f Hz\n", p.indice, p.value, getFreq(p));
      //printf("%d/%f\n", p.indice, p.value);
      SDL_LockSurface(ecran); /* On bloque la surface ecran car on va directement modifier ses pixels */
 
      /* BOUCLE 1 : on parcourt la fenêtre en largeur (pour chaque barre verticale) */
      for (i = 0 ; i < LARGEUR_FENETRE ; i++)
        {
	  /* On calcule la hauteur de la barre verticale qu'on va dessiner.
               spectre[i] nous renvoie un nombre entre 0 et 1 qu'on multiplie par 20 pour zoomer afin de voir un peu mieux (comme je vous avais dit).
               On multiplie ensuite par HAUTEUR_FENETRE pour que la barre soit agrandie par rapport à la taille de la fenêtre. */
	  hauteurBarre = spectre[i] * 20 * HAUTEUR_FENETRE;
 
	  /* On vérifie que la barre ne dépasse pas la hauteur de la fenêtre
	     Si tel est le cas on coupe la barre au niveau de la hauteur de la fenêtre. */
	  if (hauteurBarre > HAUTEUR_FENETRE)
	    hauteurBarre = HAUTEUR_FENETRE;
 
	  /* BOUCLE 2 : on parcourt en hauteur la barre verticale pour la dessiner */
	  for (j = HAUTEUR_FENETRE - hauteurBarre ; j < HAUTEUR_FENETRE ; j++)
            {
	      /* On dessine chaque pixel de la barre à la bonne couleur.
                   On fait simplement varier le rouge et le vert, chacun dans un sens différent.
 
                   j ne varie pas entre 0 et 255 mais entre 0 et HAUTEUR_FENETRE.
                   Si on veut l'adapter proportionnellement à la hauteur de la fenêtre, il suffit de faire le calcul j / RATIO, où RATIO vaut (HAUTEUR_FENETRE / 255.0).
                   J'ai dû réfléchir 2-3 minutes pour trouver le bon calcul à faire, mais c'est du niveau de tout le monde. Il suffit de réfléchir un tout petit peu */
	      setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 255 - (j / RATIO), j / RATIO, 0));
            }
        }
 
      SDL_UnlockSurface(ecran); /* On a fini de travailler sur l'écran, on débloque la surface */
 
      SDL_Flip(ecran);
    }
 
  /* Le programme se termine.
       On libère la musique de la mémoire
       et on ferme FMOD */
 
  FMOD_Sound_Release(musique);
  FMOD_System_Close(system);
  FMOD_System_Release(system);
 
  SDL_Quit();
 
  return EXIT_SUCCESS;
}
 
/* La fonction setPixel permet de dessiner pixel par pixel dans une surface */
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  int bpp = surface->format->BytesPerPixel;
 
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
 
  switch(bpp) {
  case 1:
    *p = pixel;
    break;
 
  case 2:
    *(Uint16 *)p = pixel;
    break;
 
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
 
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}
 
/* Retourne l'indice de la plus grande valeur du tableau */
 
TABMAX o(float tableau[], float tailleTableau) {
  float max = tableau[0];
  TABMAX defaut = {0,0};
  int i = 0;
  for(i = 0; i < tailleTableau; i++) {
    if(tableau[i] > max)
      max = tableau[i];
  }
  for(i = 0; i < tailleTableau; i++) {
    if(tableau[i] == max) {
      TABMAX a = {i, max};
      return a;
    }
  }
  return defaut;
}
 
float getFreq(TABMAX tabMax) {
  return (REF_FREQ*tabMax.indice)/(REF_FREQ_EQ); // Un simple produit en croix
}
