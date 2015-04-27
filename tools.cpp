#include "tools.h"


double payoff_Put(double K,double Prix)
{
    if(K-Prix>0)
    {
        return K - Prix;
    }
    else
        return 0;
}




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

int Cours::getSize()
{
    return Vecteurprix.size();
}

void Cours::ecrireCSV(string fileName)
{
        char*s2;
        string s1="/home/rachine/Documents/ENPC\ cours/ProjetSocGen/Cours/"+fileName+".csv";
        s2=(char*) s1.c_str();

    ofstream outfile(s2);

        for(int l=0;l<Vecteurprix.size()-1;l++)
        {
            outfile<<Vecteurprix[l]<<",";
        }
            outfile<<Vecteurprix[Vecteurprix.size()-1];
    outfile.close();
    cout<<"\nAll data printed on the file "<<fileName<<" on your folder.\n";




}



Grille::Grille()
{

}

Grille::~Grille()
{
//    if(Matrice.size()!=0)
//    {
//        for(int i=0;i<Matrice.size();i++)
//        {
//            delete Matrice[i];
//        }
//    }
    //Matrice.clear();

}


Grille::Grille(double initPrix, double dividende, double volatilite, double taux, int nbEtapes, int nbSimul)

{
    for (int j = 0; j<nbSimul; j++)
    {
        Cours uneSimul(initPrix,dividende,volatilite,taux,nbEtapes);
        Matrice.push_back(uneSimul);
    }

}


void Grille::apply_payoff(double K)
{
    if(Matrice.size()>0)
    {
        for(int i = 0; i<Matrice.size(); i++)
        {
            for(int j = 0; j<Matrice[i].getSize();j++)
            {
                Matrice[i].Vecteurprix[j]=payoff_Put(K,Matrice[i].Vecteurprix[j]);
            }
        }
    }
}


void Grille::afficherDebutGrille(int n, int m)
{
    if(m<Matrice.size())
    {
        for(int i=0; i<m;i++)
        {
            cout<<"Simulation "<< i << ":" <<endl;
            if(n<Matrice[i].Vecteurprix.size())
                for(int j=0;j<n;j++)
                {
                    cout <<  Matrice[i].Vecteurprix[j] << " ";
                }

            else
            {
                cout << "Vous avez rentré un nombre n trop grand." << endl;
            }
            cout<<endl;
        }
    }
    else
    {
        cout << "Vous avez rentré un nombre m trop grand." << endl;
    }
}
















