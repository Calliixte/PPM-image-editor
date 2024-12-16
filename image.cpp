#include "filtre.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Constructeur de la classe Image, prenant en entrée des vecteurs représentant les canaux rouge, vert et bleu, et initialisant le nombre de lignes et de colonnes.
Image::Image(const vector<vector<int>> &vrouge,
             const vector<vector<int>> &vvert,
             const vector<vector<int>> &vbleu) {

  // Vérification si les vecteurs d'entrée ont la même taille pour chaque canal.
  if ((vrouge.size() != vvert.size()) or (vrouge.size() != vbleu.size()) or
      (vvert.size() != vbleu.size())) {
    throw invalid_argument("les vecteurs doivent avoir la même taille1");
  }
  // Vérification si les vecteurs de chaque canal ont la même taille pour chaque ligne.
  for (int i = 0; i < vrouge.size(); i++) {
    if (vrouge[i].size() != vvert[i].size() ||
        vrouge[i].size() != vbleu[i].size() ||
        vvert[i].size() != vbleu[i].size()) {
      throw invalid_argument("les vecteurs doivent avoir la même taille");
    }
  }
  // Attribution des vecteurs d'entrée aux canaux correspondent et initialisation des propriétés de l'image.
  _rouge = vrouge;
  _vert = vvert;
  _bleu = vbleu;
  _largeur = vrouge.size();
  _longueur = vrouge[0].size();
}


