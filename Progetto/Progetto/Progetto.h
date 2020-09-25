#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#ifdef DMALLOC
#include <dmalloc.h>
#endif
//#define DEBUG_ASSERT 1

#define MAX_DEF 50
#define MAX_WORD 20
#define MIN_WORD 2


//STRUTTURA NODO E ALBERO

typedef struct rb_nodo {
	char *parola;						//key
	char *descrizione;
	int rosso;							/* if rosso=0 then the node is black */
	struct rb_nodo* sinistra;
	struct rb_nodo* destra;
	struct rb_nodo* padre;
	int indice;
	int i;
} nodo;


void azzerimo3(nodo**R, nodo*x);
void azzerimo(nodo**R, nodo*x);
void sottraggo3(nodo**R, nodo*x);
void sottraggo(nodo**R, nodo*x);
void sottraggo2(nodo**R, nodo*x);
void addiziono(nodo**R, nodo*x);
void azzero(nodo**R, nodo*x);
int InsNodo(nodo**R, char* parola);
void  StampaAlbero(nodo*x);
int  CancNodo(nodo**R, nodo*z);
void LeftRotate(nodo *R, nodo* x);
void RightRotate(nodo* R, nodo* y);
int InsDef(nodo*R, char* parola, char* descrizione);
int ContaParole(nodo* R);									// Il conta inizia da 1
int CercaParola(nodo* R, char* parola);
int TreeInsertHelp(nodo* R, nodo* z);
int Compara(char* s1, char* s2);							// Compare(a,b) should return 1 if *a > *b, -1 if *a < *b, and 0 otherwise 
void DestroyInfo(nodo* x, char* descrizione);
void DestroyKey(nodo* x, char* parola);
void PrintInfo(nodo* x, char* descrizione);
void PrintKey(nodo* x, char* parola);
void RBDeleteFixUp(nodo** R, nodo* x);
int ControlloLunghezza(char* s1);
int ControlloMaiuscola(char* s1);
char* AiutoMaiuscola(char* s1);
nodo* trovaRadice(nodo*R);
char* searchDef(nodo* R, char* word);
char* parolaa(nodo* x, char* parola);
char* getWordAt(nodo* R, int index);
nodo* getWordAt2(nodo* x, int index);
char* compatta_frase(char *a, int calzone);
char* ControlloMaiuscoloTheReal(char *s1);
nodo* createFromFile(char* fileTest1617);
void PrintGeneral(nodo*x);  // Per stampare la parola con descrizione
nodo* nodosinistra(nodo*x);
nodo* nododestra(nodo*x);
int cancWord(nodo**R, char *parola);
void  StampaAlbero2(nodo*x);
void  StampaAlbero3(nodo*x);
int CercaParola2(nodo*R, char*parola);
nodo* nullizza(nodo*R);		// Malloca lo spazio,lo  controlla e lo rende NULL;
int foglia(nodo*n);