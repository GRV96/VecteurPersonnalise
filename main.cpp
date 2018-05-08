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

    for(int i(0); i<VecteurDeInts.size(); i++)
    {
        cout << "" << VecteurDeInts.at(i) << endl;
    }

    assert(VecteurDeInts.size() == 6);
    baliser(7);

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

    /* Test de l'itérateurs avec "begin()" et "end()"
    int compteur = 0;

    for(vector<string>::iterator it = VecteurDeString.begin(); it != VecteurDeString.end(); ++it)
    {
        compteur++;
    }

    assert(compteur == 6);
    //*/

    for(int i(0); i<VecteurDeString.size(); i++)
    {
        cout << "" << VecteurDeString[i] << endl;
    }

    cout << "Tests termines" << endl;

    return 0;
}