Image::Image(const string &picture) {

  vector<vector<int>> red;
  vector<vector<int>> green;
  vector<vector<int>> blue;
  // Declaration des variables
  string line; // pour recuperer les lignes du fichier image au format .ppm, qui
               // est code en ASCII.
  string format; // pour recuperer le format de l'image : celui-ci doit être de
                 // la forme P3
  string name;   // au cas où l'utilisateur se trompe dans le nom de l'image a
                 // charger, on redemande le nom.
  int taille;
  vector<int> mypixels; // pour recuperer les donnees du fichier de maniere
                        // lineaire. On repartira ensuite ces donnees dans les
                        // tableaux correspondants
  ifstream in; // Declaration d'un "flux" qui permettra ensuite de lire les
               // donnees de l'image.
  streambuf *oldbuf; // declaration d'un "buffer" qui permettra de rediriger les
                     // entrees standard (cin) sur le fichier image portant le
                     // nom picture
  int hauteur;       // pour bien verifier que l'image est carree, et de taille
                     // respectant les conditions fixees par l'enonce
  // Initialisation des variables
  name = picture;
  // Permet d'ouvrir le fichier portant le nom picture et de rediriger l'entree
  // standard sur le fichier portant le nom picture : ouverture du fichier
  // portant le nom picture
  in.open(name.c_str());
  // redirection de l'entree standard (cin) vers le fichier image.
  oldbuf = cin.rdbuf(in.rdbuf());
  // On verifie que le fichier a bien ete ouvert. Si cela n'est pas le cas, on
  // redemande un nom de fichier valide
  while (!in) {
    cin.rdbuf(oldbuf);
    cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
    cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention ce fichier "
            "doit avoir un nom du type nom.ppm."
         << endl;
    cin >> name;
    in.open(name.c_str()); // relance
    oldbuf = cin.rdbuf(in.rdbuf());
  }
  // Lecture du nombre definissant le format (ici P3)
  // getline(cin, format);
  cin >> format;
  // on finit de lire la ligne (caractere d'espacement)
  getline(cin, line);
  // Lecture du commentaire
  getline(cin, line);
  // lecture des dimensions
  cin >> taille >> hauteur;
  getline(cin, line); // on finit de lire la ligne (caractere d'espacement)
  // On verifie que l'image a une taille qui verifie bien les conditions
  // requises par l'enonce. Si �a n'est pas le cas, on redemande un fichier
  // valide, et ce, tant que necessaire.
  while (taille != hauteur || format != "P3") {
    if (format != "P3") {
      cerr << "Erreur! L'image que vous nous avez donnee a un format ne "
              "verifiant pas les conditions requises."
           << endl;
      cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et "
              "non en brut."
           << endl;
    }
    if (taille != hauteur)
      cerr << "Erreur! L'image que vous nous avez donne n'est pas carree."
           << endl;
    in.close();
    // On va redemander un nom de fichier valide.
    do {
      cin.rdbuf(oldbuf);
      cerr << "Veuillez redonner un nom de fichier qui respecte les conditions "
              "de format et de taille. Attention, ce nom doit etre de la forme "
              "nom.ppm."
           << endl;
      cin >> name;
      in.open(name.c_str()); // relance
      oldbuf = cin.rdbuf(in.rdbuf());
    } while (!in);
    // Lecture du nombre definissant le format (ici P3)
    // getline(cin, format);
    cin >> format;
    getline(cin, line); // on finit de lire la ligne (caractere d'espacement)
    // Lecture du commentaire
    getline(cin, line);
    // lecture des dimensions
    cin >> taille >> hauteur; // relance
    getline(cin, line); // on finit de lire la ligne (caractere d'espacement)
  }
  // Lecture de la valeur max
  getline(cin, line);
  // Lecture des donnees et ecriture dans les tableaux :
  //  Pour plus de simplicite, on stocke d'abord toutes les donnees dans
  //  mypixels dans l'ordre de lecture puis ensuite on les repartira dans les
  //  differents tableaux.
  // Les donnees stockees dans mypixels sont de la forme RGB RGB RGB ....
  //  Il faudra donc repartir les valeurs R correspondant a la composante rouge
  //  de l'image dans le tableau red, de même pour G et B.
  int pix;
  mypixels.resize(3 * taille *
                  taille); // taille fixe : on alloue une fois pour toutes
  for (int i = 0; i < 3 * taille * taille; i++) {
    cin >> pix;
    mypixels[i] = pix;
  }
  // Remplissage des 3 tableaux : on repartit maintenant les valeurs dans les
  // bonnes composantes Comme dans mypixels, les donnees sont stockees de la
  // maniere suivante : RGB RGB RGB, il faut mettre les valeurs correspondant a
  // la composante rouge dans red, ... Ainsi, les valeurs de la composante rouge
  // correspondent aux valeurs stockes aux indices congrus a 0 mod 3 dans
  // mypixels, que les valeurs de la composante verte correspond aux valeurs
  // stockes aux indices sont congrus a 1 mod 3, ...
  // les valeurs d'une ligne
  int val;
  red.resize(taille);
  green.resize(taille);
  blue.resize(taille);
  for (int i = 0; i < taille; i++) {
    vector<int> ligneR(taille);
    vector<int> ligneB(taille); // les lignes ont toutes la même taille
    vector<int> ligneG(taille);
    for (int j = 0; j < taille; j++) {
      val = mypixels[3 * j + 3 * taille * i];
      ;
      ligneR[j] = val;
      val = mypixels[3 * j + 1 + 3 * taille * i];
      ligneG[j] = val;
      val = mypixels[3 * j + 2 + 3 * taille * i];
      ligneB[j] = val;
    }
    red[i] = ligneR;
    green[i] = ligneG;
    blue[i] = ligneB;
  }
  // Informations a l'utilisateur pour dire que tout s'est bien passe
  cout << " L'image " << name << " a bien ete chargee dans les tableaux ."
       << endl;
  in.close();
  // On remet a nouveau l'entree standard sur la console
  _rouge = red;
  _vert = green;
  _bleu = blue;
  _longueur = taille;
  _largeur = hauteur;
  cin.rdbuf(oldbuf);
}



// Méthode pour extraire la composante rouge de l'image
Image Image::composanteRouge() {
  vector<vector<int>> vbleu = _bleu;
  vector<vector<int>> vvert = _vert;
  // Mise à zéro de la composante bleue
  for (int i = 0; i < _bleu.size(); i++) {
    for (int j = 0; j < _bleu[i].size(); j++) {
      vbleu[i][j] = 0;
    }
  }

  // Mise à zéro de la composante verte
  for (int i = 0; i < _vert.size(); i++) {
    for (int j = 0; j < _vert[i].size(); j++) {
      vvert[i][j] = 0;
    }
  }
  // Retourne une nouvelle image avec uniquement la composante rouge
  return Image(_rouge, vvert, vbleu);
}

