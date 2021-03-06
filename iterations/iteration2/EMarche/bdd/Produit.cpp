#include "Produit.h"

using namespace std;

string Produit::getVendeur() {
    return vendeur;
}

unsigned int Produit::getQuantite(){
    return quantite;
}

float Produit::getPrixUnitaire(){
    return prixUnitaire;
}

string Produit::getReference(){
    return reference;
}

string Produit::getNom(){
    return nom;
}

string Produit::getCategorie(){
    return categorie->getNom();
}

string Produit::getDateDepot(){
    string result;
    stringstream sstm;

    sstm << dateDepot.tm_mday << "/" << dateDepot.tm_mon << "/" << dateDepot.tm_year;
    result = sstm.str();

    return result;
}

string Produit::getDateAchatVente(){
    string result;
    stringstream sstm;

    sstm << dateAchatVente.tm_mday << "/" << dateAchatVente.tm_mon << "/" << dateAchatVente.tm_year;
    result = sstm.str();

    return result;
}

string Produit::getEtatVente(){
    if(etatVente->typeVente() == false){
        return "Vente normale";
    } else {
        return "Vente aux enchères";
    }
}

float Produit::getPrixActuel(){
    if(etatVente->typeVente() == true){
        return etatVente->getPrixActuel();
    }
    return prixUnitaire;
}

string Produit::getTags(){
    string result;
    stringstream sstm;

    unsigned int i = 0;
    while(i < tags.size()) {
        sstm << tags[i] << "; ";
        i++;
    }

    result = sstm.str();
    return result;
}

vector<string> Produit::getTagsVector(){
    return tags;
}

string Produit::getDateLimite(){
    if(etatVente->typeVente() == true)
        return etatVente->getDateLimite();
    else
        return "";
}

void Produit::setReference(string r) {
    reference = r;
}

void Produit::setQuantite(unsigned int q){
    quantite = q;
}

void Produit::setDateVenteAchat(int jour, int mois, int annee){
    dateAchatVente.tm_mday = jour;
    dateAchatVente.tm_mon = mois;
    dateAchatVente.tm_year = annee;
}

void Produit::augmenterEnchere(int prix){
    if(etatVente->typeVente() == 1){
        etatVente->setPrixActuel(prix);
    }
}

void Produit::ajouterTag(std::string t){
    tags.push_back(t);
}
