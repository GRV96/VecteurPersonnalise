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
    //unsigned int tailleCase;

    // Collection contenant les éléments
    T *collection;

    /**
    *   \brief Si la collection n'est pas nulle, elle est supprimée.
    */
    void supprimerCollection()
    {
        if(collection != NULL)
        {
            free(collection);
            nbElements = 0;
        }
    }

public:
    /**
    *   \brief Constructeur
    */
    vector<T>()
    {
        collection = NULL;
        //tailleCase = sizeof(T);
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
    *   \return éléent à la position i
    */
    T at(unsigned int i) const {return collection[i];}

    /**
    *   \brief Supprime les éléments en réinitialisant la collection du le vecteur.
    */
    void clear() {supprimerCollection();}

    /**
    *    \brief Indique si le vecteur est vide.
    *    \return vrai si aucun élément n'est contenu
    */
    bool empty() const {return nbElements == 0;}

    /**
    *   \brief
    *       Supprime le dernier élément de la collection.
    *   \return
    *       Vrai si la suppression est effectuée correctement
    *       ou faux en cas d'échec ou si la collection est déjà vide.
    */
    bool pop_back()
    {
        if(!this->empty())
        {
            T* temporaire = (T*)realloc(collection, (nbElements-1)*sizeof(T));

            if(temporaire != NULL)
            {
                collection = temporaire;
                nbElements--;
                return true;
            }
        }

        return false;
    }

    /**
    *   \brief
    *       Ajoute un élément à la fin de la collection.
    *   \param nouveau
    *       Élément ajouté à la collection
    *   \return
    *       Vrai si l'ajout est effectué correctement ou faux en cas d'échec.
    */
    bool push_back(T nouveau)
    {
        T* temporaire = (T*)realloc(collection, (nbElements+1)*sizeof(T));

        if(temporaire != NULL)
        {
            collection = temporaire;
            collection[nbElements] = nouveau;
            nbElements++;
            return true;
        }

        return false;
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
        return collection[i];
    }
};

#endif // VECTOR_H_INCLUDED
