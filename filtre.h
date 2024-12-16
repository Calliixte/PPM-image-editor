#ifndef FILTRE_H_INCLUDED
#define FILTRE_H_INCLUDED

#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

class Filtre{
private:
  vector<vector<float>> _action;
  int _rayon;
public:
    Filtre(vector<vector<float>> action, int rayon);
    Filtre();
    //Image application( Image &); not done last year
    void MultiplAutour(int &,int &, int &,const Image &,int ,int);
};


#endif //FILTRE_H_INCLUDED
