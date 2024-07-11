#ifndef USER_H
#define USER_H

typedef struct
{
     int user_id;
     char nom[50];
     char prenom[50];
     char telephone[20];
     char login[20];
     char mot_de_passe[256]; // Crypté
     char role[10];          // 'Admin' ou 'Utilisateur'
} User;

// Prototypes des fonctions de gestion des utilisateurs
int ajouter_utilisateur();
User* lire_utilisateurs(int* taille);
int supprimer_utilisateur(int user_id);

int connexion();


#endif