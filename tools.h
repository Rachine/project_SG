#ifndef TOOLS_H
#define TOOLS_H
#include<cmath>
#include <vector>
#include<string>
#include<iostream>
#include <chrono>
#include <random>
using namespace std;


class Cours
{
public:
    Cours();
    ~Cours();
    Cours(double initPrix, double dividende, double volatilite, double taux, int nbEtapes);
    void afficherDebutPrix(int n);

private:
    vector<double> Vecteurprix;

};

//class Grille
//{
//public:
//    Grille();
//    ~Grille();
//    Grille(double initPrix, double dividende, double volatilite, double taux, int nbEtapes,int nbSimul);
//    void ecrireCSV(string nomFichier);
//private:

//};

#endif // TOOLS_H
