#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cstdlib>
#include <iterator>

template <typename T>
class vector
{
private:
    // Nombre d'�l�ments contenus
    unsigned int nbElements;

    // Collection contenant les �l�ments
    T** collection;

    void copierTableau(T** source, T** destination, unsigned int nbCopies)
    {
        for(int i(0); i<nbCopies; i++)
        {
            destination[i] = source[i];
        }
    }

    /**
    *   \brief Si la collection n'est pas vide, elle est supprim�e.
    */
    void supprimerCollection()
    {
        if(!this->empty())
        {
            for(int i(0); i<nbElements; i++)
            {
                delete collection[i];
            }
            delete [] collection;
            collection = 0;
            nbElements = 0;
        }
    }

public:
    /**
    *   \brief Constructeur
    */
    vector<T>()
    {
        collection = new T*[1];
        nbElements = 0;
    }

    /**
    *   \brief Destructeur
    */
    ~vector<T>()
    {
        supprimerCollection();
    }

    /**
    *   \brief Renvoie un pointeur vers l'�l�ment � la position donn�e.
    *   \param i
    *       Position de l'�l�ment demand�
    *   \return
    *       �l�ment � la position i
    */
    T at(unsigned int i) const {return *collection[i];}

    /**
    *   \brief Supprime les �l�ments en r�initialisant la collection du vecteur.
    */
    void clear() {supprimerCollection();}

    /**
    *    \brief
    *       Indique si le vecteur est vide.
    *    \return
    *       Vrai si aucun �l�ment n'est contenu
    */
    bool empty() const {return nbElements == 0;}

    /**
    *   \brief
    *       Supprime le dernier �l�ment de la collection.
    */
    void pop_back()
    {
        if(nbElements > 1)
        {
            T** temporaire = new T*[nbElements-1];

            // Les pointeurs contenus dans temporaire sont copi�s case par case sauf le dernier.
            copierTableau(collection, temporaire, nbElements-1);

            // Efface le contenu des cases de collection. Elles sont d�sallou�es.
            delete [] collection;

            // Collection pointe le m�me espace m�moire que temporaire.
            collection = temporaire;

            // D�cr�mentation du nombre d'�l�ments
            nbElements--;

            // Temporaire est dans la pile. � la fin de la m�thode, il n'existe plus.
        }
        else if(nbElements == 1)
        {
            delete [] collection;
            nbElements--;
        }
    }

    /**
    *   \brief
    *       Ajoute un �l�ment � la fin de la collection.
    *   \param nouveau
    *       �l�ment ajout� � la collection
    */
    void push_back(T nouveau)
    {
        T* ptrTemporaire = new T;
        *ptrTemporaire = nouveau;
        push_back(ptrTemporaire);
    }

    /**
    *   \brief
    *       Ajoute un �l�ment � la fin de la collection.
    *   \param nouveau
    *       Pointeur de l'�l�ment ajout� � la fin de la collection
    */
    void push_back(T* nouveau)
    {
        T** temporaire = new T*[nbElements+1];

        // Les pointeurs contenus dans temporaire sont copi�s case par case.
        copierTableau(collection, temporaire, nbElements);

        // Le nouvel �l�ment est ajout� � la fin de temporaire.
        temporaire[nbElements] = nouveau;

        // Efface le contenu des cases de collection. Elles sont d�sallou�es.
        delete [] collection;

        // Collection pointe le m�me espace m�moire que temporaire.
        collection = temporaire;

        // Incr�mentaion du nombre d'�l�ments.
        nbElements++;

        // Temporaire est dans la pile. � la fin de la m�thode, il n'existe plus.
    }

    /**
    *   \brief Accesseur du nombre d'�l�ments
    *   \return nombre d'�l�ments contenus
    */
    unsigned int size() const {return nbElements;}

    //iterator begin() const {return iterator(collection);}

    //iterator end() const {return iterator(collection + nbElements);}

    /**
    *   \brief Donne acc�s � l'�l�ment � la position sp�cifi�e.
    *   \param i
    *       Position de l'�l�ment voulu
    *   \return �l�ment � la position i
    */
    T operator[](unsigned int i)
    {
        return *collection[i];
    }

    class iterator
    {
    private:
        T* pointeur;

    public:
        /**
        *   \brief Constructeur
        */
        iterator(T** ptr): pointeur(ptr){}

        /**
        *   \brief Destructeur
        */
        ~iterator()
        {
            delete pointeur;
            pointeur = 0;
        }

        void operator++() {pointeur++;}

        void operator--() {pointeur--;}

        bool operator==(iterator i) const {return pointeur == i.pointeur;}

        bool operator!=(iterator i) const {return pointeur != i.pointeur;}

        T operator*(iterator i) const {return *pointeur;}
    };
};

#endif // VECTOR_H_INCLUDED
