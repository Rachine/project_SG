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
#include<gsl/gsl_multifit.h>

using namespace std;

double payoff_Put(double K, double Prix);

bool polynomialfit(int obs, int degree,
           double *dx, double *dy, double *store);
class Cours
{
public:
    Cours();
    ~Cours();
    Cours(double initPrix, double volatilite,double taux, int nbEtapes);
    int getSize();
    void afficherDebutPrix(unsigned int n);
    void ecrireCSV(string fileName);
    //operator=
    vector<double> Vecteurprix;

};



class Strategie
{
public:
    Strategie();
    ~Strategie();
    Strategie(int degre_poly,int nb_Etapes);
    void Calcul_coeff(int nb_Cours);
    double Calcul_Prix(vector<Cours> Matrice_Cours, double taux);
    int degree, etapes;
    void afficherDebutCoeff(int n);

    vector<double> Matrice_Coeff;
};



#endif // TOOLS_H
