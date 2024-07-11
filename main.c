#include <stdio.h>
#include "headers/user.h"

int main()
{
     int choix;
     // initialiser();

     while (1)
     {
          printf("\n--- Menu Principal ---\n");
          printf("1. Connexion\n");
          printf("2. Quitter\n");
          printf("Choisissez une option: ");

          scanf("%d", &choix);

          int role = 0;
          switch (choix)
          {
          case 1:
               role = connexion();
               if (role == 0) {
                    afficherMenuAdmin();
               } else if (role == 1) {
                    afficherMenuUser();
               } else if (role == 2) {
                    printf("Vous êtes bloqués");
               } else {
                    printf("\033[31mLogin ou mot de passe incorrect\033[0m;");
               }
               break;
          case 2:
               printf("Au revoir !\n");
               return 0;
          default:
               printf("Option invalide !\n");
          }
     }

     return 0;
}
