#include "MaFenetre.h"

using namespace std;

MaFenetre::MaFenetre(int l, int h, GestionBdd *bdd) : largeur(l), hauteur(h), gestionBdd(bdd)
{
    gestionBdd->addVue(this);
    setFixedSize(largeur, hauteur);    // taille fenetre
    //QTimer::singleShot(1000, this, SLOT(showFullScreen()));

    /* layouts */
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setAlignment(Qt::AlignTop);
    haut = new QHBoxLayout();
    centre = new QVBoxLayout();
    centre->setAlignment(Qt::AlignTop);
    bas = new QHBoxLayout();

    /*********************************************
     * HAUT                                      *
     * ******************************************/

    /* liste deroulante pour le type de recherche */
    typeRecherche = new QComboBox;
    typeRecherche->addItem("Produit");
    typeRecherche->addItem("Utilisateur");

    /* texte de la recherche */
    valRecherche = new QLineEdit;

    /* bouton rechercher */
    boutonRecherche = new QPushButton("Rechercher");

    QObject::connect(boutonRecherche, SIGNAL(clicked()), this, SLOT(rechercher()));
    QObject::connect(this,SIGNAL(signalRechercheUtilisateur(std::vector<Utilisateur*>)),this, SLOT(afficherResUtilisateurs(std::vector<Utilisateur*>)));
    QObject::connect(this,SIGNAL(signalRechercheProduits(std::vector<Produit*>)),this, SLOT(afficherResProduits(std::vector<Produit*>)));

    /* bouton accueil */
    boutonAccueil = new QPushButton("Accueil");
    QObject::connect(boutonAccueil, SIGNAL(clicked()), this, SLOT(accueil()));

    /* bouton profil */
    boutonProfil = new QPushButton("Mon profil");
    QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profil()));

    /* bouton ajouterVente */
    boutonAjouterVente = new QPushButton("Ajouter vente");
    QObject::connect(boutonAjouterVente, SIGNAL(clicked()), this, SLOT(ajouterVente()));

    /* label peudo de l'utilisateur connecté */
    pseudoConnecte = new QLabel("");

    /* bouton connexion */
    boutonConnexion = new QPushButton("Se connecter");     // bouton connexion
    QObject::connect(boutonConnexion, SIGNAL(clicked()), this, SLOT(connexion()));

    /* Layouts */
    haut->addWidget(typeRecherche);
    haut->addWidget(valRecherche);
    haut->addWidget(boutonRecherche);
    haut->addWidget(boutonAccueil);
    haut->addWidget(boutonProfil);
    haut->addWidget(boutonAjouterVente);
    haut->addWidget(pseudoConnecte);
    haut->addWidget(boutonConnexion);

    /*********************************************
     * CENTRE                                    *
     * ******************************************/

    /* Titre de la section */
    titreSection = new QLabel("Ventes en cours", this);
    QScrollArea *defile = new QScrollArea;
    defile->setLayout(centre);
    emit signalRechercheProduits(gestionBdd->ventesEnCours());

    /*********************************************
     * BAS                                       *
     * ******************************************/

    /* Boutons de changement de page */
    boutonPrecedent = new QPushButton("<");
    boutonSuivant = new QPushButton(">");
    numPage = new QLabel("1");
    bas->addWidget(boutonPrecedent);
    bas->addWidget(numPage);
    bas->addWidget(boutonSuivant);
    bas->setAlignment(Qt::AlignHCenter);


    /* Alignement vertical */
    vLayout->addLayout(haut);
    vLayout->addWidget(titreSection);
    vLayout->addWidget(defile);
    vLayout->addLayout(bas);

    setLayout(vLayout);


}

/************************************
 * FONCTIONS                        *
 * **********************************/

void MaFenetre::rechercher() {
    /* Récupération des valeurs pour la recherche */
    string type = typeRecherche->currentText().toStdString();
    string val = valRecherche->text().toStdString();

    if(type.compare("Utilisateur") == 0) {
        /* Recherche d'un utilisateur */
        vector<Utilisateur*> v = gestionBdd->rechercherUtilisateurs(val);
        emit signalRechercheUtilisateur(v);
        titreSection->setText("Résultats de la recherche de l'utilisateur " + QString::fromStdString(val));

    }else {
        /* Recherche d'un produit */
        vector<Produit*> v = gestionBdd->rechercherTags(val);
        emit signalRechercheProduits(v);
        titreSection->setText("Résultats de la recherche de la référence " + QString::fromStdString(val));
    }
}

