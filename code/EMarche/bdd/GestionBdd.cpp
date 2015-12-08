#include "GestionBdd.h"
#include <iostream>

using namespace std;

GestionBdd::GestionBdd() : utilisateurConnecte(NULL)
{

}

/* Génération de la référence */
int valRef = 1;
string nouvelleRef = "#1";
string GestionBdd::generateReference() {
    vector<Produit*>::iterator it;
    vector<Produit*> lesProduits = produits.getListProduits();
    for (it = lesProduits.begin(); it != lesProduits.end(); it++) {
        if((*it)->getReference().compare(nouvelleRef) == 0) {
            while((*it)->getReference().compare(nouvelleRef) == 0) {
                valRef++;
                string s = to_string(valRef);
                nouvelleRef = "#" + s;
            }
        }
    }
    return nouvelleRef;
}

/* Fonctions */

/* ajouter vue */
void GestionBdd::addVue(Vue* v) {
    vues.push_back(v);
}

/* maj vues */
void GestionBdd::update() {
    for(unsigned int i = 0;i < vues.size();i++)
        vues[i]->update();
}

/* PARTIE UTILISATEURS */

/* connexion */
void GestionBdd::connecterUtilisateur(string pseudo, string mdp) {
    bool valide = utilisateurs.existeUtilisateur(pseudo, mdp);
    if(valide) {
        utilisateurConnecte = utilisateurs.getUtilisateur(pseudo);
        update();
    }
}

/* déconnexion */
void GestionBdd::deconnecterUtilisateur() {
    utilisateurConnecte = NULL;
}

/* savoir si on est connecté */
bool GestionBdd::isConnecte() {
    return utilisateurConnecte != NULL ? true : false;
}

/* retourner un pointeur vers l'utilisateur connecté */
Utilisateur* GestionBdd::getUtilisateurConnecte() {
    return utilisateurConnecte;
}

/* inscription */
void GestionBdd::inscrire(string monPseudo, string monMdp, string name, string firstname,
              int jourNaiss, int moisNaiss, int anneeNaiss, string mail, string adr)
{
    utilisateurs.add(new Utilisateur(monPseudo, monMdp, name, firstname, jourNaiss, moisNaiss, anneeNaiss, mail, adr));
}

/* Ajouter un nouveau produit */
void GestionBdd::nouveauProduit(Produit *p){
    produits.addProduit(p);
}

/* recherche utilisateurs */
vector<Utilisateur*> GestionBdd::rechercherUtilisateurs(string pseudo) {
    return utilisateurs.getUtilisateurs(pseudo);
}

/* recherche utilisateur */
Utilisateur* GestionBdd::rechercherUtilisateur(string pseudo) {
    return utilisateurs.getUtilisateur(pseudo);
}

/* PARTIE PRODUITS */

/* ajouter produit en vente */
void GestionBdd::ajouterVente(string n, string cat, float prix, unsigned int qte, bool etat) {
    Produit *p = new Produit(n, cat, prix, qte, etat);
    p->setReference(generateReference());
    //utilisateurConnecte->addVente(p);
    produits.addProduit(p);
}

/* ventes en cours */
void GestionBdd::ventesEnCours() {

}

/* recherche produit par nom */
vector<Produit*> GestionBdd::rechercherProduitNom(string nom) {
    return produits.getProduitsNom(nom);
}

/* recherche produit par tags */
vector<Produit*> GestionBdd::rechercherProduitTags(string tags) {
    istringstream split(tags);
    vector<string> tokens;
    for (string each; getline(split, each, ' '); tokens.push_back(each));
    return produits.rechercherTags(tokens);
}

/* Rechercher un produit par référence */
Produit* GestionBdd::rechercherProduit(string ref) {
    return produits.getProduit(ref);
}

/* Rechercher les tags d'un produit */
vector<Produit*> GestionBdd::rechercherTags(string t){
    // Transformation des caractères du tag en minuscules
    std::transform(t.begin(), t.end(), t.begin(), ::tolower);
    return produits.rechercherTags(t);
}

/* Rechercher tous les produits d'une catégorie */
vector<Produit*> GestionBdd::rechercherCategorie(string c){
    // Transformation des caractères de la catégorie en minuscules
    std::transform(c.begin(), c.end(), c.begin(), ::tolower);
    return produits.rechercherCategorie(c);
}
