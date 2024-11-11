//Dans cette version/iteration du program on veut ajouter la 3ieme dimension a l'agregat
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "mersenne.cpp"  // générateur de nombres (pseudo-)aléatoires

using namespace std;

// ========== main ==========
int main()
{
    fstream f;
    f.open("InfosAgregat.txt",ios::out);   	// écriture des coordonnées dans un fichier texte

    CRandomMersenne RandGen((int)time(NULL));

    unsigned int n;  				// taille de la grille
    cout << "entrer la taille de la grille ou on simulera les particles" << endl;
    cin >> n;
    vector<vector<vector<bool>>> grille (n, vector<vector<bool>> (n, vector<bool>(n, false)));  // définition du vecteur 3D 

    grille[n/2][n/2][n/2] = true;  		// première particule au milieu
    // grille[][][]                 // possibilité d'ajouter plusieurs particules primaires à différentes coordonnées
    // grille[][][]
    // grille[][][]
    vector<int> xVal;             //tableau où les coordonnées de la particule seront gardées
    vector<int> yVal;
    vector<int> zVal;
    vector<double> Rayon;       //les valeurs du rayon de l'agregat
    vector<unsigned int> tps;   //temps
    double r = 0;		//rayon du cercle encerclant les particules fixés
    double rtemp = 0;
    unsigned int t = 0;     //la variable de temps, qui prend en compte le mouvement d'une particule comme une itération 
    double d = 0;		//dimension fractale
    unsigned int N = 0; 	// nombre de particules fixes
    bool grillepleine = false;  // booléen qui indique si une particule se fixe sur un bord
    int step=1;   		//longueur du pas de la particule secondaire
    double ViCroiss = 0;    	//Vitesse de croissance qui est la pente de Rayon(temps)
    bool mobile = true;		// booléen qui indique si une particule est fixe
    
    do  // boucle : lancement de particules
    {
    	
        unsigned int a = 0;  // une nouvelle particule dans une bordure au choix
        unsigned int b = 0;
        unsigned int c = 0;
        
        switch (RandGen.IRandom(1, 12)) // İnitialisation de la particule secondaire  sur une bordure
        {
        case 1:
            a = 0; b = RandGen.IRandom(0, n - 1); c = 0;	//départ du particule secondaire sur le bord bas arrière
            break;
        case 2:
            a = 0; b = RandGen.IRandom(0, n - 1); c = n - 1;	//départ du particule secondaire sur le bord haut arrière
            break;
        case 3:
            a = 0; b = 0; c = RandGen.IRandom(0, n - 1);	//départ du particule secondaire sur le bord gauche arrière
            break;
        case 4:
            a = 0; b = n - 1; c = RandGen.IRandom(0, n - 1);   //départ du particule secondaire sur le bord droit arrière  
            break;
        case 5:
            a = n - 1; b = RandGen.IRandom(0, n - 1); c = 0;	//départ du particule secondaire sur le bord bas avant
            break;
        case 6:
            a = n - 1; b = RandGen.IRandom(0, n - 1); c = n - 1;	//départ du particule secondaire sur le bord haut avant
            break;
        case 7:
            a = n - 1; b = 0; c = RandGen.IRandom(0, n - 1);	//départ du particule secondaire sur le bord gauche avant
            break;
        case 8:
            a = n - 1; b = n - 1; c = RandGen.IRandom(0, n - 1);   //départ du particule secondaire sur le bord droit avant
            break;
        case 9:
            a = RandGen.IRandom(0, n - 1); b = 0; c = 0;	//départ du particule secondaire sur le bord gauche bas
            break;
        case 10:
            a = RandGen.IRandom(0, n - 1); b = 0; c = n - 1;	//départ du particule secondaire sur le bord gauche haut
            break;
        case 11:
            a = RandGen.IRandom(0, n - 1); b = n - 1; c = 0;	//départ du particule secondaire sur le bord droit bas
            break;
        case 12:
            a = RandGen.IRandom(0, n - 1); b = n - 1; c = 0;   //départ du particule secondaire sur le bord droit haut
            break;

        }

       
        do  // boucle : mouvement de la particule jusqu'au collage
        {
            
            switch (RandGen.IRandom(1, 2))  //definiton de la longeur du pas du particule
            {
            case 1:
                step = 1;
                break;
            case 2:
                step = 2;
                break;
            }
           
            switch (RandGen.IRandom(1, 6))  // mouvement aléatoire d'un pas
            {
            case 1:			//aller a l'est
                a = (a + step) % n;
                break;
            case 2:			//aller a l'ouest
                a = (a + n - step) % n;
                break;
            case 3:			//aller au sud
                b = (b + step) % n;
                break;
            case 4:			//aller au nord
                b = (b + n - step) % n;
                break;
            case 5:         //aller en avant
                c = (c + step) % n;
                break;
            case 6:         //aller en arrière
                c = (c + n - step) % n;
            }

            t++;        //le temps s'écoule a chaque mouvement de particule

		if (grille[(a + step) % n][b][c] || grille[(a + n - step) % n][b][c] ||			// condition qui vérifie s'il y a la présence d'un voisin
				grille[a][(b + step) % n][c] || grille[a][(b + n - step) % n][c] ||
				grille[a][b][(c + step) % n] || grille[a][b][(c + n - step) % n])
			{
				grille[a][b][c] = true;
				N++;
				xVal.push_back(a);         //envoyer les coordonnées dans un tableau
				yVal.push_back(b);
				zVal.push_back(c);
				rtemp = sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));      // rayon de l'agregat lors de la diffusion
				if (rtemp > r) { r = rtemp; }
				else { r = r; }
				f << a << "  " << b << "  " << c << "  " << t << "  " << r << endl;//garder la trace de l'information de l'ordre d'apparition des particules, l'écrire sur un fichier txt

				mobile = false;
			}

           
     
        } while (mobile);

            void testcollage(bool grillepleine, unsigned int a, unsigned int b, unsigned int c, unsigned int n); // test : collage au bord de la grille ?
        
    } while(grillepleine == false);
    f.close();

    double vitessedecroiss(double ViCroiss, const vector<double>& Rayon, const vector<unsigned int>& tps);

    d=(log(N)/log(r));
    cout<<"le rayon encerclant l'agregat depuis le particule primaire est "<<r<<endl;
    cout<<"la dimension fractale est "<<d<<endl;
    cout<<"le nombre de particule généré lors de notre simulation est "<<N<<endl;
    cout <<"la vitesse de croissance est" << ViCroiss << endl;
   
    return 0;
}