// Méthode pour détecter la présence d'une couleur spécifique dans l'image
bool Image::detection(int val1, int val2, int val3) {
  bool couleurpres = false;  // Indique si la couleur spécifique est trouvée
  bool pixeltrouve = false;   // Indique si le pixel correspondant est trouvé
  for (int i = 0; i < _rouge.size(); i++) {
    for (int j = 0; j < _rouge[i].size(); j++) {
      // Vérifie si les valeurs RGB du pixel correspondent à la couleur spécifique
      couleurpres = (_rouge[i][j] == val1 && _vert[i][j] == val2 && _bleu[i][j] == val3);
      if (couleurpres)
        pixeltrouve = true;  // Si la couleur spécifique est trouvée, met pixeltrouvé à vrai
    }
  }
  return (pixeltrouve);  // Retourne si le pixel correspondant est trouvé
}

// Méthode pour convertir l'image en niveaux de gris
Image Image::niveauxDeGris() const {
  vector<vector<int>> gris;
  vector<int> gris1;
  for (int i = 0; i < _rouge.size(); i++) {
    for (int j = 0; j < _rouge[i].size(); j++) {
      gris1.push_back((_rouge[i][j] + _vert[i][j] + _bleu[i][j]) / 3); //creation du tableau gris avec l'addition de toutes les couleurs
    }
    gris.push_back(gris1);
  }
  return Image(gris, gris, gris);
}

//methode qui affiche entierement un vecteur 2d
void display2d(const vector<vector<int>> &v) {
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++) {
      cout << v[i][j] << " ";
    }
    cout << endl;
  }
}

//methode qui affiche entierement les trois vecteurs de l'image
void displaycouleur(const Image &im) {
  cout << "rouge" << endl;
  display2d(im.getRouge());
  cout << "vert" << endl;
  display2d(im.getVert());
  cout << "bleu" << endl;
  display2d(im.getBleu());
}


// Méthode pour convertir l'image en noir et blanc
Image Image::noirEtBlanc() const {
  // Convertit d'abord l'image en niveaux de gris
  Image noiretblanc = (niveauxDeGris());

  // Récupère les composantes de l'image en niveaux de gris
  vector<vector<int>> rouge = noiretblanc.getRouge();
  vector<vector<int>> vert = noiretblanc.getVert();
  vector<vector<int>> bleu = noiretblanc.getBleu();

  // Parcourt l'image en niveaux de gris pour la transformer en noir et blanc
  for (int i = 0; i < rouge.size(); i++) {
    for (int j = 0; j < rouge[i].size(); j++) {
      if (rouge[i][j] <= 127) {
        rouge[i][j] = 0;
      } else {
        rouge[i][j] = 255;
      }
    }
  }

  // Affecte les valeurs obtenues pour les composantes verte et bleue
  bleu = rouge;
  vert = rouge;

  // Retourne une nouvelle image en noir et blanc
  return Image(rouge, vert, bleu);
}

//Les trois méthodes qui renvoient les vecteurs 2d associés aux composantes de l'image
vector<vector<int>> Image::getRouge() const { return (_rouge); }
vector<vector<int>> Image::getVert() const { return (_vert); }
vector<vector<int>> Image::getBleu() const { return (_bleu); }


// Méthode pour créer un histogramme des niveaux de gris de l'image
vector<int> Image::histogrammeGris() const {
  vector<int> gris(255, 0);  // Initialise un vecteur pour compter les occurrences de chaque niveau de gris
  for (int i = 0; i < niveauxDeGris().getRouge()[1].size(); i++) {
    gris[niveauxDeGris().getRouge()[1][i]] += 1;  // Incrémente le compteur pour le niveau de gris correspondant
  }
  return gris;  // Retourne l'histogramme des niveaux de gris
}

