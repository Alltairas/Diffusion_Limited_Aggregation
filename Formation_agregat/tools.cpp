#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "mersenne.cpp"

using namespace std;

void testcollage(bool grillepleine, unsigned int a, unsigned int b, unsigned int c, unsigned int n)  // vérifier si la particule se fixe sur le bord de la grille
{
	if (a == 0 || a == n - 1 || b == 0 || b == n - 1 || c == 0 || c == n - 1)
	{
		grillepleine = true;
	}
}

double vitessedecroiss(double ViCroiss, const vector<double>& Rayon, const vector<unsigned int>& tps)
{
	{
		vector<double> Tangente(Rayon.size() - 1);
		for (int i = 0; i < Rayon.size() - 1; i++)       //liste des tangentes de Rayon(temps)
		{
			Tangente[i] = ((Rayon[i + 1] - Rayon[i]) / (tps[i + 1] - tps[i]));
		}
		for (int i = 0; i < Tangente.size(); i++)      //La moyenne de la tangente
		{
			ViCroiss = ViCroiss + Tangente[i];
		}
		ViCroiss = ViCroiss / Tangente.size();
		return ViCroiss;
	}
}

