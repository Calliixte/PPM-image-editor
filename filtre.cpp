#include "filtre.h"
#include "image.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

Filtre::Filtre(vector<vector<float>> action,int rayon){
    _action=action;
    _rayon=rayon;
}
Filtre::Filtre(){
_action={{0,0,0},{0,0,0},{0,0,0}};
_rayon=1;
}
void Filtre::MultiplAutour(int & r,int & v, int & b,const Image & img,int i,int j){

    for (int ii=_rayon;ii>0;ii--){
        for(int jj=_rayon;jj>0;jj--){
            r=r+img.getRouge()[i-ii][j-jj]*_action[i][j];
            cout<<"ii "<<ii<<"jj "<<jj<<"i "<<i<<" j "<<j<<endl;
            v=v+img.getVert()[i-ii][j-jj]*_action[i][j];
            b=b+img.getBleu()[i-ii][j-jj]*_action[i][j];
        }
    }///attention car la je pense que ça fait pas fois ii 0 et jj 0
    for (int ii=_rayon;ii>0;ii--){
        for(int jj=_rayon;jj>0;jj--){
            r=r+img.getRouge()[i+ii][j+jj]*_action[i][j];
           // cout<<"ii "<<ii<<"jj "<<jj<<"i "<<i<<" j "<<j<<endl;
            v=v+img.getVert()[i+ii][j+jj]*_action[i][j];
            b=b+img.getBleu()[i+ii][j+jj]*_action[i][j];
        }

}
}
/*
Image Filtre::application ( Image & img){  not done and bugs out so it is commented
    vector<vector<int>> rougecop=img.getRouge();
    vector<vector<int>> bleucop=img.getBleu();
    vector<vector<int>> vertcop=img.getVert();
    int r,v,b;
    for(int i=0;i<img.getRouge().size();i++){
        for(int j=0;j<img.getRouge()[i].size();j++){
            img.getPixel(r,v,b,i,j);
            if(r!=-1 || v!=-1 || b!=-1){
                    MultiplAutour(r,v,b,img,i,j);

                }
            }

        }
    }
*/
