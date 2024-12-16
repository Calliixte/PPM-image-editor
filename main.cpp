#include "filtre.h"
#include "image.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {

vector<int> choix;  // Vecteur pour stocker les choix
float lum;          // Variable pour la luminosité
string nomimage;    // Variable pour le nom de l'image
  cout<<"Donnez le nom de l'image à traiter"<<endl;
  cin>>nomimage;
  // Création d'un objet Image à partir du nom de l'image
  Image img=Image(nomimage);
  // Affichage du menu et récupération des choix de l'utilisateur
  choix=menu();
  for (int i=0;i< choix.size(); i+=2){
  // Boucle parcourant les choix de l'utilisateur par pas de 2
    switch(choix[i]){
      case 1:
        switch(choix[i+1]){
          case 1:
            img=img.composanteRouge();
          break;
          case 2:
            img=img.noirEtBlanc();
          break;
          case 3:
            img=img.niveauxDeGris();
          break;
          case 4:
            cout<<"Par combien voulez vous multiplier la luminosité ?"<<endl;
            cin>>lum;
            img=img.luminosityUp(lum);
          break;
          case 5:
              cout<<"Par combien voulez vous diviser la luminosité ?"<<endl;
            cin>>lum;
          img=img.luminosityDown(lum);
          break;
          default:
          cout<<"Erreur dans le switch : recommencer "<<endl;

        }
      break;
      case 2:
          switch(choix[i+1]){
            case 1:
              cout<<"De combien de pixels voulez-vous rogner l'image"<<endl;
              cin>>lum;
              img=img.rognerD(lum);
            break;
            case 2:
            cout<<"De combien de pixels voulez-vous rogner l'image"<<endl;
            cin>>lum;
              img=img.rognerB(lum);
            break;
            case 3:
            cout<<"De combien de pixels voulez-vous rogner l'image"<<endl;
            cin>>lum;
              img=img.rognerH(lum);
            break;
            case 4:
            cout<<"De combien de pixels voulez-vous rogner l'image"<<endl;
            cin>>lum;
             img=img.rognerG(lum);
            break;
            case 5:
                img=img.retournementH();
            break;
            case 6:
              img=img.retournementV();
            break;
            default:
            cout<<"Erreur dans le switch : recommencer "<<endl;
          }
        break;

    }
  }
  // Après la boucle, implémentation du fichier PPM résultant du traitement
  img.implantationppm();
  return 0;
}
