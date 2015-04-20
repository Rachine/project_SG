/*
 * Code réalisé par Victor Challier et Rachid Riad
 * Pricing d'options américaines
 * Projet avec la Société Générale
*/

#include "tools.h"


int main()
{

    Cours traj1(50,0,0.1,0.03,365);
    traj1.afficherDebutPrix(90);

    return 0;
}


