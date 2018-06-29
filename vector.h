#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cstdlib>
//#include <iterator>

template <typename T>
class vector
{
private:
    // Nombre d'éléments contenus
    unsigned int nbElements;

    // Collection contenant les éléments
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
    *   \brief Si la collection n'est pas vide, elle est supprimée.
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
    *   \brief Constructeur par défaut
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
    *       Renvoie l'élément à la position donnée.
    *   \param i
    *       Position de l'élément demandé
    *   \return
    *       Élément à la position i
    */
    T& at(unsigned int i) const {return *collection[i];}

    /**
    *   \brief
    *       Crée un itérateur pointant le premier élément de la collection.
    *   \return
    *       Un itérateur pointant le premier élément
    */
    iterator begin() const
    {
        iterator i;
        i.pointeur = collection;
        return i;
    }

    /**
    *   \brief
    *       Supprime les éléments en réinitialisant la collection du vecteur.
    */
    void clear() {supprimerCollection();}

    /**
    *    \brief
    *       Indique si le vecteur est vide.
    *    \return
    *       Vrai si aucun élément n'est contenu
    */
    bool empty() const {return nbElements == 0;}

    /**
    *   \brief
    *       Crée un itérateur pointant le dernier élément de la collection.
    *   \return
    *       Un itérateur pointant le dernier élément
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
    *       Supprime le dernier élément de la collection.
    */
    void pop_back()
    {
        if(nbElements > 1)
        {
            T** temporaire = new T*[nbElements-1];

            // Les pointeurs contenus dans temporaire sont copiés case par case sauf le dernier.
            copierTableau(collection, temporaire, nbElements-1);

            // Efface le contenu des cases de collection. Elles sont désallouées.
            delete [] collection;

            // Collection pointe le même espace mémoire que temporaire.
            collection = temporaire;

            // Décrémentation du nombre d'éléments
            nbElements--;

            // Temporaire est dans la pile. À la fin de la méthode, il n'existe plus.
        }
        else if(nbElements == 1)
        {
            supprimerCollection();
        }
    }

    /**
    *   \brief
    *       Ajoute un élément à la fin de la collection.
    *   \param nouveau
    *       Élément ajouté à la collection
    */
    void push_back(T nouveau)
    {
        T* ptrTemporaire = new T;
        *ptrTemporaire = nouveau;
        push_back(ptrTemporaire);
    }

    /**
    *   \brief
    *       Ajoute un élément à la fin de la collection.
    *   \param nouveau
    *       Pointeur de l'élément ajouté à la fin de la collection
    */
    void push_back(T* nouveau)
    {
        T** temporaire = new T*[nbElements+1];

        // Les pointeurs contenus dans temporaire sont copiés case par case.
        copierTableau(collection, temporaire, nbElements);

        // Le nouvel élément est ajouté à la fin de temporaire.
        temporaire[nbElements] = nouveau;

        // Efface le contenu des cases de collection. Elles sont désallouées.
        delete [] collection;

        // Collection pointe le même espace mémoire que temporaire.
        collection = temporaire;

        // Incrémentaion du nombre d'éléments.
        nbElements++;

        // Temporaire est dans la pile. À la fin de la méthode, il n'existe plus.
    }

    /**
    *   \brief Accesseur du nombre d'éléments
    *   \return nombre d'éléments contenus
    */
    unsigned int size() const {return nbElements;}

    /**
    *   \brief Donne accès à l'élément à la position spécifiée.
    *   \param i
    *       Position de l'élément voulu
    *   \return élément à la position i
    */
    T& operator[](unsigned int i)
    {
        return *collection[i];
    }
};

#endif // VECTOR_H_INCLUDED
