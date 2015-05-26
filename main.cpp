/*
 * Code réalisé par Victor Challier et Rachid Riad
 * Pricing d'options américaines
 * Projet avec la Société Générale
*/

#include "tools.h"



int main()
{

    Cours traj1(50,0.1,0.03,365);
    traj1.afficherDebutPrix(5);
    //traj1.ecrireCSV("test");
    Strategie strat(4,15);
    strat.afficherDebutCoeff(5);
    strat.Calcul_coeff(5);
    strat.afficherDebutCoeff(5);

    return 0;
}