/* retour à l'accueil avec l'affichage des ventes en cours */
void MaFenetre::accueil() {
    titreSection->setText("Ventes en cours");
    emit signalRechercheProduits(gestionBdd->ventesEnCours());
}

/* voir mon profil */
void MaFenetre::profil() {
    if(!gestionBdd->isConnecte()) {
        QMessageBox::warning(this, "Consulter son profil", "Attention, vous devez être connecté pour consulter son profil !");
    } else {
        titreSection->setText("Mon profil");
        clearLayout(centre);
        QHBoxLayout *box = new QHBoxLayout;
        QGroupBox *boxTxt = new QGroupBox;
        QHBoxLayout *boxButtons = new QHBoxLayout;
        box->setAlignment(Qt::AlignLeft);
        boxButtons->setAlignment(Qt::AlignLeft);
        boutonProfil = new QPushButton("Mon profil");
        QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profil()));
        box->addWidget(boutonProfil);
        boutonStatistiques = new QPushButton("Mes statistiques");
        QObject::connect(boutonStatistiques, SIGNAL(clicked()), this, SLOT(statistiques()));
        box->addWidget(boutonStatistiques);
        boutonVentes = new QPushButton("Mes ventes");
        QObject::connect(boutonVentes, SIGNAL(clicked()), this, SLOT(ventes()));
        box->addWidget(boutonVentes);
        boutonAchats = new QPushButton("Mes achats");
        QObject::connect(boutonAchats, SIGNAL(clicked()), this, SLOT(achats()));
        box->addWidget(boutonAchats);

        QGridLayout *grille = new QGridLayout();
        QString pseudo = QString::fromStdString(gestionBdd->getUtilisateurConnecte()->getPseudo());
        QString nom = QString::fromStdString(gestionBdd->getUtilisateurConnecte()->getNom());
        QString prenom = QString::fromStdString(gestionBdd->getUtilisateurConnecte()->getPrenom());
        QString ddn = QString::fromStdString(gestionBdd->getUtilisateurConnecte()->getDateNaissance());
        QString email = QString::fromStdString(gestionBdd->getUtilisateurConnecte()->getEmail());
        grille->addWidget(new QLabel("<b>Pseudo : </b>" + pseudo), 0, 0);
        grille->addWidget(new QLabel("<b>Nom : </b>" + nom), 1, 0);
        grille->addWidget(new QLabel("<b>Prénom : </b>" + prenom), 2, 0);
        grille->addWidget(new QLabel("<b>Date de naissance : </b>" + ddn), 3, 0);
        grille->addWidget(new QLabel("<b>Email : </b>" + email), 4, 0);
        QPushButton *modifProfil = new QPushButton("Modifier profil");
        QObject::connect(modifProfil, SIGNAL(clicked()), this, SLOT(modificationProfil()));
        boxButtons->addWidget(modifProfil);
        boxTxt->setLayout(grille);

        centre->addLayout(box);
        centre->addWidget(boxTxt);
        centre->addLayout(boxButtons);
    }
}

