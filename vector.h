#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cstdlib>

template <typename T>
class vector
{
private:
    // Nombre d'�l�ments contenus
    unsigned int nbElements;

    // Taille d'une case du tableau
    //unsigned int tailleCase;

    // Collection contenant les �l�ments
    T *collection;

    /**
    *   \brief Si la collection n'est pas nulle, elle est supprim�e.
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
    *   \brief Renvoie un pointeur vers l'�l�ment � la position donn�e.
    *   \param i
    *       Position de l'�l�ment demand�
    *   \return �l�ent � la position i
    */
    T at(unsigned int i) const {return collection[i];}

    /**
    *   \brief Supprime les �l�ments en r�initialisant la collection du le vecteur.
    */
    void clear() {supprimerCollection();}

    /**
    *    \brief Indique si le vecteur est vide.
    *    \return vrai si aucun �l�ment n'est contenu
    */
    bool empty() const {return nbElements == 0;}

    /**
    *   \brief
    *       Supprime le dernier �l�ment de la collection.
    *   \return
    *       Vrai si la suppression est effectu�e correctement
    *       ou faux en cas d'�chec ou si la collection est d�j� vide.
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
    *       Ajoute un �l�ment � la fin de la collection.
    *   \param nouveau
    *       �l�ment ajout� � la collection
    *   \return
    *       Vrai si l'ajout est effectu� correctement ou faux en cas d'�chec.
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
    T operator[](unsigned int i)
    {
        return collection[i];
    }
};

#endif // VECTOR_H_INCLUDED
