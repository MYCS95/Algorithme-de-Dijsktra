#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct ville ville;
typedef struct graphe graphe;

struct ville {
    int indice;
    char *nom_ville;
    int cout;
    ville *suiv;
    ville *voisine;
};

struct graphe {
    ville* premiereVille; //Pr�mi�re ville ajout�e dans le graphe
    ville* derniereVille; //Derniere ville ajout�e dans le graphe
};

void afficheVille(ville *pVille);
void afficheGraphe(graphe *pGraphe);
void afficheListeVille(ville *pVille);
void afficheVilleVoisine(ville *pVille);
graphe* creerGraphe();
graphe* ajouterVille(char pNomVille[50], graphe *pGraphe);
graphe* ajouterVilleVoisine(char pVilleDepart[50], char pVilleVoisine[50], int pCout, graphe* pGraphe);
int nombreVille(graphe *pGraphe);
ville* rechercherVille(char pVille[50], graphe *pGraphe);
void calculCoutMinimal(char pVilleDepart[50], graphe *pGraphe);
ville* getVille(char pVille[50], graphe *pGraphe);
int obtenirIndice(ville *pVille, graphe *pGraphe);
ville* rechercheVilleOptimale(ville *pPremiereVilleNonParcouru);
void miseAJourCout(ville* pPremiereVilleParcouru, ville* pPremiereVilleNonParcouru, ville* pDerniereVilleParcouru, graphe *pGraphe);
ville* supprimerVille(ville* pVilleASupprimer, ville* pOuSupprimer);

int main()
{
    graphe *g = creerGraphe();
    g = NULL;
    g = ajouterVille("A", g);
    g = ajouterVille("B", g);
    g = ajouterVille("C", g);
    g = ajouterVille("D", g);
    g = ajouterVille("E", g);
    g = ajouterVille("F", g);
    g = ajouterVille("G", g);
    g = ajouterVille("H", g);
    g = ajouterVille("I", g);
    g = ajouterVille("J", g);
    g = ajouterVille("K", g);

    g = ajouterVilleVoisine("A", "B", 6, g);
    g = ajouterVilleVoisine("A", "K", 3, g);
    g = ajouterVilleVoisine("A", "G", 4, g);

    g = ajouterVilleVoisine("B", "A", 6, g);
    g = ajouterVilleVoisine("B", "C", 5, g);
    g = ajouterVilleVoisine("B", "D", 2, g);
    g = ajouterVilleVoisine("B", "K", 2, g);

    g = ajouterVilleVoisine("C", "B", 5, g);
    g = ajouterVilleVoisine("C", "D", 1, g);
    g = ajouterVilleVoisine("C", "E", 3, g);

    g = ajouterVilleVoisine("D", "B", 2, g);
    g = ajouterVilleVoisine("D", "C", 1, g);
    g = ajouterVilleVoisine("D", "E", 4, g);

    g = ajouterVilleVoisine("E", "C", 3, g);
    g = ajouterVilleVoisine("E", "J", 1, g);
    g = ajouterVilleVoisine("E", "D", 4, g);

    g = ajouterVilleVoisine("F", "D", 5, g);
    g = ajouterVilleVoisine("F", "J", 1, g);
    g = ajouterVilleVoisine("F", "I", 2, g);
    g = ajouterVilleVoisine("F", "H", 9, g);
    g = ajouterVilleVoisine("F", "G", 2, g);
    g = ajouterVilleVoisine("F", "K", 8, g);

    g = ajouterVilleVoisine("G", "A", 4, g);
    g = ajouterVilleVoisine("G", "K", 1, g);
    g = ajouterVilleVoisine("G", "F", 2, g);
    g = ajouterVilleVoisine("G", "H", 3, g);

    g = ajouterVilleVoisine("H", "G", 3, g);
    g = ajouterVilleVoisine("H", "F", 9, g);
    g = ajouterVilleVoisine("H", "I", 5, g);

    g = ajouterVilleVoisine("I", "H", 5, g);
    g = ajouterVilleVoisine("I", "F", 2, g);
    g = ajouterVilleVoisine("I", "J", 3, g);

    g = ajouterVilleVoisine("J", "I", 3, g);
    g = ajouterVilleVoisine("J", "F", 1, g);
    g = ajouterVilleVoisine("J", "E", 1, g);

    g = ajouterVilleVoisine("K", "A", 3, g);
    g = ajouterVilleVoisine("K", "B", 2, g);
    g = ajouterVilleVoisine("K", "F", 8, g);
    g = ajouterVilleVoisine("K", "G", 1, g);

    afficheGraphe(g);

    calculCoutMinimal("A", g);

    //afficheListeVille(v);
}

