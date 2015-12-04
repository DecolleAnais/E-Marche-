#include "Utilisateur.h"

using namespace std;

/* Fonctions get */
string Utilisateur::getPseudo() {
    return pseudo;
}

string Utilisateur::getMdp() {
    return mdp;
}

string Utilisateur::getNom() {
    return nom;
}

string Utilisateur::getPrenom() {
    return prenom;
}

string Utilisateur::getDateNaissance() {
    string result;
    stringstream sstm;

    sstm << dateNaissance.tm_mday << "/" << dateNaissance.tm_mon << "/" << dateNaissance.tm_year;
    result = sstm.str();

    return result;
}

string Utilisateur::getEmail() {
    return email;
}

string Utilisateur::getAdresse() {
    return adresse;
}

unsigned int Utilisateur::getNbVentes() {
    return nbVentes;
}

unsigned int Utilisateur::getNbAchats() {
    return nbAchats;
}

unsigned int Utilisateur::getNote() {
    return note;
}

/* Fonctions set */
void Utilisateur::setPseudo(string p) {
    pseudo = p;
}

void Utilisateur::setMdp(string m) {
    mdp = m;
}

void Utilisateur::setNom(string n) {
    nom = n;
}

void Utilisateur::setPrenom(string p) {
    prenom = p;
}

void Utilisateur::setDateNaissance(int jour, int mois, int annee) {
    dateNaissance.tm_mday = jour;
    dateNaissance.tm_mon = mois;
    dateNaissance.tm_year = annee;
}

void Utilisateur::setEmail(string e) {
    email = e;
}

void Utilisateur::setAdresse(string a) {
    adresse = a;
}

void Utilisateur::setNbVentes(unsigned int n) {
    nbVentes = n;
}

void Utilisateur::setNbAchats(unsigned int n) {
    nbAchats = n;
}

void Utilisateur::setNote(unsigned int n) {
    note = n;
}