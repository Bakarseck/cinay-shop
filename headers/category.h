#ifndef CATEGORY_H
#define CATEGORY_H

typedef struct
{
     int id;
     char libelle[50];
} Category;

int ajouter_categorie(Category category);
void lister_categories();

#endif // CATEGORY_H