/* Permet d'avoir le nombre de ville dans un graphe */
int nombreVille(graphe *pGraphe) {
    ville *ptr;
    ptr = pGraphe->premiereVille;
    int i = 0;
    while(ptr != NULL) {
        i = i + 1;
        ptr = ptr->suiv;
    }
    return i;
}

/* Permet de cr�er un graphe */
graphe* creerGraphe() {
    graphe *g = (graphe*)malloc(sizeof(graphe));
    g->premiereVille = NULL;
    g->derniereVille = NULL;
    return g;
}

/* Permet d'ajouter une ville au graphe */
graphe* ajouterVille(char pNomVille[50], graphe *pGraphe) {
    if(pGraphe == NULL) {
        ville *v = (ville*)malloc(sizeof(ville));
        v->cout = 0;
        v->indice = 1;
        v->nom_ville = pNomVille;
        v->suiv = NULL;
        v->voisine = NULL;
        pGraphe = (graphe*)malloc(sizeof(graphe));
        pGraphe->premiereVille = v;
        pGraphe->derniereVille = v;
        return pGraphe;
    }
    else {
        ville *v = (ville*)malloc(sizeof(ville));
        v->cout = 0;
        v->indice = nombreVille(pGraphe) + 1;
        v->nom_ville = pNomVille;
        v->suiv = NULL;
        v->voisine = NULL;
        pGraphe->derniereVille->suiv = v;
        pGraphe->derniereVille = v;
        return pGraphe;
    }
}

/*Permet d'afficher la liste des villes suivants une ville */
void afficheListeVille(ville *pVille) {
    ville *ptr;
    ptr = pVille;
    while(ptr != NULL) {
        afficheVille(ptr);
        printf(" -> ");
        ptr = ptr->suiv;
    }
}

/*Permet la liste des villes voisines d'une ville */
void afficheVilleVoisine(ville *pVille) {
    ville *ptr;
    if(pVille != NULL) {
        ptr = pVille->voisine;
        while(ptr != NULL) {
            afficheVille(ptr);
            printf(" -> ");
            ptr = ptr->suiv;
        }
    }
}

/*Permet d'afficher une ville */
void afficheVille(ville *pVille) {
    printf("(%d,%s,%d)", pVille->indice, pVille->nom_ville, pVille->cout);
}

/* Permet d'afficher un graphe */
void afficheGraphe(graphe *pGraphe) {
    ville *ptr;
    ptr = pGraphe->premiereVille;
    while(ptr != NULL) {
        afficheVille(ptr);
        printf(" -> ");
        afficheVilleVoisine(ptr);
        printf("FIN");
        ptr = ptr->suiv;
        printf("\n\n");
    }
}

/* Permet d'ajouter une ville voisine � une ville */
graphe* ajouterVilleVoisine(char pVilleDepart[50], char pVilleVoisine[50], int pCout, graphe *pGraphe) {
    ville *ptr, *tmp;
    ptr = pGraphe->premiereVille;
    while(ptr != NULL && ptr->nom_ville != pVilleDepart) {
        ptr = ptr->suiv;
    }
    if(ptr == NULL)
        return 1; //Ville de d�part non trouv�

    ville *v = (ville*)malloc(sizeof(ville));

    v->nom_ville = pVilleVoisine;
    tmp = rechercherVille(pVilleVoisine, pGraphe);
    v->indice = tmp->indice;
    v->cout = pCout;
    v->voisine = NULL;
    v->suiv = NULL;

    if(ptr->voisine == NULL) {
        ptr->voisine = v;
    }
    else {
        tmp = ptr->voisine;
        while(tmp->suiv != NULL) {
            tmp = tmp->suiv;
        }
        tmp->suiv = v;
    }
    return pGraphe;
}

/*Permet de chercher une ville dans le graphe */
ville* rechercherVille(char pVille[50], graphe *pGraphe) {
    ville *ptr;
    ptr = pGraphe->premiereVille;
    while(ptr != NULL && ptr->nom_ville != pVille) {
        ptr = ptr->suiv;
    }

    return ptr;
}

