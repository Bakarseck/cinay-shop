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

          switch (choix)
          {
          case 1:
               connexion();
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
