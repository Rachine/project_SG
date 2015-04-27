#ifndef TOOLS_H
#define TOOLS_H
#include<cmath>
#include <vector>
#include<string>
#include<iostream>
#include <chrono>
#include <random>
#include <sstream>
#include <fstream>
using namespace std;

double payoff_Put(double K, double Prix);


class Cours
{
public:
    Cours();
    ~Cours();
    Cours(double initPrix, double dividende, double volatilite, double taux, int nbEtapes);
    int getSize();
    void afficherDebutPrix(int n);
    void ecrireCSV(string fileName);
    //operator=
    vector<double> Vecteurprix;

};

class Grille
{
public:
    Grille();
    ~Grille();
    Grille(double initPrix, double dividende, double volatilite, double taux, int nbEtapes,int nbSimul);
    void apply_payoff(double K);
    void afficherDebutGrille(int n, int m);
    vector<Cours> Matrice;

};



#endif // TOOLS_H