/* Permet de calculer la distance minimale d'une ville aux autres */
void calculCoutMinimal(char pVilleDepart[50], graphe *pGraphe) {
    ville *villeDepart, *villeNonParcouru, *villeParcouru, *ptr, *tmp, *temp, *premiereVilleNonParcouru, *premiereVilleParcouru, *parc;
    ville *villeOptimale;
    int distance = 0;
    villeDepart = NULL;
    ptr = NULL;
    premiereVilleNonParcouru = NULL;
    premiereVilleParcouru = NULL;
    temp = NULL;
    ptr = NULL;
    parc = NULL;

    villeDepart = getVille(pVilleDepart, pGraphe);
    //Ville parcouru = ville de d�part par d�faut
    villeParcouru = (ville*)malloc(sizeof(ville));
    villeParcouru->cout = villeDepart->cout;
    villeParcouru->indice = villeDepart->indice;
    villeParcouru->nom_ville = villeDepart->nom_ville;
    villeParcouru->suiv = NULL;
    villeParcouru->voisine = NULL;
    premiereVilleParcouru = villeParcouru;

    //Initialisation de l'algotithme de Dijikstra
    ptr = pGraphe->premiereVille;
    while(ptr != NULL) {
        if(ptr->nom_ville == villeParcouru->nom_ville) {
            ptr = ptr->suiv;
            continue;
        }
        //La distance entre la ville de d�part et la ville selectionn�
        distance = obtenirDistance(ptr, villeParcouru);
        if(villeNonParcouru == NULL) {
            villeNonParcouru = (ville*)malloc(sizeof(ville));
            villeNonParcouru->cout = distance;
            villeNonParcouru->indice = ptr->indice;
            villeNonParcouru->nom_ville = ptr->nom_ville;
            villeNonParcouru->voisine = NULL;
            premiereVilleNonParcouru = villeNonParcouru;
        }
        else {
            tmp = (ville*)malloc(sizeof(ville));
            tmp->nom_ville = ptr->nom_ville;
            tmp->suiv = NULL;
            tmp->cout = distance + villeParcouru->cout;
            tmp->voisine = NULL;
            //tmp->indice = obtenirIndice(tmp, pGraphe);
            villeNonParcouru->suiv = tmp;
            villeNonParcouru = tmp;
        }
        ptr = ptr->suiv;
    }
    //Fin d'initialisation

    //Etape 2 : Recherche des distances minimales entre ville
    ptr = premiereVilleNonParcouru;
    parc = (ville*)malloc(sizeof(ville));
    parc->cout = premiereVilleNonParcouru->cout;
    parc->indice = premiereVilleNonParcouru->indice;
    parc->nom_ville = premiereVilleNonParcouru->nom_ville;
    parc->suiv = premiereVilleNonParcouru->suiv;
    parc->voisine = premiereVilleNonParcouru;
    while(parc != NULL) {
        villeOptimale = NULL;
        villeOptimale = rechercheVilleOptimale(premiereVilleNonParcouru);

        temp = (ville*)malloc(sizeof(ville)); //Sauvegarder la ville optimale
        temp->nom_ville = villeOptimale->nom_ville;
        temp->suiv = NULL;
        temp->cout = villeOptimale->cout;
        temp->voisine = villeOptimale->voisine;

        villeParcouru->suiv = temp;
        villeParcouru = temp;

        //Suppression de la ville optimale
        premiereVilleNonParcouru = supprimerVille(villeOptimale, premiereVilleNonParcouru);

        //Mise a jour des distances
        miseAJourCout(premiereVilleParcouru, premiereVilleNonParcouru, temp, pGraphe);

        parc = premiereVilleNonParcouru;
    }
    printf("\n\nVille parcouru : ");
    afficheListeVille(premiereVilleParcouru);
    printf("FIN\n");
}

/* Recup�re une ville */
ville* getVille(char pVille[50], graphe *pGraphe) {
    ville *ptr;
    ptr = pGraphe->premiereVille;
    while(ptr != NULL && ptr->nom_ville != pVille)
        ptr = ptr->suiv;
    return ptr;
}

