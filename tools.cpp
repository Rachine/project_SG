#include "tools.h"

#include<gsl/gsl_multifit.h>
// construct a trivial random generator engine from a time-based seed:
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator (seed);// probleme avec le seed à sortir de là pour la génération
bool polynomialfit(int obs, int degree,
           double *dx, double *dy, double *store)
{
  gsl_multifit_linear_workspace *ws;
  gsl_matrix *cov, *X;
  gsl_vector *y, *c;
  double chisq;

  int i, j;

  X = gsl_matrix_alloc(obs, degree);
  y = gsl_vector_alloc(obs);
  c = gsl_vector_alloc(degree);
  cov = gsl_matrix_alloc(degree, degree);

  for(i=0; i < obs; i++) {
    gsl_matrix_set(X, i, 0, 1.0);
    for(j=0; j < degree; j++) {
      gsl_matrix_set(X, i, j, pow(dx[i], j));
    }
    gsl_vector_set(y, i, dy[i]);
  }

  ws = gsl_multifit_linear_alloc(obs, degree);
  gsl_multifit_linear(X, y, c, cov, &chisq, ws);

  for(i=0; i < degree; i++)
  {
    store[i] = gsl_vector_get(c, i);
  }

  gsl_multifit_linear_free(ws);
  gsl_matrix_free(X);
  gsl_matrix_free(cov);
  gsl_vector_free(y);
  gsl_vector_free(c);
  return true;
}

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



Cours::Cours(double initPrix, double volatilite, double taux, double nbEtapes)
{
    // Initialisation d'une ligne de notre matrice des prix qui correspond
    //à une trajectoire de prix.
    Vecteurprix.push_back(initPrix);
    //ici regler le problèmes des volatilités!!
    double dt=1/nbEtapes;
    normal_distribution<double> distribution (0,1);

    for ( int i = 1; i<nbEtapes; i++)
    {
        double p=distribution(generator);
        double y;
        //y = Vecteurprix[i-1]*exp(volatilite*p-volatilite*volatilite/(2*nbEtapes))*exp(taux/nbEtapes);
        y= Vecteurprix[i-1]*exp((taux-pow(volatilite,2)*0.5)*dt+(volatilite*sqrt(dt))*p);
        Vecteurprix.push_back(y);
    }

}

void Cours::afficherDebutPrix(unsigned int n)
{
    //On met cette fonction pour faire des tests dans la console.
    if(n<Vecteurprix.size())
    {
    for(unsigned int i = 0; i < n; i++ )
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

        for(unsigned int l=0;l<Vecteurprix.size()-1;l++)
        {
            outfile<<Vecteurprix[l]<<",";
        }
            outfile<<Vecteurprix[Vecteurprix.size()-1];
    outfile.close();
    cout<<"\nAll data printed on the file "<<fileName<<" on your folder.\n";




}

Strategie::Strategie()
{

}

Strategie::~Strategie()
{

}

void Strategie::Calcul_Prix(vector<Cours> Matrice_Cours, double taux, double strike)
{
    int degre_poly=degree;
    vector<double> Matrice_Strategie;
    for(unsigned int i=0; i<Matrice_Cours.size(); i++)
    {
        Matrice_Strategie.push_back(0);
    }

    for(int j=0; j<Matrice_Cours[0].getSize()-1; j++)
    {
        for(unsigned int nb_simul = 0; nb_simul<Matrice_Cours.size(); nb_simul++)
        {
            double S = Matrice_Cours[nb_simul].Vecteurprix[j];
            double valeur_j1=0;
            double valeur_j;
            valeur_j = payoff_Put(strike,S);
            for(int k=0 ; k<degre_poly+1; k++)
            {
                valeur_j1 += Matrice_Coeff[j*(degre_poly+1)+k] * pow(S,k);
            }
            if (valeur_j1<valeur_j)
            {
                Matrice_Strategie[nb_simul] = payoff_Put(strike,S)*exp(-taux*j);
            }
        }
    }

    for(unsigned int nb_simul = 0; nb_simul<Matrice_Cours.size(); nb_simul++)
    {
        if (Matrice_Strategie[nb_simul]==0)
        {
            Matrice_Strategie[nb_simul] = exp(-taux*Matrice_Cours.size())*payoff_Put(strike,Matrice_Cours[nb_simul].Vecteurprix[Matrice_Cours[0].getSize()]);
        }
    }
    double Somme = 0;
    for(unsigned int nb = 0; nb<Matrice_Strategie.size(); nb++)
    {
        Somme += Matrice_Strategie[nb];
    }
    double Prix = Somme/Matrice_Strategie.size();
    cout << "Le prix de l'option est : " << Prix << endl;
}

Strategie::Strategie(int degre_poly,int nb_Etapes)
{
    degree=degre_poly;
    etapes=nb_Etapes;
    for(int j=0; j<nb_Etapes; j++)
    {
        for(int i=0; i<degre_poly+1; i++)
        {
            Matrice_Coeff.push_back(i+(degre_poly+1)*j);
        }
    }
}

void Strategie::Calcul_coeff(int nb_Cours)
{
    vector<Cours> Grille;
    #define DEGREE degree+1
    double coeff[DEGREE];
    #define NP nb_Cours
    for(int k=0; k<nb_Cours;k++)
    {

        Cours Cours_It(100,0.2,0.1,etapes);
        Grille.push_back(Cours_It);
    }
    double x[nb_Cours];
    double y[nb_Cours];
    for(int j=0; j<etapes-1; j++)
    {
        for(int k=0;k<nb_Cours;k++)
        {
            x[k]=Grille[k].Vecteurprix[j];
            y[k]=payoff_Put(100,Grille[k].Vecteurprix[j+1]);

        }
        polynomialfit(NP, DEGREE, x, y, coeff);
        for(int i=0;i<degree+1;i++)
        {
            Matrice_Coeff[i+(degree+1)*j]=coeff[i];
        }
    }


}

void Strategie::afficherDebutCoeff( int n)
{
    //On met cette fonction pour faire des tests dans la console.
    if(n<etapes)
    {
    for( int i = 0; i < n; i++ )
    {
        cout <<"Les coefficients du Polynome à l'itération " << i << " sont:"<<endl;
        for(int j=0;j<degree+1;j++)
        {
            cout <<Matrice_Coeff[j+(degree+1)*i]<<" ";
        }
        cout <<endl;
    }
    cout << endl;
    }
    else
    {
        cout << "Vous avez rentré un nombre trop grand." << endl;
    }
}















