/*
 * Code réalisé par Victor Challier et Rachid Riad
 * Pricing d'options américaines
 * Projet avec la Société Générale
*/

#include "tools.h"


int main()
{

    Cours traj1(50,0,0.1,0.03,365);
    //traj1.ecrireCSV("test");
    Grille grille1(50,0,0.1,0.03,365,10);
    grille1.afficherDebutGrille(5,5);
    return 0;
}


