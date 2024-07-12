#include "../headers/header.h"

const char *USER_FILE = "../data/user.bin";
const char *TEMP_USER_FILE = "../data/user_temp.bin";
const char *VENTES_FILE = "../data/ventes.bin";
const char *CATEGORY_FILE = "../data/category.bin";
const char *PRODUITS_FILE = "../data/produits.bin";

void ajouter_utilisateur(SDL_Renderer *renderer, TTF_Font *font)
{
     char nom[50] = {0};
     char prenom[50] = {0};
     char telephone[20] = {0};
     char login[6] = {0};
     char mot_de_passe[256] = {0};
     int nom_length = 0, prenom_length = 0, telephone_length = 0, login_length = 0, mot_de_passe_length = 0;
     int field = 0;
     char chiffre[20];

     SDL_Color white = {255, 255, 255, 255};

     int running = 1;
     SDL_StartTextInput();

     while (running)
     {
          SDL_Event event;
          while (SDL_PollEvent(&event))
          {
               if (event.type == SDL_QUIT)
               {
                    SDL_Quit();
                    TTF_Quit();
                    exit(0);
               }
               else if (event.type == SDL_KEYDOWN)
               {
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                         if (field == 4)
                         {
                              running = 0;
                         }
                         else
                         {
                              field++;
                         }
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                         if (field == 0 && nom_length > 0)
                         {
                              nom[--nom_length] = '\0';
                         }
                         else if (field == 1 && prenom_length > 0)
                         {
                              prenom[--prenom_length] = '\0';
                         }
                         else if (field == 2 && telephone_length > 0)
                         {
                              telephone[--telephone_length] = '\0';
                         }
                         else if (field == 3 && login_length > 0)
                         {
                              login[--login_length] = '\0';
                         }
                    }
               }
               else if (event.type == SDL_TEXTINPUT)
               {
                    if (field == 0 && nom_length < sizeof(nom) - 1)
                    {
                         strcat(nom, event.text.text);
                         nom_length++;
                    }
                    else if (field == 1 && prenom_length < sizeof(prenom) - 1)
                    {
                         strcat(prenom, event.text.text);
                         prenom_length++;
                    }
                    else if (field == 2 && telephone_length < sizeof(telephone) - 1)
                    {
                         strcat(telephone, event.text.text);
                         telephone_length++;
                    }
                    else if (field == 3 && login_length < sizeof(login) - 1)
                    {
                         strcat(login, event.text.text);
                         login_length++;
                    }
               }
          }

          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderClear(renderer);

          renderText(renderer, "Ajouter un utilisateur", 100, 50, white, font);
          renderText(renderer, "Nom:", 100, 100, white, font);
          renderText(renderer, nom, 200, 100, white, font);
          renderText(renderer, "Prenom:", 100, 150, white, font);
          renderText(renderer, prenom, 200, 150, white, font);
          renderText(renderer, "Telephone:", 100, 200, white, font);
          renderText(renderer, telephone, 200, 200, white, font);
          renderText(renderer, "Login:", 100, 250, white, font);
          renderText(renderer, login, 200, 250, white, font);

          strcpy(mot_de_passe, "passer123");

          SDL_RenderPresent(renderer);
     }

     SDL_StopTextInput();

     // Enregistrer l'utilisateur
     FILE *fichier = fopen(USER_FILE, "ab");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier USERS.dat");
          return;
     }

     User user;
     user.user_id = auto_increment(USER_FILE);
     strcpy(user.nom, nom);
     strcpy(user.prenom, prenom);
     strcpy(user.telephone, telephone);
     strcpy(user.login, login);
     strcpy(user.mot_de_passe, chiffre);
     strcpy(user.role, "USER");

     char line[512];

     strcpy(chiffre, mot_de_passe);
     chiffrerCesar(chiffre, 10);

     sprintf(line, "%d %s %s %s %s %s %s\n", user.user_id, user.prenom, user.nom, user.telephone, user.login, chiffre, user.role);

     if (ajouter_fichier(USER_FILE, line) == 0)
     {
          printf("Utilisateur ajouté avec succès.\n");
          fclose(fichier);

          printf("Utilisateur ajouté avec succès.\n");
     }
     else
     {
          printf("Erreur lors de l'ajout de l'utilisateur.\n");
     }

     return 0;
}

int ajouter_categorie()
{
     Category category;

     printf("Veuillez saisir le libellé de la catégorie: \n");
     scanf("%49s", category.libelle);

     int id = auto_increment(CATEGORY_FILE);
     category.category_id = id;

     char line[100];
     sprintf(line, "%d %s\n", category.category_id, category.libelle);

     if (ajouter_fichier(CATEGORY_FILE, line) == 0)
     {
          printf("Catégorie ajoutée avec succès.\n");
          return 0;
     }
     else
     {
          printf("Erreur lors de l'ajout de la catégorie.\n");
          return -1;
     }
}

