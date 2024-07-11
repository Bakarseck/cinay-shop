Utilisateurs (Users)
---------------------
user_id (PK)
nom
prenom
telephone
login (unique)
mot_de_passe
role

Catégories (Categories)
-----------------------
category_id (PK)
libelle

Produits (Products)
--------------------
product_id (PK)
designation
prix
quantite_stock
code (unique)
date_ajout
category_id (FK)

Ventes (Sales)
--------------
sale_id (PK)
date_vente
user_id (FK)
montant_total

Détails des Ventes (SaleDetails)
--------------------------------
sale_detail_id (PK)
sale_id (FK)
product_id (FK)
quantite
prix_unitaire
