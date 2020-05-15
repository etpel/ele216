/*
 * MODULE ARBRE
 * 	module qui définie les structures d'une liste type arbre
 * 	et qui regroupe les fonctions de ces derniers
 *
 * Auteur: Étienne Pelletier
 * date: 05/2020
 */

#include <stdio.h>
#include <stdlib.h>


//DEFINITION DES TYPES

/*
 * Variable pour les processus
 */
typedef struct proc
{
	int pid;    //l'indentifiant du processus
	char * nom; //le nom du processus
}proc;

/*
 * Les noeuds pour de l'arbre
 */
typedef struct noeud_arbre noeud_arbre;
struct noeud_arbre
{
	noeud_arbre *parent;    //ptr vers le noeud parent
	noeud_arbre *enfant;    //ptr vers un noeud enfant
	noeud_arbre *frere_suivant; //ptr vers le noeud suivant
	noeud_arbre *frere_precedant;   //ptr vers le noeud precedant
	proc * processus;   //processus du noeud actuel

};


/*
 * structure pour faire une liste type arbre
 */
typedef struct arbre
{
	noeud_arbre *tete;  //premier noeud de l'arbre
	noeud_arbre *courant;   //le noeud courant dans la navigation
}arbre;


//FONCTIONS DE CREATION

/* proc_init
 * 	Fonction qui fait une allocation pour une varable processus et la retourne
 * 	Elle ajoute egalement les argument de celle-ci
 *
 * Paramètre:
 * 	pid: Indentifiant du processus
 * 	nom: nom du processus
 *
 * Retourne la nouvelle variable
 * Retourne NULL dans le cas d'une echec à l'allocation
 */
proc * proc_init(int pid, const char * nom);



/* arbre_init_arbre
 * 	Fonction qui initie l'arbre et la retourne
 * 	Les arguments de la variable arbre sont initiés à NULL
 *
 * Retourne la nouvelle variable
 * Retourne NULL si l'allocation echoue
 */
arbre * arbre_init_arbre(void);

/* arbre_ajoute_frere
 * 	Ajoute un noeud frere, suivant du noeud courant
 * 	Fait pointer le ptr noeud_courant au nouveau noeud inséré
 * 	Si l'arbre est vide elle ajoute ce dernier à la tete de l'arbre
 *
 * Paramètre
 * 	arbre: La liste type arbre dont nous souhaitons ajouter processus frere
 * 	processus: le processus
 *
 * Retourne -1 si elle échoue l'allocation du noeud
 * Retourne 0 si tous c'est bien déroulé
 */
int arbre_ajoute_frere(arbre * arbre, proc * processus);

/* arbre_ajoute_enfant
 * 	Ajoute un noeud enfant au noeud courant
 * 	Si l'arbre est vide elle ajoute ce dernier à la tete de l'arbre
 * 	Si le noeud à déjà un enfant, le noeud est ajouter comme frere de l'enfant
 *
 * Paramètre:
 * 	arbre: La liste type arbre dont nous souhaitons ajouter processus frere
 * 	processus: le processus
 *
 * Retourne -1 si elle échoue l'allocation du noeud
 * Retourne 0 si tous c'est bien déroulé
 */
int arbre_ajoute_enfant(arbre * arbre, proc * processus);

//FONCTIONS DE DÉVELLOPEMENT

/* arbre_rebobine
 * 	fait poiter le ptr noeud courant au noeud de tête de l'arbre
 *
 * Paramètre:
 * 	arbre: La liste type arbre dont nous souhaitons rebobiner
 *
 * retourne le processus de la tete
 */
proc * arbre_rebobine(arbre * arbre);

/* arbre_proc_precedant
 * 	Fait pointer le ptr courant à son noeud frère precedant
 * 	Si le frère precedant n'existe pas la fonction ne changera pas le noeud courant
 *
 * Paramètre:
 * 	arbre: La liste type arbre
 *
 * retourne le processus du nouveau noeud courant si il y a un noeud precedant
 * retourne NULL si le noeud frère precedant n'existe pas
 */
proc * arbre_proc_precedant(arbre * arbre);

/* arbre_proc_suivant
 * 	Fait pointer le ptr courant à son noeud frère suivant
 * 	Si le frère suivant n'existe pas la fonction ne changera pas le noeud courant
 *
 * Paramètre:
 * 	arbre: La liste type arbre
 *
 * retourne le processus du nouveau noeud courant si il y a un noeud suivant
 * retourne NULL si le noeud frère suivant n'existe pas
 */
proc * arbre_proc_suivant(arbre * arbre);

/* arbre_proc_enfant
 * 	fait pointer le ptr courant au noeud enfant sauf si le noeud n'existe pas
 *
 * Paramètre:
 * 	arbre: La liste type arbre
 *
 * retourne le processus du nouveau noeud courant
 * retourne NULL si le noeud enfant n'existe pas
 */
proc * arbre_proc_enfant(arbre * arbre);

/* arbre_proc_parent
 * 	fait pointer le ptr courant au noeud parent sauf si le noeud n'existe pas
 *
 * Paramètre:
 * 	arbre: La liste type arbre
 *
 * retourne le processus du nouveau noeud courant
 * retourne NULL si le noeud parent n'existe pas
 */
proc * arbre_proc_parent(arbre * arbre);

/* arbre_premier_frere
 * 	fait pointer le ptr courant au premier noeud de la meme génération
 *
 * Paramètre:
 * 	arbre: La liste type arbre
 *
 * retourne le processus du nouveau noeud courant, soit le premier frere
 */
proc * arbre_premier_frere(arbre * arbre);
 
/* arbre_dernier_frere
 * 	fait pointer le ptr courant au dernier noeud de la meme génération
 *
 * Paramètre:
 * 	arbre: La liste type arbre
 *
 * retourne le processus du nouveau noeud courant, soit le dernier frere
 */
proc * arbre_dernier_frere(arbre * arbre);

//FONCTIONS DE DESTRUCTION

/* arbre_retire_noeud
 * 	retire le noeud courant de l'arbre et le transmet en parametre
 */
noeud_arbre * arbre_retire_noeud(arbre * arbre);


/*
 * desallocation d'un noeud
 */
int arbre_suprime_noeud(noeud_arbre * noeud);

/*
 * desallocation de l'arbre
 */
int arbre_suprime_arbre(arbre * arbre);