void lister_categories()
{
     FILE *fichier = fopen(CATEGORY_FILE, "r");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier des catégories");
          return;
     }

     Category category;
     printf("--- Liste des Catégories ---\n");
     while (fscanf(fichier, "%d %49s", &category.category_id, category.libelle) != EOF)
     {
          printf("ID: %d, Libellé: %s\n", category.category_id, category.libelle);
     }

     fclose(fichier);
}

int ajouter_produit()
{
     Product product;

     printf("Veuillez saisir la désignation du produit: \n");
     scanf("%99s", product.designation);

     printf("Veuillez saisir le prix du produit: \n");
     scanf("%f", &product.prix);

     printf("Veuillez saisir la quantité en stock: \n");
     scanf("%d", &product.quantite_stock);

     printf("Veuillez saisir le code du produit (5 caractères): \n");
     scanf("%5s", product.code);

     printf("Veuillez saisir l'ID de la catégorie: \n");
     scanf("%d", &product.category_id);

     int id = auto_increment(PRODUITS_FILE);
     product.product_id = id;

     char line[200];
     sprintf(line, "%d %s %.2f %d %s %d\n", product.product_id, product.designation, product.prix, product.quantite_stock, product.code, product.category_id);

     if (ajouter_fichier(PRODUITS_FILE, line) == 0)
     {
          printf("Produit ajouté avec succès.\n");
          return 0;
     }
     else
     {
          printf("Erreur lors de l'ajout du produit.\n");
          return -1;
     }
}

void lister_produits()
{
     FILE *fichier = fopen(PRODUITS_FILE, "r");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier des produits");
          return;
     }

     Product product;
     printf("--- Liste des Produits ---\n");
     while (fscanf(fichier, "%d %99s %f %d %5s %d", &product.product_id, product.designation, &product.prix, &product.quantite_stock, product.code, &product.category_id) != EOF)
     {
          printf("ID: %d, Désignation: %s, Prix: %.2f, Quantité en stock: %d, Code: %s, Catégorie ID: %d\n", product.product_id, product.designation, product.prix, product.quantite_stock, product.code, product.category_id);
     }

     fclose(fichier);
}

void afficherMenuAdmin(SDL_Renderer *renderer, TTF_Font *font)
{
     int choix = -1;
     SDL_Color white = {255, 255, 255, 255};
     int running = 1;

     while (running)
     {
          SDL_Event event;
          while (SDL_PollEvent(&event))
          {
               if (event.type == SDL_QUIT)
               {
                    SDL_Quit();
                    TTF_Quit();
                    exit(0);
               }
               else if (event.type == SDL_KEYDOWN)
               {
                    if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym <= SDLK_9)
                    {
                         choix = event.key.keysym.sym - SDLK_0;
                         running = 0;
                    }
               }
          }

          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderClear(renderer);

          renderText(renderer, "--- Menu Administrateur ---", 100, 50, white, font);
          renderText(renderer, "1. Ajouter un utilisateur", 100, 100, white, font);
          renderText(renderer, "2. Ajouter une categorie", 100, 150, white, font);
          renderText(renderer, "3. Ajouter un produit", 100, 200, white, font);
          renderText(renderer, "4. Lister les utilisateurs", 100, 250, white, font);
          renderText(renderer, "5. Lister les categories", 100, 300, white, font);
          renderText(renderer, "6. Lister les produits", 100, 350, white, font);
          renderText(renderer, "7. Effectuer une vente", 100, 400, white, font);
          renderText(renderer, "8. Imprimer l'etat du jour", 100, 450, white, font);
          renderText(renderer, "9. Changer mot de passe", 100, 500, white, font);
          renderText(renderer, "10. Deconnexion", 100, 550, white, font);
          renderText(renderer, "Choisissez une option: ", 100, 600, white, font);

          SDL_RenderPresent(renderer);
     }

     switch (choix)
     {
     case 1:
          ajouter_utilisateur(renderer, font);
          break;
     case 2:
          ajouter_categorie();
          break;
     case 3:
          ajouter_produit();
          break;
     case 4:
          // lister_utilisateurs();
          break;
     case 5:
          lister_categories();
          break;
     case 6:
          lister_produits();
          break;
     case 7:
          // effectuer_vente(renderer, font);
          break;
     case 8:
          // imprimer_etat_jour(renderer, font);
          break;
     case 9:
          changer_mot_de_passe(renderer, font);
     case 10:
          printf("Déconnexion réussie.\n");
          SDL_Quit();
          TTF_Quit();
          exit(0);
          return;
     default:
          printf("Option invalide. Veuillez réessayer.\n");
          break;
     }

     afficherMenuAdmin(renderer, font);
}