// Méthode pour créer un histogramme des couleurs de l'image
vector<vector<vector<int>>> Image::histogrammeCouleur() const {
  // Création d'un vecteur tridimensionnel pour stocker l'histogramme des couleurs
  vector<vector<vector<int>>> couleur(255);
  // Initialisation des valeurs de l'histogramme à zéro
  for (int i = 0; i < couleur.size(); i++) {
    couleur[i] = vector<vector<int>>(255);
    for (int j = 0; j < couleur[i].size(); j++) {
      couleur[i][j] = vector<int>(255, 0);
    }
  }
  // Parcours de l'image pour compter l'occurrence de chaque couleur
  for (int i = 0; i < _rouge.size(); i++) {
    for (int j = 0; j < _vert.size(); j++) {
      for (int k = 0; k < _bleu.size(); k++) {
        couleur[_rouge[i][j]][_vert[i][j]][_bleu[i][j]] += 1;
      }
    }
  }
  return couleur;  // Retourne l'histogramme des couleurs
}

// Méthode pour augmenter la luminosité de l'image
Image Image::luminosityUp(float luminosity) const {
    vector<vector<int>> updatedRouge = _rouge;
    vector<vector<int>> updatedVert = _vert;
    vector<vector<int>> updatedBleu = _bleu;

    // Vérifier que la luminosité est supérieure à 1, sinon la corriger
    if (luminosity < 1) {
        luminosity = 1;
    }

    // Parcourir les canaux rouge, vert et bleu de l'image
    for (int i = 0; i < _rouge.size(); i++) {
        for (int j = 0; j < _rouge[i].size(); j++) {
            // Mettre à jour les valeurs des canaux en fonction de la luminosité
            if (_rouge[i][j] * luminosity > 255) {
                updatedRouge[i][j] = 255;
            } else {
                updatedRouge[i][j] = _rouge[i][j] * luminosity;
            }
            if (_bleu[i][j] * luminosity > 255) {
                updatedBleu[i][j] = 255;
            } else {
                updatedBleu[i][j] = _bleu[i][j] * luminosity;
            }
            if (_vert[i][j] * luminosity > 255) {
                updatedVert[i][j] = 255;
            } else {
                updatedVert[i][j] = _vert[i][j] * luminosity;
            }
        }
    }

    return Image(updatedRouge, updatedVert, updatedBleu);
}

// Méthode pour diminuer la luminosité de l'image
Image Image::luminosityDown(float luminosity) const {
  vector<vector<int>> updatedRouge = _rouge;
  vector<vector<int>> updatedVert = _vert;
  vector<vector<int>> updatedBleu = _bleu;
  // Si la luminosité est supérieure à 1, la corriger
  luminosity = 1 / luminosity;
  if (luminosity > 1) {
    luminosity = 1;
  }
  // Parcourir les canaux rouge, vert et bleu de l'image
  for (int i = 0; i < _rouge.size(); i++) {
    for (int j = 0; j < _rouge[i].size(); j++) {
      // Appliquer la diminution de luminosité à chaque canal en fonction de la valeur de luminosité
      if (_rouge[i][j] * luminosity > 255) {
        updatedRouge[i][j] = 255;
      } else {
        updatedRouge[i][j] = _rouge[i][j] * luminosity;
      }
      if (_bleu[i][j] * luminosity > 255) {
        updatedBleu[i][j] = 255;
      } else {
        updatedBleu[i][j] = _bleu[i][j] * luminosity;
      }
      if (_vert[i][j] * luminosity > 255) {
        updatedVert[i][j] = 255;
      } else {
        updatedVert[i][j] = _vert[i][j] * luminosity;
      }
    }
  }
  return Image(updatedRouge, updatedVert, updatedBleu);  // Retourner une nouvelle image avec la diminution de luminosité
}

