#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cstdlib>
//#include <iterator>

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

    void eliminerCasesVides(unsigned int vides)
    {
        T** temporaire = new T*[nbElements-vides];
        T* elementActuel = NULL;
        unsigned int posTemporaire = 0;

        for(unsigned int i=0; i<nbElements; i++)
        {
            elementActuel = collection[i];
            if(elementActuel != NULL)
            {
                temporaire[posTemporaire] = elementActuel;
                posTemporaire++;
            }
        }

        nbElements -= vides;
        collection = new T*[nbElements];
        copierTableau(temporaire, collection, nbElements);
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

    class iterator
    {

    friend class vector;

    private:

        // Pointeur de pointeurs contenant la collection du vecteur
        T** pointeur;

        // Indice pour parcourir la collection
        unsigned int indice;

    public:

        /**
        *   \brief Constructeur
        */
        iterator() {indice = 0;}

        /**
        *   \brief Destructeur
        */
        ~iterator()
        {
            pointeur = 0;
        }

        iterator operator+(int p) const
        {
            iterator i;
            i.pointeur = pointeur;
            i.indice = indice + p;
            return i;
        }

        void operator++() {indice++;}

        iterator operator-(int m) const
        {
            iterator i;
            i.pointeur = pointeur;
            i.indice = indice - m;
            return i;
        }

        void operator--() {indice--;}

        bool operator==(iterator i) const {return pointeur==i.pointeur && indice == i.indice;}

        bool operator!=(iterator i) const {return pointeur!=i.pointeur || indice!=i.indice;}

        bool operator<(iterator i) const {return indice < i.indice;}
        bool operator<=(iterator i) const {return (*this)<i || (*this)==i;}

        bool operator>(iterator i) const {return indice > i.indice;}
        bool operator>=(iterator i) const {return (*this)>i || (*this)==i;}

        T& operator*() const {return *pointeur[indice];}
    };

    /**
    *   \brief Constructeur par d�faut
    */
    vector<T>()
    {
        collection = new T*[1];
        nbElements = 0;
    }

    /**
    *   \brief Constructeur par copie
    */
    vector<T>(const vector<T>& v)
    {
        nbElements = v.nbElements;
        collection = new T*[nbElements];

        for(unsigned int i(0); i<nbElements; i++)
        {
            collection[i] = new T;
            *collection[i] = *v.collection[i];
        }
    }

    /**
    *   \brief Destructeur
    */
    ~vector<T>()
    {
        supprimerCollection();
    }

    /**
    *   \brief
    *       Renvoie l'�l�ment � la position donn�e.
    *   \param i
    *       Position de l'�l�ment demand�
    *   \return
    *       �l�ment � la position i
    */
    T& at(unsigned int i) const {return *collection[i];}

    /**
    *   \brief
    *       Cr�e un it�rateur pointant le premier �l�ment de la collection.
    *   \return
    *       Un it�rateur pointant le premier �l�ment
    */
    iterator begin() const
    {
        iterator i;
        i.pointeur = collection;
        return i;
    }

    /**
    *   \brief
    *       Supprime les �l�ments en r�initialisant la collection du vecteur.
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
    *       Cr�e un it�rateur pointant le dernier �l�ment de la collection.
    *   \return
    *       Un it�rateur pointant le dernier �l�ment
    */
    iterator end() const
    {
        iterator i;
        i.pointeur = collection;
        i.indice = nbElements;
        return i;
    }

    void erase(iterator position)
    {
        erase(position, position+1);
    }

    void erase(iterator premier, iterator dernier)
    {
        unsigned int position;
        unsigned int suppressions = 0;

        for(premier; premier<dernier; ++premier)
        {
            position = premier.indice;
            delete collection[position];
            collection[position] = 0;
            suppressions++;
        }

        eliminerCasesVides(suppressions);
    }

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
            supprimerCollection();
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

    /**
    *   \brief Donne acc�s � l'�l�ment � la position sp�cifi�e.
    *   \param i
    *       Position de l'�l�ment voulu
    *   \return �l�ment � la position i
    */
    T& operator[](unsigned int i)
    {
        return *collection[i];
    }
};

#endif // VECTOR_H_INCLUDED