void changer_mot_de_passe(SDL_Renderer *renderer, TTF_Font *font)
{
     char login[50] = {0};
     char nouveau_mdp[256] = {0};
     int login_length = 0;
     int mdp_length = 0;
     int entering_login = 1;

     SDL_Color white = {255, 255, 255, 255};

     int running = 1;
     while (running)
     {
          SDL_Event event;
          while (SDL_PollEvent(&event))
          {
               if (event.type == SDL_QUIT)
               {
                    SDL_Quit();
                    TTF_Quit();
                    exit(0);
               }
               else if (event.type == SDL_KEYDOWN)
               {
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                         running = 0;
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE)
                    {
                         if (entering_login)
                         {
                              if (login_length > 0)
                              {
                                   login[--login_length] = '\0';
                              }
                         }
                         else
                         {
                              if (mdp_length > 0)
                              {
                                   nouveau_mdp[--mdp_length] = '\0';
                              }
                         }
                    }
                    else if (event.key.keysym.sym == SDLK_TAB)
                    {
                         entering_login = !entering_login;
                    }
               }
               else if (event.type == SDL_TEXTINPUT)
               {
                    if (entering_login)
                    {
                         if (login_length < sizeof(login) - 1)
                         {
                              strcat(login, event.text.text);
                              login_length++;
                         }
                    }
                    else
                    {
                         if (mdp_length < sizeof(nouveau_mdp) - 1)
                         {
                              strcat(nouveau_mdp, event.text.text);
                              mdp_length++;
                         }
                    }
               }
          }

          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderClear(renderer);

          renderText(renderer, "Changer le mot de passe", 100, 50, white, font);
          renderText(renderer, "Entrez votre login:", 100, 100, white, font);
          renderText(renderer, login, 100, 150, white, font);
          renderText(renderer, "Entrez le nouveau mot de passe:", 100, 200, white, font);
          renderText(renderer, nouveau_mdp, 100, 250, white, font);

          SDL_RenderPresent(renderer);
     }

     // Recherche et mise à jour de l'utilisateur
     FILE *fichier = fopen(USER_FILE, "r");
     FILE *fichier_temp = fopen(TEMP_USER_FILE, "w");
     if (fichier == NULL || fichier_temp == NULL)
     {
          perror("Erreur d'ouverture du fichier");
          return;
     }

     User userTemp;
     int trouve = 0;
     char chiffre[50];
     char dechiffre[50];

     while (fscanf(fichier, "%d %s %s %s %s %s %s", &userTemp.user_id, userTemp.nom, userTemp.prenom, userTemp.login, userTemp.telephone, userTemp.mot_de_passe, userTemp.role) == 7)
     {
          if (strcmp(userTemp.login, login) == 0)
          {
               strcpy(chiffre, nouveau_mdp);

               chiffrerCesar(chiffre, 10);

               strcpy(userTemp.mot_de_passe, chiffre);
               trouve = 1;
          }
          fprintf(fichier_temp, "%d %s %s %s %s %s %s\n", userTemp.user_id, userTemp.nom, userTemp.prenom, userTemp.login, userTemp.telephone, userTemp.mot_de_passe, userTemp.role);
     }

     fclose(fichier);
     fclose(fichier_temp);

     if (trouve)
     {
          if (remove(USER_FILE) == 0 && rename(TEMP_USER_FILE, USER_FILE) == 0)
          {
               printf("Mot de passe mis à jour avec succès.\n");
          }
          else
          {
               perror("Erreur lors de la mise à jour du fichier utilisateur");
          }
     }
     else
     {
          printf("Utilisateur non trouvé.\n");
          remove(TEMP_USER_FILE);
     }
}

void afficherMenuUser(SDL_Renderer *renderer, TTF_Font *font)
{
     int choix = -1;
     SDL_Color white = {255, 255, 255, 255};
     int running = 1;

     while (running)
     {
          SDL_Event event;
          while (SDL_PollEvent(&event))
          {
               if (event.type == SDL_QUIT)
               {
                    SDL_Quit();
                    TTF_Quit();
                    exit(0);
               }
               else if (event.type == SDL_KEYDOWN)
               {
                    if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym <= SDLK_4)
                    {
                         choix = event.key.keysym.sym - SDLK_0;
                         running = 0;
                    }
               }
          }

          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          SDL_RenderClear(renderer);

          renderText(renderer, "--- Menu Utilisateur ---", 100, 50, white, font);
          renderText(renderer, "1. Effectuer une vente", 100, 100, white, font);
          renderText(renderer, "2. Imprimer l'etat du jour", 100, 150, white, font);
          renderText(renderer, "3. Lister les produits", 100, 200, white, font);
          renderText(renderer, "4. Changez le mot de passe", 100, 250, white, font);
          renderText(renderer, "5. Deconnexion", 100, 300, white, font);
          renderText(renderer, "Choisissez une option: ", 100, 400, white, font);

          SDL_RenderPresent(renderer);
     }

     switch (choix)
     {
     case 1:
          // effectuer_vente();
          break;
     case 2:
          // imprimer_etat_jour();
          break;
     case 3:
          lister_produits();
          break;
     case 4:
          changer_mot_de_passe(renderer, font);
          break;
     case 5:
          printf("Déconnexion réussie.\n");
          SDL_Quit();
          TTF_Quit();
          exit(0);
          return;
     default:
          printf("Option invalide. Veuillez réessayer.\n");
          break;
     }

     afficherMenuUser(renderer, font);
}

