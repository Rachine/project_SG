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



Cours::Cours(double initPrix, double volatilite, double taux, int nbEtapes)
{
    // Initialisation d'une ligne de notre matrice des prix qui correspond
    //à une trajectoire de prix.
    Vecteurprix.push_back(initPrix);
    //ici regler le problèmes des volatilités!!
    double sigma = volatilite;

    normal_distribution<double> distribution (0.0,1);
    for ( int i = 1; i<nbEtapes; i++)
    {
        double p=distribution(generator);
        double y;
        y = Vecteurprix[i-1]*exp(sigma*p-sigma*sigma/(2*nbEtapes));
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

double Strategie::Calcul_Prix(vector<Cours> Matrice_Cours, double taux)
{
    return 1;
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

        Cours Cours_It(50,0.1,0.03,etapes);
        Grille.push_back(Cours_It);
    }
    double x[nb_Cours];
    double y[nb_Cours];
    for(int j=0; j<etapes-1; j++)
    {
        for(int k=0;k<nb_Cours;k++)
        {
            x[k]=Grille[k].Vecteurprix[j];
            y[k]=payoff_Put(50,Grille[k].Vecteurprix[j+1]);

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
    for(unsigned int i = 0; i < n; i++ )
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















