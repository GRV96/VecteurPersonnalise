#include <cassert>
#include <iostream>
#include <string>
//#include <vector>

#include "vector.h"

using namespace std;

void baliser(unsigned int balise)
{
    cout << "Balise " << balise << endl;
}

int main()
{
    cout << "Debut des tests" << endl;

    vector<int> VecteurDeInts;
    cout << "Taille d'un vecteur d'entiers: " << sizeof(vector<int>) << endl;

    assert(VecteurDeInts.size() == 0);
    baliser(1);

    VecteurDeInts.push_back(3);

    assert(!VecteurDeInts.empty());
    baliser(2);

    VecteurDeInts.push_back(4);

    assert(VecteurDeInts[0] == 3);
    baliser(3);
    assert(VecteurDeInts.at(1) == 4);
    baliser(4);

    assert(VecteurDeInts.size() == 2);
    baliser(5);

    VecteurDeInts.clear();

    assert(VecteurDeInts.size() == 0);
    baliser(6);

    VecteurDeInts.push_back(1);
    VecteurDeInts.push_back(2);
    VecteurDeInts.push_back(3);
    VecteurDeInts.push_back(4);
    VecteurDeInts.push_back(5);
    VecteurDeInts.push_back(6);

    for(unsigned int i(0); i<VecteurDeInts.size(); i++)
    {
        cout << "" << VecteurDeInts.at(i) << endl;
    }

    assert(VecteurDeInts.size() == 6);
    baliser(7);

    //*
    cout << "Essai de erase() avec deux iterateurs." << endl;

    VecteurDeInts.erase(VecteurDeInts.begin()+2, VecteurDeInts.end()-1);

    for(int i(0); i<VecteurDeInts.size(); i++)
    {
        cout << "" << VecteurDeInts[i] << endl;
    }
    //*/

    // Second vecteur
    vector<string> VecteurDeString;

    VecteurDeString.push_back("Allo");

    assert(VecteurDeString.size() == 1);
    baliser(8);

    assert(VecteurDeString[0] != "A110");
    baliser(9);
    assert(VecteurDeString[0] == "Allo");
    baliser(10);

    VecteurDeString.push_back("Bob");
    VecteurDeString.push_back("Chat");
    VecteurDeString.push_back("Dog");
    VecteurDeString.push_back("Element");
    VecteurDeString.push_back("Flash");

    assert(VecteurDeString.size() == 6);
    baliser(11);

    //* Test de l'itérateur avec "begin()" et "end()"
    int compteur = 0;

    for(vector<string>::iterator it = VecteurDeString.begin(); it != VecteurDeString.end(); ++it)
    {
        string chaine = *it;

        cout << "Chaine " << compteur << ": " << chaine << ", taille: " << chaine.size() << endl;
        compteur++;

        if(compteur == 3)
        {
            *it = "Alexandre";
        }
        baliser(100+compteur);
    }

    cout << "Compteur: " << compteur << endl;

    assert(compteur == 6);
    baliser(12);
    //*/

    // Vérifie que la chaîne à la position 3 a été changée.
    for(int i(0); i<VecteurDeString.size(); i++)
    {
        cout << "" << VecteurDeString[i] << endl;
    }

    //*
    cout << "Essai de erase() avec un iterateur." << endl;

    VecteurDeString.erase(VecteurDeString.begin()+3);

    for(int i(0); i<VecteurDeString.size(); i++)
    {
        cout << "" << VecteurDeString[i] << endl;
    }
    //*/

    cout << "Tests termines" << endl;

    return 0;
}
