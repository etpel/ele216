/*
 * MODULE ARBRE
 * module qui dÃ©finie les structure d'une liste type arbre
 * et qui regroupe les fonctions pour ce dernier
 *
 * Auteur: Ã‰tienne Pelletier
 * date: 05/2020
 */

#include "arbre.h"

//PROTOTYPE DES FONCTIONS PRIVÉES
/*
 * Fonction privée qui initie un noeuds avec un processus et la retourne
 * Les ptr autre que processus dans le noeud sont initiés à NULL
 *
 * Paramètre:
 * processus: Le processus qui sera mis dans le noeud
 *
 * La fonction retourne la nouvelle variable
 * ou elle retourne NULL dans le cas d'une echec à l'allocation
 */
static noeud_arbre* arbre_init_noeud(proc *processus);

static noeud_arbre* arbre_init_noeud(proc *processus) {
	//on fait l'allocation du nouveau noeud
	noeud_arbre *noeud = (noeud_arbre*) malloc(sizeof(noeud_arbre));
	if (noeud == NULL) {
		printf("echec d'allocation dynamique");
		return NULL;	//On retourne NULL dans le cas d'une échec
	}

	//on initie les ptr à NULL et on copie le processus dans le noeud
	noeud->processus = processus;
	noeud->enfant = NULL;
	noeud->parent = NULL;
	noeud->frere_precedant = NULL;
	noeud->frere_suivant = NULL;
	return noeud;
}

// DÉCLARATION DE FONCTION

proc* proc_init(int pid, const char *nom) {
	//allocation dynamique pour le processus
	proc *processus = (proc*) malloc(sizeof(proc));
	if (processus == NULL) {
		printf("echec d'allocation dynamique");
		return NULL;	//on retourne NULL
	}
	//allocation dymnamique pour la chaine de caractère
	processus->nom = (char*) malloc(strlen(nom) * sizeof(char));
	if (processus->nom == NULL) {
		printf("echec d'allocation dynamique");
		free(processus);
		return NULL;	//on retourne NULL
	}

	//On copie le nom de processus et l'identifint dans la structure
	strcpy(processus->nom, nom);
	processus->pid = pid;
	return processus;	//on retourne la nouvelle variable
}



arbre* arbre_init_arbre(void) {
	//allocation de la variable arbre
	arbre *arbre_init = (arbre*) malloc(sizeof(arbre));
	if (arbre_init == NULL) {
		printf("echec d'allocation dynamique");
		return NULL;	//dans le cas d'un echec on retourne NULL
	}

	// on initie tous les ptr à NULL
	arbre_init->courant = NULL;
	arbre_init->tete = NULL;
	return arbre_init;	//on retourne l'adresse de la nouvelle variable
}

int arbre_ajoute_frere(arbre *arbre, proc *processus) {
	//on effectue l'allocation du noeud
	noeud_arbre *frere = arbre_init_noeud(processus);
	if (frere == NULL) {
		return -1;
	}
	//si le noeud tête n'existe pas c'est que l'arbre n'a pas de noeud encore
	if (arbre->tete == NULL) {

		arbre->tete = frere;
		arbre->courant = frere;
		return 0;
	}
	//si le noeud courant n'a pas de frere à sa droite
	if (arbre->courant->frere_suivant == NULL) {
		arbre->courant->frere_suivant = frere;
		frere->frere_precedant = arbre->courant;

		frere->parent = arbre->courant->parent;
		arbre->courant = frere;
		return 0;
	}

	//si le noeud courant a un frère à sa droite on insere entre les deux
	arbre->courant->frere_suivant->frere_precedant = frere;
	frere->frere_suivant = arbre->courant->frere_suivant;
	arbre->courant->frere_suivant = frere;
	frere->frere_precedant = arbre->courant;

	frere->parent = arbre->courant->parent;
	arbre->courant = frere;
	return 0;

}

int arbre_ajoute_enfant(arbre * arbre, proc * processus){
	//ptr vers la nouvelle allocation du noeud frere
	noeud_arbre *enfant;

	//si le noeud tête n'existe pas c'est que l'arbre n'a pas de noeud encore
	if (arbre->tete == NULL) {
		return arbre_ajoute_frere(arbre,processus);
	}
	//si le proc courant a déjà un enfant on ajoute un frere à l'enfant
	if(arbre->courant->enfant != NULL)
	{
		arbre_proc_enfant(arbre);
		return arbre_ajoute_frere(arbre,processus);
	}

	//sinon on ajoute l'enfant au noeud courant
	//on effectue l'allocation dinamique
	enfant = arbre_init_noeud(processus);
	if (enfant == NULL) {
		return -1;
	}
	arbre->courant->enfant = enfant;
	enfant->parent = arbre->courant;
	arbre->courant = enfant;

	return 1;
}

proc * arbre_rebobine(arbre * arbre)
{
	arbre->courant = arbre->tete;
	return arbre->courant->processus;
}

proc * arbre_proc_precedant(arbre * arbre)
{
	if(arbre->courant->frere_precedant == NULL)
	{
		return NULL;
	}
	arbre->courant = arbre->courant->frere_precedant;
	return arbre->courant->processus;
}

proc * arbre_proc_suivant(arbre * arbre)
{
	if(arbre->courant->frere_suivant == NULL)
	{
		return NULL;
	}
	arbre->courant = arbre->courant->frere_suivant;
	return arbre->courant->processus;
}
proc * arbre_proc_enfant(arbre * arbre)
{
	if(arbre->courant->enfant == NULL)
	{
		return NULL;
	}
	arbre->courant = arbre->courant->enfant;
	return arbre->courant->processus;
}

proc * arbre_proc_parent(arbre * arbre)
{
	if(arbre->courant->parent == NULL)
	{
		return NULL;
	}
	arbre->courant = arbre->courant->parent;
	return arbre->courant->processus;
}

proc * arbre_premier_frere(arbre * arbre)
{
	//si le processus a un parent on va au parent
	//et on retourne le premier enfant de ce dernier
	if(arbre_proc_parent(arbre) != NULL)
	{
		return arbre_proc_enfant(arbre);
	}
	//sinon on defile tout les processus jusqu'au premier
	while(arbre_proc_precedant(arbre) != NULL){}
	return arbre->courant->processus;
}

proc * arbre_dernier_frere(arbre * arbre)
{
	//on defile tout les processus jusqu'au dernier
	while(arbre_proc_suivant(arbre) != NULL){}
	return arbre->courant->processus;
}




