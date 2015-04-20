#include "tools.h"

Cours::Cours()
{
    //Constructeur des tableaux.
}



Cours::Cours(double initPrix, double dividende, double volatilite, double taux, int nbEtapes)
{
    // Initialisation d'une ligne de notre matrice des prix qui correspond
    //à une trajectoire de prix.
    Vecteurprix.push_back(initPrix);
    //ici regler le problèmes des volatilités!!
    double sigma = volatilite;
    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution (0.0,1);
    for ( int i = 1; i<nbEtapes; i++)
    {
        double p=distribution(generator);
        double y;
        y = Vecteurprix[i-1]*exp(sigma*p-sigma*sigma/(2*nbEtapes));
        Vecteurprix.push_back(y);
    }

}

void Cours::afficherDebutPrix(int n)
{
    //On met cette fonction pour faire des tests dans la console.
    if(n<Vecteurprix.size())
    {
    for(int i = 0; i < n; i++ )
    {
        cout << "Prix du stock à l'étape " << i << " = " << Vecteurprix[i] << endl;
    }
    cout << endl;
    }
    else
    {
        cout << "Vous avez rentré un nombre trop grand." << endl;
    }
}

Cours::~Cours()
{
    //Destructeur
}