int Atoi(char text[255])
{
     size_t i;
     for (i = 0; i < strlen(text); i++)
     {
          int r = text[i];
          if ((r < 48 || r > 57))
          {
               return -1;
          }
     }
     return 1;
}

void ScannerInt(int *a)
{
     char text[255];

invalid:
     scanf("%[^\n]s", text);
     short b = Atoi(text);
     if (b == -1)
     {
          printf("Please Enter a valid Int\n");
          goto invalid;
     }
     *a = atoi(text);

     if (*a > 1000000)
     {
          printf("Please Enter a valid Int\n");
          goto invalid;
     }
}

char *chiffrerCesar(char *texte, int decalage)
{
     int i;
     char c;

     for (i = 0; texte[i] != '\0'; i++)
     {
          c = texte[i];

          if (c >= 'a' && c <= 'z')
          {
               c = (c - 'a' + decalage) % 26 + 'a';
          }
          else if (c >= 'A' && c <= 'Z')
          {
               c = (c - 'A' + decalage) % 26 + 'A';
          }

          texte[i] = c;
     }

     return texte;
}

char *dechiffrerCesar(char *texte, int decalage)
{
     return (texte, 26 - decalage);
}

char *lire_fichier(const char *chemin_fichier)
{
     // Ouvre le fichier en mode lecture binaire ("rb")
     FILE *fichier = fopen(chemin_fichier, "rb");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier");
          return NULL;
     }

     // Se déplace à la fin du fichier pour obtenir la taille du fichier
     fseek(fichier, 0, SEEK_END);
     long taille = ftell(fichier);
     fseek(fichier, 0, SEEK_SET);

     // Alloue la mémoire pour le contenu du fichier (+1 pour le caractère nul terminant)
     char *contenu = malloc(taille + 1);
     if (contenu)
     {
          // Lit le contenu du fichier
          fread(contenu, 1, taille, fichier);
          // Ajoute le caractère nul terminant à la fin de la chaîne
          contenu[taille] = '\0';
     }

     // Ferme le fichier
     fclose(fichier);
     return contenu;
}

int ecrire_fichier(const char *chemin_fichier, const char *contenu)
{
     // Ouvre le fichier en mode écriture binaire ("wb")
     FILE *fichier = fopen(chemin_fichier, "wb");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier");
          return -1;
     }

     // Écrit le contenu dans le fichier
     size_t longueur = strlen(contenu);
     if (fwrite(contenu, sizeof(char), longueur, fichier) < longueur)
     {
          perror("Erreur d'écriture dans le fichier");
          fclose(fichier);
          return -1;
     }

     // Ferme le fichier
     fclose(fichier);
     return 0;
}

int ajouter_fichier(const char *chemin_fichier, const char *contenu)
{
     // Ouvre le fichier en mode ajout binaire ("ab")
     FILE *fichier = fopen(chemin_fichier, "ab");
     if (fichier == NULL)
     {
          perror("Erreur d'ouverture du fichier");
          return -1;
     }

     // Écrit le contenu à la fin du fichier
     size_t longueur = strlen(contenu);
     if (fwrite(contenu, sizeof(char), longueur, fichier) < longueur)
     {
          perror("Erreur d'ajout dans le fichier");
          fclose(fichier);
          return -1;
     }

     // Ferme le fichier
     fclose(fichier);
     return 0;
}

int supprimer_fichier(const char *chemin_fichier)
{
     // Supprime le fichier
     if (remove(chemin_fichier) == 0)
     {
          return 0;
     }
     else
     {
          perror("Erreur de suppression du fichier");
          return -1;
     }
}

int auto_increment(const char *chemin_fichier)
{
     FILE *fichier = fopen(chemin_fichier, "r");

     if (fichier == NULL)
     {
          return 0;
     }

     int id = 0;
     User userTemp;

     while (
         fscanf(fichier, "%d %s %s %s %s %s %s", &userTemp.user_id, userTemp.nom, userTemp.prenom, userTemp.login, userTemp.telephone, userTemp.mot_de_passe, userTemp.role) == 7)
     {
          id = userTemp.user_id;
     }

     fclose(fichier);

     return id + 1;
}