#include <stdio.h>
#include "headers/user.h"
#include "headers/file.h"
#include <string.h>

const char* USER_FILE = "data/user.bin";

int ajouter_utilisateur() {

     User user;

     printf("Veuillez saisir votre nom: \n");
     scanf("%s", &user.nom);

     printf("Veuillez saisir votre prénom: \n");
     scanf("%s", &user.prenom);

     printf("Veuillez saisir votre mot de passe: \n");
     scanf("%s", &user.mot_de_passe);

     const char line[255];

     int id = 0;
     id = auto_increment(USER_FILE);

     printf("%d", id);

     sprintf(line, "%d %s %s %s \n", id, user.nom, user.prenom, user.mot_de_passe);

     ajouter_fichier(USER_FILE, line);
}

int connexion() {

     FILE *fichier = fopen(USER_FILE, "r");

     if (fichier == NULL)
     {
          return -1;
     }

     User userTemp;

     char login[50];
     char password[50];

     printf("Veuillez entrez votre login:\n");
     scanf("%s", login);

     printf("Veuillez entrez votre password:\n");
     scanf("%s", password);

     // 1 Rokhaya NDAO rokhyndao 771234567 passer123 USER
     while (
          fscanf(fichier, "%d %s %s %s %s %s %s", &userTemp.user_id, userTemp.nom, userTemp.prenom, userTemp.login, userTemp.telephone,  userTemp.mot_de_passe, userTemp.role) == 7)
     {

          if (strcmp(login, userTemp.login) == 0) {
               if (strcmp(password, userTemp.mot_de_passe) == 0) {
                    printf("Vous êtes connectés");
                    fclose(fichier);
                    return 0;
               } else {
                    fclose(fichier);
                    return 1;
               }
          }
     }

     fclose(fichier);
     return 1;
}    