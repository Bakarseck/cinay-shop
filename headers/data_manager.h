#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <stdio.h>

typedef struct
{
     int user_id;
     char nom[50];
     char prenom[50];
     char telephone[20];
     char login[6];
     char mot_de_passe[256]; // Crypté
     char role[10];          // 'Admin' ou 'Utilisateur'
} User;

typedef struct
{
     int category_id;
     char libelle[50];
} Category;

typedef struct
{
     int product_id;
     char designation[100];
     float prix;
     int quantite_stock;
     char code[6];
     char date_ajout[11]; // Format AAAA-MM-JJ
     int category_id;
} Product;

typedef struct
{
     int sale_id;
     char date_vente[20]; // Format AAAAMMDDHHmmSS
     int user_id;
     float montant_total;
} Sale;

typedef struct
{
     int sale_detail_id;
     int sale_id;
     int product_id;
     int quantite;
     float prix_unitaire;
} SaleDetail;



#endif