#ifndef GESTIONBDD_H
#define GESTIONBDD_H

#include <string>
#include <vector>
#include <algorithm>
#include "LesUtilisateurs.h"
#include "LesProduits.h"
#include "Vue.h"
#include "Avis.h"

//!
//! \brief The GestionBdd class - Gère le stockage des utilisateurs, des produits, et la mise à jour des vues
//!
class GestionBdd
{

protected:
    LesUtilisateurs utilisateurs;
    LesProduits produits;
    std::vector<Vue*> vues;
    Utilisateur *utilisateurConnecte;
    std::string ref;
    int quantite;
    Produit *produitCourant;

public:
    //!
    //! \brief GestionBdd - constructeur
    //!
    GestionBdd();

    ~GestionBdd() {
        std::vector<Vue*>::iterator it;
        for(it = vues.begin(); it != vues.end();it++) {
            delete(*it);
        }
        delete(utilisateurConnecte);
    }

    /* FONCTIONS */


    /* incrémenter ref servant de référence unique aux produits */
    //!
    //! \fn void incrementerRef()
    //! \brief incrémente la référence pour l'attribuer à un produit et qu'elle soit unique (version 1)
    //!
    void incrementerRef();

    /* nouvelle référence */
    //!
    //! \fn std::string generateReference()
    //! \brief génère une référence unique (version 2)
    //! \return std::string - référence
    //!
    std::string generateReference();

    /* ajouter vue */
    //!
    //! \fn void addVue(Vue* v)
    //! \brief ajoute une vue au vector contenant les vues
    //! \param v - pointeur vers la vue à ajouter
    //!
    void addVue(Vue* v);

    /* maj vues */
    //!
    //! \fn void update()
    //! \brief provoque la fonction update dans toutes les vues
    //!
    void update();

    //!
    //! \fn void setQuantite(int qte)
    //! \brief Cette fonction fixe la quantité du produit que l'on veut acheter
    //! \param qte
    //!
    void setQuantite(int qte);

    //!
    //! \fn int getQuantite()
    //! \brief Cette fonction retourne la quantité du produit que l'on veut acheter
    //! \return Un entier
    //!
    int getQuantite();

    //!
    //! \fn Produit* getProduitCourant()
    //! \brief Cette fonction retourne le produit courant
    //! \return Le produit courant
    //!
    Produit* getProduitCourant();

    //!
    //! \fn void setProduitCourant(Produit *p)
    //! \brief Cette fonction fixe le produit courant lorsque l'on consulte la fiche d'un produit
    //! \param p - Produit consulté
    //!
    void setProduitCourant(Produit *p);

    /* connexion */
    //!
    //! \fn void connecterUtilisateur(std::string pseudo, std::string mdp)
    //! \brief connecte l'utilisateur avec ce pseudo et ce mot de passe s'il existe
    //! \param pseudo - pseudo de l'utilisateur qui veut se connecter
    //! \param mdp - mot de passe de l'utilisateur qui veut se connecter
    //!
    void connecterUtilisateur(std::string pseudo, std::string mdp);

    /* déconnexion */
    //!
    //! \fn void deconnecterUtilisateur()
    //! \brief déconnecte l'utilisateur
    //!
    void deconnecterUtilisateur();

    /* savoir si on est connecté */
    //!
    //! \fn bool isConnecte()
    //! \brief retourne true si un utilisateur est connecté, false sinon
    //! \return true si un utilisateur est connecté, false sinon
    //!
    bool isConnecte();

    /* retourner un pointeur vers l'utilisateur connecté */
    //!
    //! \fn Utilisateur* getUtilisateurConnecte()
    //! \brief récupère un pointeur vers l'utilisateur actuellement connecté
    //! \return pointeur vers l'utilisateur connecté
    //!
    Utilisateur* getUtilisateurConnecte();

