#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    int id;
    char designation[50];
    double prix;
    int quantite;
    char code[6];
    char date_ajout[20];
    int category_id;
} Product;

int ajouter_produit(Product product);
void lister_produits();

#endif // PRODUCT_H
