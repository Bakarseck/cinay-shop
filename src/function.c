#include "../headers/header.h"

const char *USER_FILE = "../data/user.bin";
const char *VENTES_FILE = "../data/ventes.bin";
const char *CATEGORY_FILE = "../data/category.bin";
const char *PRODUITS_FILE = "../data/produits.bin";

int ajouter_utilisateur()
{
     User user;

     printf("Veuillez saisir votre nom: \n");
     scanf("%s", user.nom);

     printf("Veuillez saisir votre prénom: \n");
     scanf("%s", user.prenom);

     printf("Veuillez saisir votre téléphone: \n");
     scanf("%s", user.telephone);

     printf("Veuillez saisir votre login: \n");
     scanf("%s", user.login);

     strcpy(user.mot_de_passe, "passer123");

     printf("Veuillez saisir votre rôle (ADMIN, USER, USERBLOQUE): \n");
     scanf("%s", user.role);

     int id = auto_increment(USER_FILE);
     user.user_id = id;

     char line[512];
     char chiffre[50];

     strcpy(chiffre, user.mot_de_passe);
     chiffrerCesar(chiffre, 10);

     sprintf(line, "%d %s %s %s %s %s %s\n", user.user_id, user.prenom, user.nom, user.telephone, user.login, chiffre, user.role);

     if (ajouter_fichier(USER_FILE, line) == 0)
     {
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

void afficherMenuAdmin()
{
     int choix;

     while (1)
     {
          printf("--- Menu Administrateur ---\n");
          printf("1. Ajouter un utilisateur\n");
          printf("2. Ajouter une catégorie\n");
          printf("3. Ajouter un produit\n");
          printf("4. Lister les utilisateurs\n");
          printf("5. Lister les catégories\n");
          printf("6. Lister les produits\n");
          printf("7. Effectuer une vente\n");
          printf("8. Imprimer l'état du jour\n");
          printf("9. Déconnexion\n");
          printf("Choisissez une option: ");
          scanf("%d", &choix);

          switch (choix)
          {
          case 1:
               ajouter_utilisateur();
               break;
          case 2:
               ajouter_categorie();
               break;
          case 3:
               ajouter_produit();
               break;
          case 4:
               break;
          case 5:
               lister_categories();
               break;
          case 6:
               lister_produits();
               break;
          case 7:
               break;
          case 8:
               break;
          case 9:
               printf("Déconnexion réussie.\n");
               exit(0);
               return;
          default:
               printf("Option invalide. Veuillez réessayer.\n");
               break;
          }
     }
}

void afficherMenuUser()
{
     int choix;

     while (1)
     {
          printf("--- Menu Utilisateur ---\n");
          printf("1. Effectuer une vente\n");
          printf("2. Imprimer l'état du jour\n");
          printf("3. Lister les produits\n");
          printf("4. Déconnexion\n");
          printf("Choisissez une option: ");
          scanf("%d", &choix);

          switch (choix)
          {
          case 1:
               break;
          case 2:
               break;
          case 3:
               break;
          case 4:
               printf("Déconnexion réussie.\n");
               exit(0);
               return;
          default:
               printf("Option invalide. Veuillez réessayer.\n");
               break;
          }
     }
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