// Méthode pour exporter les données de l'image au format .ppm
void Image::implantationppm() {
  // Déclaration d'un objet ofstream pour écrire dans un fichier
  ofstream streamecr;

  // Déclaration de la variable pour stocker le nom du fichier
  string nomfichier;

  // Demande à l'utilisateur de saisir le nom du fichier à créer ou modifier
  cout << "donnez le nom du fichier a creer ou modifier" << endl;
  cin >> nomfichier;

  // Vérifie si le nom du fichier se termine par ".ppm", sinon l'ajoute
  if (nomfichier.size() - 1 != 'm' && nomfichier.size() - 2 != 'p') {
    nomfichier = nomfichier.append(".ppm");
  }

  // Ouvre le fichier avec le nom spécifié en mode écriture
  streamecr.open(nomfichier);

  // Écriture de l'en-tête PPM dans le fichier
  streamecr << "P3" << endl;  // Format de l'image
  streamecr << "#all rights reserved TUI de Yasro" << endl;  // Commentaire
  streamecr << _vert.size() << " " << _vert[0].size() << endl;  // Dimensions de l'image
  streamecr << "255" << endl; // Profondeur de couleur

  // Parcours des canaux rouge, vert et bleu pour écrire les valeurs dans le fichier
  for (int i = 0; i < _rouge.size(); i++) {
    for (int j = 0; j < _rouge[i].size(); j++) {
      streamecr << _rouge[i][j] << " ";  // Valeur du canal rouge
      streamecr << _vert[i][j] << " ";   // Valeur du canal vert
      streamecr << _bleu[i][j] << " ";   // Valeur du canal bleu
      streamecr << endl;  // Passage à la ligne pour la prochaine série de valeurs
    }
  }

  // Ferme le fichier après écriture
  streamecr.close();
}

/*
Image Image::contrastUp(float contrast) const {}

// fonction pour le menu, à créer dans le main ultérieurement
void creernom(string &nom) {
  cout << "Entrez le nom du fichier sur lequel vous souhaitez travailler"
       << endl;
  cin >> nom;
}
*/


// Fonction pour obtenir les choix de traitements à appliquer sur une image
vector<int> menu() {
  int nbtraitements;
  int choix;

  // Demander le nombre de traitements à l'utilisateur
  cout << "Combien de traitements souhaitez-vous réaliser sur l'image ?" << endl;
  cin >> nbtraitements;

  // Initialiser le vecteur des choix de traitements
  vector<int> choixtraitements;

  // Si aucun traitement n'est demandé, retourner le vecteur vide
  if (nbtraitements == 0)
    return choixtraitements;

  // Demander à l'utilisateur de choisir la catégorie de traitement pour chaque traitement demandé
  for (int i = 0; i < nbtraitements; i++) {
    cout << "Quelle catégorie de traitement souhaitez-vous réaliser ? \n "
            "1) Modification de couleur \n 2) Modification de forme"
         << endl;
    cin >> choix;

    // Vérifier que le choix est valide (entre 1 et 2)
    while (choix < 1 || choix > 2) {
      cout << "Erreur, veuillez choisir entre 1 et 2" << endl;
      cin >> choix;
    }

    // Ajouter le choix de catégorie au vecteur
    choixtraitements.push_back(choix);

    // En fonction de la catégorie choisie, demander des informations supplémentaires
    switch (choix) {
    case 1:
      cout << "Quel traitement de couleur souhaitez-vous réaliser ? \n 1) "
              "Composante Rouge \n 2) Noir et Blanc \n 3) Niveaux de Gris \n 4) "
              "Augmentation de la luminosité \n 5) Diminution de la luminosité "
           << endl;
      cin >> choix;

      // Vérifier que le choix est valide (entre 1 et 5)
      while (choix > 5 || choix < 1) {
        cout << "Erreur, veuillez choisir entre 1 et 5" << endl;
        cin >> choix;
      }

      // Ajouter le choix de traitement de couleur au vecteur
      choixtraitements.push_back(choix);
      break;

    case 2:
      cout << "Quel traitement de forme souhaitez-vous réaliser ? \n 1) Rogner la droite \n 2) Rogner le bas \n 3) Rogner le haut \n 4) Rogner la gauche \n 5) Faire la symétrie horizontale \n 6) Faire la symétrie verticale" << endl;
      cin >> choix;

      // Vérifier que le choix est valide (entre 1 et 6)
      while (choix > 6 || choix < 1) {
        cout << "Erreur, veuillez choisir entre 1 et 6" << endl;
        cin >> choix;
      }

      // Ajouter le choix de traitement de forme au vecteur
      choixtraitements.push_back(choix);
      break;
    }
  }

  // Retourner le vecteur des choix de traitements
  return choixtraitements;
}