/* voir mes statistiques */
void MaFenetre::statistiques() {
    if(!gestionBdd->isConnecte()) {
        QMessageBox::warning(this, "Consulter son profil", "Attention, vous devez être connecté pour consulter son profil !");
    } else {
        titreSection->setText("Mes statistiques");
        clearLayout(centre);
        QHBoxLayout *box = new QHBoxLayout;
        QGroupBox *boxTxt = new QGroupBox;
        box->setAlignment(Qt::AlignLeft);
        boutonProfil = new QPushButton("Mon profil");
        QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profil()));
        box->addWidget(boutonProfil);
        boutonStatistiques = new QPushButton("Mes statistiques");
        QObject::connect(boutonStatistiques, SIGNAL(clicked()), this, SLOT(statistiques()));
        box->addWidget(boutonStatistiques);
        boutonVentes = new QPushButton("Mes ventes");
        QObject::connect(boutonVentes, SIGNAL(clicked()), this, SLOT(ventes()));
        box->addWidget(boutonVentes);
        boutonAchats = new QPushButton("Mes achats");
        QObject::connect(boutonAchats, SIGNAL(clicked()), this, SLOT(achats()));
        box->addWidget(boutonAchats);

        QGridLayout *grille = new QGridLayout();
        string ventes = to_string(gestionBdd->getUtilisateurConnecte()->getNbVentes());
        string achats = to_string(gestionBdd->getUtilisateurConnecte()->getNbAchats());
        string notation = to_string(gestionBdd->getUtilisateurConnecte()->getNote());
        QString nbVentes = QString::fromStdString(ventes);
        QString nbAchats = QString::fromStdString(achats);
        QString note = QString::fromStdString(notation);

        grille->addWidget(new QLabel("<b>Note globale : </b>" + note + "/5"), 0, 0);
        grille->addWidget(new QLabel("<b>Nombre de ventes : </b>" + nbVentes), 1, 0);
        grille->addWidget(new QLabel("<b>Nombre d\'achats : </b>" + nbAchats), 2, 0);
        grille->addWidget(new QLabel(""), 3, 0);
        grille->addWidget(new QLabel("<b>Avis</b>"), 4, 0);
        vector<Avis>::iterator it;
        vector<Avis> avis = gestionBdd->getUtilisateurConnecte()->getLesAvis();
        int ligne = 5;
        int colonne = 0;
        for(it = avis.begin();it != avis.end();it++) {
            QString auteur = QString::fromStdString((it)->getAuteur());
            QString note = QString::fromStdString(to_string((it)->getNote()));
            QString commentaire = QString::fromStdString((it)->getCommentaire());
            grille->addWidget(new QLabel("<b>Auteur : </b>" + auteur), ligne, colonne);
            colonne++;
            grille->addWidget(new QLabel("<b>Note : </b>" + note), ligne, colonne);
            ligne++;
            colonne = 0;
            grille->addWidget(new QLabel("<b>Commentaire : </b>" + commentaire), ligne, colonne);
            ligne++;
        }
        boxTxt->setLayout(grille);

        centre->addLayout(box);
        centre->addWidget(boxTxt);
    }
}

/* voir mes ventes */
void MaFenetre::ventes() {
    if(!gestionBdd->isConnecte()) {
        QMessageBox::warning(this, "Consulter son profil", "Attention, vous devez être connecté pour consulter son profil !");
    } else {
        titreSection->setText("Mes ventes");
        clearLayout(centre);
        QHBoxLayout *box = new QHBoxLayout;
        box->setAlignment(Qt::AlignLeft);
        boutonProfil = new QPushButton("Mon profil");
        QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profil()));
        box->addWidget(boutonProfil);
        boutonStatistiques = new QPushButton("Mes statistiques");
        QObject::connect(boutonStatistiques, SIGNAL(clicked()), this, SLOT(statistiques()));
        box->addWidget(boutonStatistiques);
        boutonVentes = new QPushButton("Mes ventes");
        QObject::connect(boutonVentes, SIGNAL(clicked()), this, SLOT(ventes()));
        box->addWidget(boutonVentes);
        boutonAchats = new QPushButton("Mes achats");
        QObject::connect(boutonAchats, SIGNAL(clicked()), this, SLOT(achats()));
        box->addWidget(boutonAchats);

        centre->addLayout(box);
    }
}

/* voir mes achats */
void MaFenetre::achats() {
    if(!gestionBdd->isConnecte()) {
        QMessageBox::warning(this, "Consulter son profil", "Attention, vous devez être connecté pour consulter son profil !");
    } else {
        titreSection->setText("Mes achats");
        clearLayout(centre);
        QHBoxLayout *box = new QHBoxLayout;
        box->setAlignment(Qt::AlignLeft);
        boutonProfil = new QPushButton("Mon profil");
        QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profil()));
        box->addWidget(boutonProfil);
        boutonStatistiques = new QPushButton("Mes statistiques");
        QObject::connect(boutonStatistiques, SIGNAL(clicked()), this, SLOT(statistiques()));
        box->addWidget(boutonStatistiques);
        boutonVentes = new QPushButton("Mes ventes");
        QObject::connect(boutonVentes, SIGNAL(clicked()), this, SLOT(ventes()));
        box->addWidget(boutonVentes);
        boutonAchats = new QPushButton("Mes achats");
        QObject::connect(boutonAchats, SIGNAL(clicked()), this, SLOT(achats()));
        box->addWidget(boutonAchats);

        centre->addLayout(box);
    }
}

