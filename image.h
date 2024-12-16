#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

// Déclaration de la classe Image
class Image {
private:
  vector<vector<int>> _rouge;  // Données du canal rouge
  vector<vector<int>> _vert;   // Données du canal vert
  vector<vector<int>> _bleu;   // Données du canal bleu
  int _longueur;                // Longueur de l'image
  int _largeur;                 // Largeur de l'image

public:
  // Constructeurs
  Image(const vector<vector<int>> &, const vector<vector<int>> &, const vector<vector<int>> &);
  Image(const string &);


  // Méthodes de traitement d'image
  Image composanteRouge();
  bool detection(int, int, int);
  Image niveauxDeGris() const;
  Image noirEtBlanc() const;
  vector<vector<int>> getRouge() const;
  vector<vector<int>> getVert() const;
  vector<vector<int>> getBleu() const;
  vector<int> histogrammeGris() const;
  vector<vector<vector<int>>> histogrammeCouleur() const;
  void implantationppm();
  Image luminosityUp(float) const;
  Image luminosityDown(float) const;
  Image contrastUp(float) const;
  Image contrastDown(float) const;
  Image rognerD(int) const;
  Image rognerG(int) const;
  Image rognerB(int) const;
  Image rognerH(int) const;
  Image retournementH() const;
  Image retournementV() const;
};
void display2d(const vector<vector<int>> &);
void displaycouleur(const Image &);
void loadPicture(const string &picture, vector<vector<int>> &red,
                  vector<vector<int>> &green,
                  vector<vector<int>>  &blue);
std::vector<int> menu();

#endif
