#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cstdlib>

template <typename T>
class vector
{
private:
    // Nombre d'éléments contenus
    unsigned int nbElements;

    // Taille d'une case du tableau
    //unsigned int tailleElement;

    // Collection contenant les éléments
    T** collection;

    void copierTableau(T** source, T** destination, unsigned int nbCopies)
    {
        for(int i(0); i<nbCopies; i++)
        {
            destination[i] = source[i];
        }
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
                //collection[i] = nullptr;
            }
            delete [] collection;
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
        //tailleElement = sizeof(T);
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
    *   \brief Renvoie un pointeur vers l'élément à la position donnée.
    *   \param i
    *       Position de l'élément demandé
    *   \return
    *       Élément à la position i
    */
    T at(unsigned int i) const {return *collection[i];}

    /**
    *   \brief Supprime les éléments en réinitialisant la collection du vecteur.
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
    *       Supprime le dernier élément de la collection.
    */
    void pop_back()
    {
        if(nbElements > 1)
        {
            T** temporaire = new T*[nbElements-1];
            copierTableau(collection, temporaire, nbElements-1);
            delete [] collection;
            collection = temporaire;
            nbElements--;
        }
        else if(nbElements == 1)
        {
            delete [] collection;
            nbElements--;
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
        copierTableau(collection, temporaire, nbElements);
        temporaire[nbElements] = nouveau;
        delete [] collection;
        collection = temporaire;
        nbElements++;
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
    T operator[](unsigned int i)
    {
        return *collection[i];
    }
};

#endif // VECTOR_H_INCLUDED