/* ajouter une vente */
void MaFenetre::ajouterVente() {
    if(gestionBdd->isConnecte()) {
        ajouterVentes = new DialogAjouterVente(gestionBdd);
    }else {
        QMessageBox::warning(this, "Ajouter une vente", "Attention, vous devez être connecté pour ajouter un produit en vente !");
    }
}

/* modification de profil */
void MaFenetre::modificationProfil() {
    if(gestionBdd->isConnecte()) {
        modifProfil = new DialogModificationProfil(gestionBdd);
    } else {
        QMessageBox::warning(this, "Modifier son profil", "Attention, vous devez être connecté pour modifier son profil !");
    }
}

/* connexion */
void MaFenetre::connexion() {
    if(gestionBdd->isConnecte()) {
        gestionBdd->deconnecterUtilisateur();
        pseudoConnecte->setText("");
        boutonConnexion->setText("Se connecter");
    }else {
        connexions = new DialogConnexion(gestionBdd);
    }
}

/* affichage du résultat d'une recherche d'utilisateurs */
void MaFenetre::afficherResUtilisateurs(vector<Utilisateur*> v) {
    clearLayout(centre);
    /* pour chaque utilisateur correspondant */
    vector<Utilisateur*>::iterator it;
    int i = 0;
    for(it = v.begin();it != v.end();it++) {
        QHBoxLayout *box = new QHBoxLayout;
        box->setAlignment(Qt::AlignLeft);
        string pseudoStr = (*it)->getPseudo();
        QString pseudo = QString::fromStdString(pseudoStr);
        QString note = QString::number((*it)->getNote());
        /* affichage du pseudo et de la note */
        box->addWidget(new QLabel("Pseudo : " + pseudo + "  -   Note : " + note));
        /* création d'un bouton pour accéder au profil concerné */
        QPushButton *voirProfil = new QPushButton("Voir profil");
        QObject::connect(voirProfil, SIGNAL(clicked()), &mapper, SLOT( map() ));
        //QObject::connect(voirProfil, SIGNAL(clicked()), this, SLOT(voirProfil(string pseudoStr)));
        mapper.setMapping(voirProfil, pseudo);
        box->addWidget(voirProfil);
        centre->addLayout(box);
        i++;
    }
    connect( &mapper, SIGNAL( mapped(QString) ), this, SLOT( profilAutreUtilisateur(QString) ) );
    centre->update();
}