    /* inscrire */
    //!
    //! \fn void inscrire(std::string monPseudo, std::string monMdp, std::string name, std::string firstname, int jourNaiss, int moisNaiss, int anneeNaiss, std::string mail, std::string adr, int codePostal)
    //! \brief inscrire un nouvel utilisateur et le stocker dans utilisateurs
    //! \param monPseudo - pseudo de l'utilisateur à inscrire
    //! \param monMdp - mot de passe de l'utilisateur à inscrire
    //! \param name - nom de l'utilisateur à inscrire
    //! \param firstname - prenom de l'utilisateur à inscrire
    //! \param jourNaiss - jour de la date de naissance de l'utilisateur à inscrire
    //! \param moisNaiss - mois de la date de naissance de l'utilisateur à inscrire
    //! \param anneeNaiss - année de la date de naissance de l'utilisateur à inscrire
    //! \param mail - adresse mail de l'utilisateur à inscrire
    //! \param adr - adresse de l'utilisateur à inscrire
    //! \param codePostal - code postal de l'utilisateur à inscrire
    //!
    void inscrire(std::string monPseudo, std::string monMdp, std::string name, std::string firstname,
                  int jourNaiss, int moisNaiss, int anneeNaiss, std::string mail, std::string adr, int codePostal);

    /*modifier profil */
    //!
    //! \fn void modifierProfil(std::string nom, std::string prenom, std::string mail, int codePostal, std::string ville, std::string adresse)
    //! \brief modifie le profil avec ces informations
    //! \param nom - nouveau nom
    //! \param prenom - nouveau prénom
    //! \param mail - nouvelle adresse mail
    //! \param codePostal - nouveau code postal
    //! \param ville - nouvelle ville
    //! \param adresse - nouvelle adresse
    //!
    void modifierProfil(std::string nom, std::string prenom, std::string mail,
                        int codePostal, std::string ville, std::string adresse);

    //!
    //! \fn void acheterProduit(Produit* p)
    //! \brief acheterProduit - Acheter un produit, avec suppression du produit si la quantité arrive à 0
    //! \param p - Pointeur vers le produit à acheter
    //! \param quantite - Quantité de produit acheté
    //!
    void acheterProduit(Produit* p, int quantite);

    /* recherche utilisateur */
    //!
    //! \fn Utilisateur* rechercherUtilisateur(std::string pseudo)
    //! \brief recherche l'utilisateur avec ce pseudo
    //! \param pseudo - pseudo recherché
    //! \return un pointeur vers l'utilisateur recherché
    //!
    Utilisateur* rechercherUtilisateur(std::string pseudo);

    /* ajouter vente */
    //!
    //! \fn void ajouterVente(std::string n, std::string cat, float prix, unsigned int qte, bool etat)
    //! \brief ajoute un produit en vente normale avec ces caractéristiques
    //! \param n - nom du produit
    //! \param cat - catégorie du produit
    //! \param prix - prix du produit
    //! \param qte - quantité du produit
    //! \param etat - état du produit (en enchère ou non)
    //!
    void ajouterVente(std::string n, std::string cat, float prix, unsigned int qte, bool etat);

    //!
    //! \fn void ajouterVente(std::string n, std::string cat, float prix, unsigned int qte, bool etat, struct tm date)
    //! \brief ajoute un produit en vente aux enchères avec ces caractéristiques
    //! \param n - nom du produit
    //! \param cat - catégorie du produit
    //! \param prix - prix du produit
    //! \param qte - quantité du produit
    //! \param etat - état du produit (enchère ou non)
    //! \param date - date limite de l'enchère du produit
    //!
    void ajouterVente(std::string n, std::string cat, float prix, unsigned int qte, bool etat, struct tm date);

    /* ventes en cours */
    //!
    //! \fn std::vector<Produit*> ventesEnCours()
    //! \brief rtourne les ventes en cours
    //! \return un vector contenant des pointeurs vers les produits en vente
    //!
    std::vector<Produit*> ventesEnCours();

    /* recherche produit */
    //!
    //! \fn Produit* rechercherProduit(std::string ref)
    //! \brief recherche le produit avec cette référence
    //! \param ref - référence du produit recherché
    //! \return le produit recherché
    //!
    Produit* rechercherProduit(std::string ref);

    //!
    //! \fn std::vector<Produit*> rechercherTags(std::string t)
    //! \brief recherche un produit par tags (c'est à dire nom, catégorie)
    //! \param t - tags recherchés
    //! \return un vector contenant des pointeurs sur les produits trouvés
    //!
    std::vector<Produit*> rechercherTags(std::string t);

};

#endif // GESTIONBDD_H
