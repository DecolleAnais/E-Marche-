#include "EtatVente.h"

using namespace std;

EtatVente::EtatVente(bool b):typeDeVente(b){

}

bool EtatVente::typeVente(){
    return typeDeVente;
}

float EtatVente::getPrixActuel(){
    return prixActuel;
}

string EtatVente::getDateLimite(){
    string result;
    stringstream sstm;

    sstm << dateLimite.tm_mday << "/" << dateLimite.tm_mon << "/" << dateLimite.tm_year;
    result = sstm.str();

    return result;
}

void EtatVente::setPrixActuel(float prix){
    prixActuel = prix;
}

void EtatVente::setDateLimite(struct tm date){
    dateLimite = date;
}
