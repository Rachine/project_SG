/*
 * Code réalisé par Victor Challier et Rachid Riad
 * Pricing d'options américaines
 * Projet avec la Société Générale
*/

#include "tools.h"



int main()
{

    Cours traj1(36,0.2,0.06,50);
    traj1.afficherDebutPrix(5);
    traj1.ecrireCSV("test");
    Strategie strat(4,100);
    strat.afficherDebutCoeff(5);
    strat.Calcul_coeff(5);
    strat.afficherDebutCoeff(5);
    vector<Cours> Matrice;
    double etapes=50;
    for(int k=0; k<1000;k++)
    {

        Cours Cours_It(100.0,0.2,0.1,etapes);

        Matrice.push_back(Cours_It);
    }
    strat.Calcul_Prix(Matrice,0.2,100);

    return 0;
}