/* Permet de caculer la distance entre deux villes */
int obtenirDistance(ville *pVilleDepart, ville *pVilleArrive) {
    ville *ptr;
    ptr = pVilleDepart->voisine;
    while(ptr != NULL) {
        if(ptr->nom_ville == pVilleArrive->nom_ville) {
            return ptr->cout;
        }
        ptr = ptr->suiv;
    }
    if(ptr == NULL)
        return INT_MAX; //Au cas ou les deux villes sont pas voisines
}

/*Permet d'obtenir l'indice d'une ville */
int obtenirIndice(ville *pVille, graphe *pGraphe) {
    ville *ptr;
    ptr = pGraphe->premiereVille;
    while(ptr != NULL && ptr->nom_ville != pVille->nom_ville) {
        ptr = ptr->suiv;
    }
    return ptr->indice;
}

/* Recherche la ville la plus proche parmi la liste des villes non parcouru */
ville* rechercheVilleOptimale(ville *pPremiereVilleNonParcouru) {
    ville* ptr, *villeOptimale;
    ptr = pPremiereVilleNonParcouru->suiv;
    villeOptimale = pPremiereVilleNonParcouru;
    while(ptr != NULL) {
        if(villeOptimale->cout >= ptr->cout)
            villeOptimale = ptr;

        ptr = ptr->suiv;
    }
    return villeOptimale;
}

/* Supprimer une ville de la liste des villes non parcouru */
ville* supprimerVille(ville *pVilleASupprimer, ville* pOuSupprimer) {
    ville *ptr, *prec, *tmp;

    ptr = pOuSupprimer;
    prec = NULL;
    while(ptr != NULL) {
        if(ptr->nom_ville == pVilleASupprimer->nom_ville) {
            if(prec != NULL) {
                if(ptr->suiv == NULL) {
                    //Suppression en queue de liste
                    tmp = ptr;
                    prec->suiv = NULL;
                    free(ptr);
                    return pOuSupprimer;
                }
                else {
                    //Suppression au milieu de la liste
                    prec->suiv = ptr->suiv;
                    free(ptr);
                    return pOuSupprimer;
                }
            }
            else {
                //Suppression en tete de liste
                tmp = ptr->suiv;
                free(ptr);
                return tmp;
            }
        }
        prec = ptr;
        ptr = ptr->suiv;
    }
}

/* Permet de mettre � jour les distances entre les villes */
void miseAJourCout(ville* pVilleDepart, ville* pPremiereVilleNonParcouru, ville *pDerniereVilleParcouru, graphe *pGraphe) {
    ville* ptr, *tmp, *temp, *derniereVilleParcouru, *villeDepart;
    ptr = NULL;
    tmp = NULL;
    derniereVilleParcouru = NULL;
    villeDepart = NULL;
    ptr = pPremiereVilleNonParcouru;

    int disDerniereVille = 0, disVilleDepart = 0, distance = 0, disDerniereVilleDepart = 0;
    while(ptr != NULL) {
        derniereVilleParcouru = rechercherVille(pDerniereVilleParcouru->nom_ville, pGraphe);
        derniereVilleParcouru->cout = pDerniereVilleParcouru->cout;
        //Distance entre la derni�re ville et la ville actielle
        disDerniereVille = obtenirDistance(derniereVilleParcouru, ptr);
        if(disDerniereVille != INT_MAX) {
            //Il y un chemin entre la derniere ville parcouru et la ville actuelle
            tmp = rechercherVille(ptr->nom_ville, pGraphe);
            tmp->cout = ptr->cout;
            //Distance entre la ville actuelle et la ville de depart
            disVilleDepart = obtenirDistance(tmp, pVilleDepart);
            if(disVilleDepart != INT_MAX) {
                //Il y a un chemin entre la ville actuelle et la ville de d�part
                distance = derniereVilleParcouru->cout + disDerniereVille;
                if(distance <= ptr->cout || ptr->cout == INT_MAX) {
                    ptr->cout = distance;
                    ptr = ptr->suiv;
                    continue;
                }
            }
            else {
                //Distance entre la derniere ville parcouru et la ville actuelle
                disDerniereVille = obtenirDistance(derniereVilleParcouru, ptr);
                if(disDerniereVille != INT_MAX) {
                    distance = derniereVilleParcouru->cout + disDerniereVille;
                    if(distance <= ptr->cout || ptr->cout == INT_MAX) {
                        ptr->cout = distance;
                        ptr = ptr->suiv;
                        continue;
                    }
                }
            }
        }
        ptr = ptr->suiv;
    }
}