/* voir profil du pseudo donné */
void MaFenetre::profilAutreUtilisateur(QString pseudonyme) {
    if(!gestionBdd->isConnecte()) {
        QMessageBox::warning(this, "Consulter un profil", "Attention, vous devez être connecté pour consulter un profil !");
    } else {
        titreSection->setText("Profil");
        clearLayout(centre);
        QHBoxLayout *box = new QHBoxLayout;
        QGroupBox *boxTxt = new QGroupBox;
        QHBoxLayout *boxButtons = new QHBoxLayout;
        box->setAlignment(Qt::AlignLeft);
        boxButtons->setAlignment(Qt::AlignLeft);
        boutonProfil = new QPushButton("Profil");
        QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profilAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonProfil);
        boutonStatistiques = new QPushButton("Statistiques");
        QObject::connect(boutonStatistiques, SIGNAL(clicked()), this, SLOT(statistiquesAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonStatistiques);
        boutonVentes = new QPushButton("Ventes");
        QObject::connect(boutonVentes, SIGNAL(clicked()), this, SLOT(ventesAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonVentes);
        boutonAchats = new QPushButton("Achats");
        QObject::connect(boutonAchats, SIGNAL(clicked()), this, SLOT(achatsAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonAchats);

        QGridLayout *grille = new QGridLayout();
        QString pseudo = QString::fromStdString(gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getPseudo());
        QString nom = QString::fromStdString(gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getNom());
        QString prenom = QString::fromStdString(gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getPrenom());
        QString ddn = QString::fromStdString(gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getDateNaissance());
        QString email = QString::fromStdString(gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getEmail());
        grille->addWidget(new QLabel("<b>Pseudo : </b>" + pseudo), 0, 0);
        grille->addWidget(new QLabel("<b>Nom : </b>" + nom), 1, 0);
        grille->addWidget(new QLabel("<b>Prénom : </b>" + prenom), 2, 0);
        grille->addWidget(new QLabel("<b>Date de naissance : </b>" + ddn), 3, 0);
        grille->addWidget(new QLabel("<b>Email : </b>" + email), 4, 0);
        boxTxt->setLayout(grille);

        centre->addLayout(box);
        centre->addWidget(boxTxt);
        centre->addLayout(boxButtons);
    }
}

/* voir les statistiques d'un pseudo */
void MaFenetre::statistiquesAutreUtilisateur(QString pseudonyme) {
    if(!gestionBdd->isConnecte()) {
        QMessageBox::warning(this, "Consulter un profil", "Attention, vous devez être connecté pour consulter un profil !");
    } else {
        titreSection->setText("Mes statistiques");
        clearLayout(centre);
        QHBoxLayout *box = new QHBoxLayout;
        QGroupBox *boxTxt = new QGroupBox;
        box->setAlignment(Qt::AlignLeft);
        boutonProfil = new QPushButton("Profil");
        QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profilAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonProfil);
        boutonStatistiques = new QPushButton("Statistiques");
        QObject::connect(boutonStatistiques, SIGNAL(clicked()), this, SLOT(statistiquesAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonStatistiques);
        boutonVentes = new QPushButton("Ventes");
        QObject::connect(boutonVentes, SIGNAL(clicked()), this, SLOT(ventesAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonVentes);
        boutonAchats = new QPushButton("Achats");
        QObject::connect(boutonAchats, SIGNAL(clicked()), this, SLOT(achatsAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonAchats);

        QGridLayout *grille = new QGridLayout();
        string ventes = to_string(gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getNbVentes());
        string achats = to_string(gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getNbAchats());
        string notation = to_string(gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getNote());
        QString nbVentes = QString::fromStdString(ventes);
        QString nbAchats = QString::fromStdString(achats);
        QString note = QString::fromStdString(notation);

        grille->addWidget(new QLabel("<b>Note globale : </b>" + note + "/5"), 0, 0);
        grille->addWidget(new QLabel("<b>Nombre de ventes : </b>" + nbVentes), 1, 0);
        grille->addWidget(new QLabel("<b>Nombre d\'achats : </b>" + nbAchats), 2, 0);
        grille->addWidget(new QLabel(""), 3, 0);
        grille->addWidget(new QLabel("<b>Avis</b>"), 4, 0);
        vector<Avis>::iterator it;
        vector<Avis> avis = gestionBdd->rechercherUtilisateur(pseudonyme.toStdString())->getLesAvis();
        int ligne = 5;
        int colonne = 0;
        for(it = avis.begin();it != avis.end();it++) {
            QString auteur = QString::fromStdString((it)->getAuteur());
            QString note = QString::fromStdString(to_string((it)->getNote()));
            QString commentaire = QString::fromStdString((it)->getCommentaire());
            grille->addWidget(new QLabel("<b>Auteur : </b>" + auteur), ligne, colonne);
            colonne++;
            grille->addWidget(new QLabel("<b>Note : </b>" + note), ligne, colonne);
            ligne++;
            colonne = 0;
            grille->addWidget(new QLabel("<b>Commentaire : </b>" + commentaire), ligne, colonne);
            ligne++;
        }
        boxTxt->setLayout(grille);

        centre->addLayout(box);
        centre->addWidget(boxTxt);
    }
}

/* voir les ventes d'un pseudo */
void MaFenetre::ventesAutreUtilisateur(QString pseudonyme) {
    if(!gestionBdd->isConnecte()) {
        QMessageBox::warning(this, "Consulter un profil", "Attention, vous devez être connecté pour consulter un profil !");
    } else {
        titreSection->setText("Mes ventes");
        clearLayout(centre);
        QHBoxLayout *box = new QHBoxLayout;
        box->setAlignment(Qt::AlignLeft);
        boutonProfil = new QPushButton("Profil");
        QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profilAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonProfil);
        boutonStatistiques = new QPushButton("Statistiques");
        QObject::connect(boutonStatistiques, SIGNAL(clicked()), this, SLOT(statistiquesAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonStatistiques);
        boutonVentes = new QPushButton("Ventes");
        QObject::connect(boutonVentes, SIGNAL(clicked()), this, SLOT(ventesAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonVentes);
        boutonAchats = new QPushButton("Achats");
        QObject::connect(boutonAchats, SIGNAL(clicked()), this, SLOT(achatsAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonAchats);

        centre->addLayout(box);
    }
}

/* voir les achats selon un pseudo */
void MaFenetre::achatsAutreUtilisateur(QString pseudonyme) {
    if(!gestionBdd->isConnecte()) {
        QMessageBox::warning(this, "Consulter un profil", "Attention, vous devez être connecté pour consulter un profil !");
    } else {
        titreSection->setText("Mes achats");
        clearLayout(centre);
        QHBoxLayout *box = new QHBoxLayout;
        box->setAlignment(Qt::AlignLeft);
        boutonProfil = new QPushButton("Profil");
        QObject::connect(boutonProfil, SIGNAL(clicked()), this, SLOT(profilAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonProfil);
        boutonStatistiques = new QPushButton("Statistiques");
        QObject::connect(boutonStatistiques, SIGNAL(clicked()), this, SLOT(statistiquesAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonStatistiques);
        boutonVentes = new QPushButton("Ventes");
        QObject::connect(boutonVentes, SIGNAL(clicked()), this, SLOT(ventesAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonVentes);
        boutonAchats = new QPushButton("Achats");
        QObject::connect(boutonAchats, SIGNAL(clicked()), this, SLOT(achatsAutreUtilisateur(pseudonyme)));
        box->addWidget(boutonAchats);

        centre->addLayout(box);
    }
}

/* affichage du résultat d'une recherche de produits */
void MaFenetre::afficherResProduits(vector<Produit*> v) {
    clearLayout(centre);
    vector<Produit*>::iterator it;
    for(it = v.begin();it != v.end();it++) {
        /* création d'une grille pour chaque produit */
        QGroupBox *box = new QGroupBox;
        QGridLayout *grille = new QGridLayout();

        /* conversion des champs string du produit en QString */
        QString ref = QString::fromStdString((*it)->getReference());
        QString nom = QString::fromStdString((*it)->getNom());
        QString cat = QString::fromStdString((*it)->getCategorie());
        QString prix = QString::number((*it)->getPrixActuel());
        QString qte = QString::number((*it)->getQuantite());
        QString vendeur = QString::fromStdString((*it)->getVendeur());
        QString dateDepot = QString::fromStdString((*it)->getDateDepot());

        /* agencement dans le GridLayout */
        grille->addWidget(new QLabel("Nom : " + nom), 0, 0);
        grille->addWidget(new QLabel("Référence : " + ref), 0, 1);
        grille->addWidget(new QLabel("Catégorie : " + cat), 1, 0);
        grille->addWidget(new QLabel("Date du dépôt : " + dateDepot), 2, 0);
        grille->addWidget(new QLabel("Quantité : " + qte), 3, 0);
        grille->addWidget(new QLabel("Vendeur : " + vendeur), 4, 0);

        /* affichages spécifiques aux enchères ou ventes normales */
        if((*it)->getEtatVente() == "Vente aux enchères") {
            QString dateLimite = QString::fromStdString((*it)->getDateLimite());
            grille->addWidget(new QLabel("Date Limite : " + dateLimite));
            grille->addWidget(new QLabel("Prix Actuel : " + prix), 0, 4);
            grille->addWidget(new QLabel("Vente aux Enchères"), 2, 4);
        }else {
            grille->addWidget(new QLabel("Prix Unitaire : " + prix), 0, 4);
            grille->addWidget(new QLabel("Vente Normale"), 2, 4);
        }

        /* création d'un bouton pour accéder au produit concerné */
        QPushButton *voirProduit = new QPushButton("Voir produit");
        grille->addWidget(voirProduit, 2, 5);
        QObject::connect(voirProduit, SIGNAL(clicked()), this, SLOT(voirProduit(string)));

        box->setLayout(grille);
        centre->addWidget(box);
    }
    centre->update();
}

void MaFenetre::voirProduit(string ref) {

}

void MaFenetre::update() {
    if(gestionBdd->isConnecte()) {
        /* mets à jour l'interface à la connexion */
        pseudoConnecte->setText(QString::fromStdString(gestionBdd->getUtilisateurConnecte()->getPseudo()));
        boutonConnexion->setText("Se déconnecter");
    }
    if(titreSection->text() == "Ventes en cours") {
        /* mets à jour l'affichage des ventes en cours en cas d'ajout */
        emit signalRechercheProduits(gestionBdd->ventesEnCours());
    }
}

/* vide le layout */
void MaFenetre::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
        }

        layout -> removeItem(item);
        delete item->widget();
        delete item;
    }
}