// Fonction pour rogner l'image du côté droit
Image Image::rognerD(int nb) const {
  Image res = *this;
  for (int i = 0; i < nb; i++) {
    for (int j = 0; j < res._rouge.size(); j++) {
      res._rouge[j].pop_back();
      res._vert[j].pop_back();
      res._bleu[j].pop_back();
    }
  }
  res._largeur -= nb;
  return res;
}

// Fonction pour rogner l'image du côté bas
Image Image::rognerB(int nb) const{
  Image res = *this;
  for (int i = 0; i < nb; i++) {
    res._rouge.pop_back();
    res._vert.pop_back();
    res._bleu.pop_back();
  }
  res._longueur-=nb;
  return res;
}

// Fonction pour rogner l'image du côté haut
Image Image::rognerH(int nb) const{
  Image res = *this;
  for (int i = 0; i < nb; i++) {
    for(int j=0; j<res._rouge.size()-1; j++){
      res._rouge[j]=res._rouge[j+1];
      res._vert[j]=res._vert[j+1];
      res._bleu[j]=res._bleu[j+1];
      res._rouge.pop_back();
      res._vert.pop_back();
      res._bleu.pop_back();
    }
  }
  res._longueur-=nb;
  return res;
}

// Fonction pour rogner l'image du côté gauche
Image Image::rognerG(int nb) const{
  Image res = *this;
  for (int i = 0; i < nb; i++) {
    for (int j = 0; j < res._rouge.size(); j++) {
      for(int k=0; k<res._rouge[j].size()-1; k++){
        res._rouge[j][k]=res._rouge[j][k+1];
        res._vert[j][k]=res._vert[j][k+1];
        res._bleu[j][k]=res._bleu[j][k+1];
      }
      res._rouge[j].pop_back();
      res._vert[j].pop_back();
      res._bleu[j].pop_back();
    }
  }
  res._largeur -= nb;
  return res;
}

// Fonction pour effectuer un retournement horizontal de l'image
Image Image::retournementH() const {
  int cpt = 0;
  vector<vector<int>> tempRouge = _rouge;
  vector<vector<int>> tempVert = _vert;
  vector<vector<int>> tempBleu = _bleu;
  for (int i = 0; i < _rouge.size(); i++) {
    cpt = 0;
    for (int j = _rouge[i].size()-1; j >= 0; j--) {
      tempRouge[i][cpt] = _rouge[i][j];
      tempVert[i][cpt] = _vert[i][j];
      tempBleu[i][cpt] = _bleu[i][j];
      cpt++;
    }
  }
  return Image(tempRouge, tempVert, tempBleu);
}

// Fonction pour effectuer un retournement vertical de l'image
Image Image::retournementV() const {
  int cpt = 0;
  vector<vector<int>> tempRouge = _rouge;
  vector<vector<int>> tempVert = _vert;
  vector<vector<int>> tempBleu = _bleu;
  for (int i = _rouge.size()-1; i >=0; i--) {
    for (int j =0; j < _rouge[i].size(); j++) {
      tempRouge[cpt][j] = _rouge[i][j];
      tempVert[cpt][j] = _vert[i][j];
      tempBleu[cpt][j] = _bleu[i][j];
    }
    cpt++;
  }
  return Image(tempRouge, tempVert,tempBleu);
}
