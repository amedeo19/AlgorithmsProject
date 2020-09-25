#include "Progetto.h"


///////////////////////////////// NOSTRE FUNZIONI
//INSERISCI NODO


int InsNodo(nodo**R, char* parola) {
	nodo* y = NULL;
	nodo* x = NULL;
	nodo* newNode = NULL;
	int flag;

	parola = compatta_frase(parola, strlen(parola));			// Controllo punteggiatura
	if (-1 == ControlloLunghezza(parola)) {
		return 1;
	}
	parola = ControlloMaiuscoloTheReal(parola);
	if (parola == NULL)
		return 1;
	x = nullizza(x);
	x->parola = parola;

	flag = TreeInsertHelp((*R), x);
	if (flag == 1)
		return 1;
	newNode = x;
	if (x->padre == NULL) {										// Se il padre non esiste...
		x->rosso = 0;											// Allora è nero
	}
	else {
		x->rosso = 1;											// Se il padre esiste aggiungo un nodo rosso
		while (x->padre != NULL) {
			if (x->padre->rosso == 1) {							// Se il padre è rosso...
				if (x->padre == x->padre->padre->sinistra) {			// Ed è il figlio sinistro del nonno
					y = x->padre->padre->destra;							// Y è uguale al figlio destro del nonno
					if (y == NULL) {// AGGIUNTO DA ME											// Se Y è nullo
						if (x == x->padre->destra)
							LeftRotate((*R), x->padre);
						RightRotate((*R), x->padre);
						x->rosso = 0;
						x->sinistra->rosso = x->destra->rosso = 1;
						if ((x->padre != NULL)) {
							if (x->padre->padre != NULL) {
								x = x->padre->padre;
							}
							else {
								*R = trovaRadice(*R);
								if ((*R) != NULL)
									(*R)->rosso = 0;
								return 0;
							}
						}
						else {
							*R = trovaRadice(*R);
							if ((*R) != NULL)
								(*R)->rosso = 0;
							return 0;
						}
					}
					else if (y->rosso == 1) {
						x->padre->rosso = 0;									// Il padre è nero
						y->rosso = 0;											// Lo zio diventa nero
						x->padre->padre->rosso = 1;								// Il nonno diventa rosso
						x = x->padre->padre;									// X diventa il nonno
					}
					else {												// Se y è nero...
						if (x == x->padre->destra) {						// Se il nodo è il figlio destro...
							x = x->padre;										// X diventa il padre
							LeftRotate((*R), x);								// Ruota a sinistra
						}
						x->padre->rosso = 0;								// Il padre diventa nero
						x->padre->padre->rosso = 1;							// Il nonno diventa rosso
						RightRotate((*R), x->padre->padre);					// Rotazione a destra della radice e del nonno
					}
				}
				else {													// Se x->padre == x->padre->padre->destra 
					y = x->padre->padre->sinistra;							// Y è uguale al figlio sinistro del nonno
					if (y == NULL) {// AGGIUNTO DA ME											// Se Y è nullo
						if (x == x->padre->sinistra)
							RightRotate((*R), x->padre);
						LeftRotate((*R), x->padre);
						x->rosso = 0;
						x->sinistra->rosso = x->destra->rosso = 1;
						if ((x->padre != NULL)) {
							if (x->padre->padre != NULL) {
								x = x->padre->padre;
							}
							else {
								*R = trovaRadice(*R);
								if ((*R) != NULL)
									(*R)->rosso = 0;
								return 0;
							}
						}
						else {
							*R = trovaRadice(*R);
							if ((*R) != NULL)
								(*R)->rosso = 0;
							return 0;
						}
					}
					else 						// Ruota a sinistra
						if (y->rosso == 1) {										// Se Y è rosso
							x->padre->rosso = 0;									// Il padre diventa nero
							y->rosso = 0;											// Y diventa nero
							x->padre->padre->rosso = 1;								// Il nonno diventa rosso
							x = x->padre->padre;									// X diventa il nonno del nodo
						}
						else {													// Se Y è nero
							if (x == x->padre->sinistra) {							// Se X è il figlio di sinistra del padre
								x = x->padre;											// X diventa il padre
								RightRotate((*R), x);									// Rotazione di X
							}
							x->padre->rosso = 0;									// Il padre di x diventa nero
							x->padre->padre->rosso = 1;								// Il nonno diventa rosso
							LeftRotate((*R), x->padre->padre);						// Rotazioni della Radice e del nonno
						}
				}
			}
			else {
				*R = trovaRadice(*R);
				if ((*R) != NULL)
					(*R)->rosso = 0;
				return 0;
			}
		}
	}
	*R = trovaRadice(*R);
	if ((*R) != NULL) {
		(*R)->rosso = 0;							// La radice diventa nera
	}
	return 0;

#ifdef DEBUG_ASSERT
	Assert(!tree->nil->red, "nil not red in RBTreeInsert");
	Assert(!tree->root->red, "root not red in RBTreeInsert");
#endif
}

int TreeInsertHelp(nodo* R, nodo* z) {							//  Aiuta la funzione inserimento nodo a capire dove il nodo dovrà essere inserito 
	nodo* y = NULL;
	z->descrizione = "null";
	nodo* x = NULL;
	nodo* nil = NULL;
	int l;
	z->indice = 0;

	y = R;
	z->sinistra = z->destra = nil;
	l = Compara(y->parola, z->parola);								// l>0: la parola da aggiungere è più piccola
	if ((l == 0) && (R->indice != 0))								// Non và bene
		return 1;
	else if ((l == 0) && (R->indice == 0)) {					// Y è la radice
		R->i = 0;
		return 0;
	}
	if ((R->destra == NULL) && (R->sinistra == NULL)) {
		if (l <= -1) {													// La parola và a destra
			y->destra = z;
			z->padre = y;
			z->indice++;
		}
		else if (l >= 1) {												// La parola và a sinistra
			y->sinistra = z;
			z->padre = y;
			R->indice++;
		}
		z->i = 0;
		return 0;													// Inserimento
	}
	else if (l >= 1) {
		if (R->sinistra != NULL) {
			x = R;
			addiziono(&x, x);
			azzero(&x, x);
			x = R->sinistra;										// X è il figlio sinistro della Radice
		}
		else {
			x = R;
			addiziono(&x, x);
			azzero(&x, x);
			R->sinistra = z;
			z->padre = y;
			z->i = 0;
			return 0;
		}
	}
	else if (l <= -1) {
		if (R->destra != NULL) {
			x = R->destra;
			z->indice = R->indice + 1;
		}
		else {
			R->destra = z;
			z->padre = y;
			z->i = 0;
			return 0;
		}
	}
	while (x != nil) {// DA CONTROLLARE										// X è nullo
		y = x;
		if (Compara(x->parola, z->parola) >= 1) {					// Se x->parola > z->parola...											// X diventa il figlio sinistro
			addiziono(&x, x);
			azzero(&x, x);
			x = x->sinistra;											// Paragono con x->destro
		}
		else if (Compara(x->parola, z->parola) <= -1) {				// Se z->parola > x->parola...
			z->indice = x->indice + 1;
			x = x->destra;												// X diventa il figlio destro
		}
		else if (0 == Compara(x->parola, z->parola)) {				// Se sono la stessa parola...
			sottraggo(&(x), x);
			azzerimo(&(x), x);
			return 1;														// Ritorna
		}
	}
	z->padre = y;											// Il padre di Z diventa Y 
	if (Compara(y->parola, z->parola) == 0) {
		return 1;
	}
	else if (Compara(y->parola, z->parola) >= 1) {		// Se Y è la radice e/o se Y(il padre) è più grande di Z...
		y->sinistra = z;											// Allora il figlio sinistro del padre diventa Z
	}
	else {														// Se Y non è la radice e Y non èpiù grande di Z
		y->destra = z;												// Y destro diventa z 
	}
	z->i = 0;

#ifdef DEBUG_ASSERT
	Assert(!R->rosso == 1, "nil non e' rosso in TreeInsertHelp");
#endif
	return 0;
}


///FUNZIONE ROTAZIONE A SINISTRA
void LeftRotate(nodo *R, nodo* x) {
	nodo* y;
	nodo* nil = NULL;

	y = x->destra;							// Y è il figlio di destra di X
	x->destra = y->sinistra;				// X destro è uguale a y sinistro

	if (y->sinistra != nil)					// Se il figlio sinistro di y è NULL
		y->sinistra->padre = x;					// Allora prendo in considerazione il padre  

	y->padre = x->padre;

	// instead of checking if x->parent is the root as in the book, we 
	// count on the root sentinel to implicitly take care of this case 
	if (x->padre == NULL) {
		y->sinistra = x;
		x->padre = y;
	}
	else if (x == x->padre->sinistra) {
		x->padre->sinistra = y;
	}
	else {
		x->padre->destra = y;
	}
	y->sinistra = x;
	x->padre = y;

#ifdef DEBUG_ASSERT
	Assert(!R->rosso == 1, "Nil non è rosso in TreeInsertHelp");
#endif

}

///FUNZIONE ROTAZIONE A DESTRA

void RightRotate(nodo* R, nodo* y) {
	nodo* x;
	nodo* nil = NULL;

	x = y->sinistra;
	y->sinistra = x->destra;

	if (nil != x->destra)
		x->destra->padre = y;
	x->padre = y->padre;
	if (y->padre == NULL) {
		x->destra = y;
		y->padre = x;
	}
	else
		if (y == y->padre->sinistra) {
			y->padre->sinistra = x;
		}
		else {
			y->padre->destra = x;
		}
		x->destra = y;
		y->padre = x;

#ifdef DEBUG_ASSERT
		Assert(!R->rosso == 1, "Nil non è rosso in TreeInsertHelp");
#endif
}

//FUNZIONE CANCELLA NODO

int CercaParola2(nodo*R, char*parola) {

	if (R->parola == parola) {
		return R->indice;
	}

	if (Compara(parola, R->parola) <= -1) {
		if (R->sinistra == NULL)
			return -1;
		else
			return CercaParola2(R->sinistra, parola);
	}
	else {
		if (R->destra == NULL)
			return -1;
		else
			return CercaParola2(R->destra, parola);
	}

}

nodo* getWordAt3(nodo* R, int index) {
	nodo*x;
	char *parola = NULL;
	x = getWordAt2(R, index);							// da rivedere
	if (x != NULL) {
		return x;
	}
	return NULL;
}

int cancWord(nodo**R, char *parola) {
	int i;
	nodo*x;

	*R = trovaRadice(*R);
	x = (nodo*)malloc(sizeof(nodo));		// x,nuovo nodo
	if (x == NULL)							// Controlli malloc
		return NULL;
	x->parola = (char*)malloc(sizeof(char) * 20);
	if (x->parola == NULL)
		return NULL;
	x = nullizza(x);
	i = CercaParola2(*R, parola);
	if (i == -1)
		return 1;
	x = getWordAt3(*R, i);
	if (x == NULL)
		return 1;
	i = CancNodo(R, x);
	return i;
}

int foglia(nodo*n) {

	if ((n->destra == NULL) && (n->sinistra == NULL)) {
		return 0;
	}
	return 1;
}

int CancNodo(nodo**R, nodo* z) {				// Da sottrarre gli indici

	nodo* s;
	nodo* w;
	nodo* y;
	nodo* x;
	nodo* nil = NULL;
	nodo* radice = *R;
	int i, m = 0;

	i = CercaParola(radice, z->parola);
	if (i == -1)
		return 1;
	if ((z->sinistra == nil) || (z->destra == nil))			// Se z ha come figlio almeno una foglia...
		y = z;													// Y diventa z
	else
		y = Successori(R, z);										// Sennò y diventa il successivo								

	sottraggo3(R, y);
	azzerimo3(R, y);
	if ((y->sinistra == nil) && (y->destra != NULL)) {								// Se y->sinistra è nullo
		x = y->destra;											// X diventa y->destra
	}
	else if ((y->destra == nil) && (y->sinistra != nil)) {	// Se y->destra è nullo ma  y->sinistra no...
		x = y->sinistra;										// X èil figlio di sinistra
	}
	else {													// Se sono nulli entrambi
		x = y;													// X è uguale ad y
		m = 1;													// Conta se è NULL o no
	}

	if (y->padre != NULL) {
		w = y->padre;
	}				// Altrimenti è la radice

	if (m != 1) {
		if (radice == (x->padre = y->padre)) {				// Se la radice è uguale al padre del numero da sostituire... assegnamento da y->p a x->p 
			radice = x;											// (*R)->sinistra diventa x
		}
		else {												// Se y->padre non è la radice... 	
			if (y == y->padre->sinistra) {						// Se y è il figlio sinistro...
				y->padre->sinistra = x;								// X diventa il figlio sinistro del padre di y (x sostituisce y)
			}
			else {												// Se y è il figlio destro...
				y->padre->destra = x;								// X diventa il figlio destro del padre di y (x sostituisce y)
			}
		}
		if (y != z) {								// Se y è diverso da z

#ifdef DEBUG_ASSERT
			Assert((y != R->null), "y is nil in RBDelete\n");
#endif
			// Y è il nodo da dividere e x è il suo figlio

			if (!(y->rosso == 1))							// Se y è nero... 
				RBDeleteFixUp(&(*R), x);					// Funzione che mette il nodo y al posto di z


			DestroyKey(z, z->parola);					// Cancella la parola di z
			DestroyInfo(z, z->descrizione);				// Cancella l' informazione di z
			y->sinistra = z->sinistra;					// Y->sinistra diventa z->sinistra
			y->destra = z->destra;						// Y->destra diventa z->destra
			y->padre = z->padre;						// Y->padre diventa z->padre
			y->rosso = z->rosso;						// Y prende il colore di z
			z->sinistra->padre = z->destra->padre = y;	// I figli di z diventano i figli di y
			if (z == z->padre->sinistra) {				// Se z è il figlio sinistro del padre 
				z->padre->sinistra = y;						// Il figlio sinistro del padre diventa z
			}
			else {										// Se invece è quello destro... 
				z->padre->destra = y;						// Il figlio destro del padre di z diventa y
			}
			free(z);									// Elimina z
		}
		else {										// Se y è uguale a z
			DestroyKey(y, y->parola);					// Cancella la parola di y
			DestroyInfo(y, y->descrizione);				// Cancella la descrizione di y
			if (!(y->rosso))							// Se y non è rosso
				RBDeleteFixUp(&(*R), x);					// Vai in cancella nodo
			free(y);									// Elimina y
		}
#ifdef DEBUG_ASSERT
		Assert(!R->null->rosso, "nil not black in RBDelete");
#endif
	}
	else {											// Se x non esiste
		if (z != y) {											// Se devo sostituire col successore...
			nodo *a = NULL;

			a = nullizza(a);
			a->parola = z->parola;
			a->descrizione = z->descrizione;
			z->parola = y->parola;
			z->descrizione = y->descrizione;
			y->parola = a->parola;
			y->descrizione = a->descrizione;
			z = y;
		}if (z == (*R)) {								// Se è la radice
			DestroyKey(y, y->parola);						// Cancella la parola di y
			DestroyInfo(y, y->descrizione);					// Cancella la descrizione di y
			free(*R);										// Elimina la radice,l'albero non esiste più anche perchè se z è uguale a y e non ha figli l' unico nodo è la radice!!
			return 0;
		}
		if (z->rosso == 0) {								// Se z è nero... 
			if (y == y->padre->sinistra) {				// Se y è il figlio sinistro... 
				s = y->padre->destra;						// S è quello destro
				if (foglia(s) == 0) {					// Se s è l' ultimo nodo prima delle foglie (perchè s deve essere presente ed essere nero,sennò l' albero non sarebbe equilibrato)
					y->padre->rosso = 0;					// Il padre di s diventa nero
					s->rosso = 1;							// S diventa rosso
				}
				else {									// Se s non è una foglia...
					if ((s->sinistra != NULL) && (s->destra == NULL)) {// Se s ha solo il figlio sinistro...
						RightRotate(*R, s);								// Prima lo ruoto in modo tale da avere solo figli destri
						s = y->padre->destra;							// S torna ad essere il fratello di y
					}
					LeftRotate(*R, s->padre);							// Ruoto a sinistra
					y->padre->rosso = 0;								// Il figlio sinistro della miniradice diventa nero
					if (y->padre->rosso == 1)
						y->padre->padre->rosso = 1;							// Miniradice rossa
					else
						y->padre->padre->rosso = 0;							// Miniradice nera 
					y->padre->padre->destra->rosso = 0;					// Figlio destro della miniradice diventa nero 
					if (y->padre->destra != NULL) {						// Se era presente sia il figlio sinistro che destro di s...
						y->padre->destra->rosso = 1;						// Il figlio sinistro diventa fratello di y e rosso
					}
				}
			}
		}
		DestroyInfo(z, z->descrizione);
		DestroyKey(z, z->parola);
		if (z == z->padre->sinistra)
			z->padre->sinistra = NULL;
		else
			z->padre->destra = NULL;
		free(z);
	}
	return 0;
}

///FUNZIONE AGGIUNTIVA RBDELETE

void RBDeleteFixUp(nodo** R, nodo* x) {
	nodo* w;											// Fratello

	while ((!x->rosso) && (*R != x)) {							// Se x non è nè la radice nè è rosso
		if (x == x->padre->sinistra) {								// Se è il figlio di sinistra
			w = x->padre->destra;										// W è il fratello
																		// Caso in cui  w sia nullo
			if (w->rosso) {												// Se è rosso... 
				w->rosso = 0;												// Diventa nero
				x->padre->rosso = 1;										// E il padre rosso
				LeftRotate(*R, x->padre);									// Rotazione a sinistra di R e del padre di x
				w = x->padre->destra;										// W ritorna il fratello di destra
			}
			// Caso in cui w sia nullo
			if ((!w->destra->rosso) && (!w->sinistra->rosso)) {		// Se w di destra e di sinistra sono neri...
				w->rosso = 1;											// W diventa rosso
				x = x->padre;											// x diventa il padre
			}
			else {													// Se w di destra è nero (non w di sinistra)...
				if (!w->destra->rosso) {
					w->sinistra->rosso = 0;								// W di sinistra diventa nero
					w->rosso = 1;										// W diventa rosso
					RightRotate(*R, w);									// Ruoto a destra la radice e W
					w = x->padre->destra;								// W diventa il figlio destro di x
				}
				w->rosso = x->padre->rosso;							// W diventa dello stesso colore del padre di x
				x->padre->rosso = 0;								// X->padre diventa nero
				w->destra->rosso = 0;								// W di destra diventa nero
				LeftRotate(*R, x->padre);							// Ruota a sinistra la Radice col padre di x
				x = *R;												// X diventa la radice per uscire dal while
			}
		}
		else {													// Se x è il figlio destro...
			w = x->padre->sinistra;									// W diventa il figlio sinistro
			if (w->rosso) {											// Se w è rosso..
				w->rosso = 0;											// W diventa  nero
				x->padre->rosso = 1;									// x->padre diventa rosso
				RightRotate(*R, x->padre);								// Rotazione della radice e del padre di x
				w = x->padre->sinistra;									// W ritorna ad essere il figlio sinistro
			}
			if ((!w->destra->rosso) && (!w->sinistra->rosso)) {		// Se il figlio destro di w è rosso e pure il figlio sinistro di w
				w->rosso = 1;											// W diventa rosso
				x = x->padre;											// X diventa il padre
			}
			else {													// Se solo il figlio di sinistra è rosso
				if (!w->sinistra->rosso) {
					w->destra->rosso = 0;								// W di destra è nero
					w->rosso = 1;										// W diventa rosso
					LeftRotate(*R, w);									// Rotazione sinistra di w
					w = x->padre->sinistra;								// W ritorna ad essere il figlio sinistro
				}
				w->rosso = x->padre->rosso;							// Il colore di w diventa uguale a quello del padre di x
				x->padre->rosso = 0;								// Il padre di x diventa nero
				w->sinistra->rosso = 0;								// W di sinistra diventa nero
				RightRotate(*R, x->padre);							// Rotazione a destra della radicee e del padre
				x = *R;												// X diventa la radice
			}
		}
	}
	x->rosso = 0;										// x diventa nero

#ifdef DEBUG_ASSERT
	Assert(!tree->null->rosso, "nil not black in RBDeleteFixUp");
#endif
}

///FUNZIONE DESTROYINFO E DESTROYKEY

void DestroyInfo(nodo* x, char* descrizione) {
	if (descrizione != "null")
		free(x->descrizione);
	return;
}
void DestroyKey(nodo* x, char* parola) {
	if (parola != NULL)
		free(x->parola);
	return;
}

///FUNZIONE SUCCESSORI DEI NODI

nodo* Successori(nodo**R, nodo* x) {				// Prende il nodo successivo rispetto a quello chiamato
	nodo* y;
	nodo* nil = NULL;
	nodo* radice = *R;

	if (nil != (y = x->destra)) {						// Se y è diverso da NULL
		while (y->sinistra != nil) {						// Finchè y->sinistra è nulla
			y = y->sinistra;									// y=y->sinistra
		}
		return(y);											// ritorna y;
	}
	else {												// Se y è NULL...
		y = x->padre;										// y è uguale al padre di x
		while (x == y->destra) {							// Finchè x == y->destra
			x = y;												// x=y
			y = y->padre;										// y=y->padre
		}
		if (y == radice)									// Se y è uguale alla Radice... 
			return(nil);										// Ritorna NULL
		return(y);											// Ritorna y
	}
}


//FUNZIONE STAMPA ALBERO

void StampaAlbero(nodo*x) {
	StampaAlbero2(x);
	StampaAlbero3(x);
	return;
}

void  StampaAlbero2(nodo*x) {						// Da riguardare

	nodo*b;
	b = trovaRadice(x);
	b = nododestra(b);

	if (x == b) {
		if (x->i == 0)
			PrintGeneral(x);
		return;
	}

	if ((x->sinistra != NULL) && (x->sinistra->i == 0)) {
		StampaAlbero2(x->sinistra);
	}
	else if (((x->sinistra == NULL) || (x->sinistra->i == 1)) && (x->i == 0)) {
		PrintGeneral(x);
		StampaAlbero2(x);
	}
	else if (((x->sinistra == NULL) || (x->sinistra->i == 1)) && (x->i == 1) && (x->destra != NULL) && (x->destra->i == 0)) {
		StampaAlbero2(x->destra);
	}
	else if (x->padre != NULL) {
		StampaAlbero2(x->padre);
	}
}

void  StampaAlbero3(nodo*x) {						// Da riguardare

	nodo*b;
	b = trovaRadice(x);
	b = nododestra(b);

	if (x == b) {
		if (x->i == 1)
			x->i = 0;
		return;
	}

	if ((x->sinistra != NULL) && (x->sinistra->i == 1)) {
		StampaAlbero3(x->sinistra);
	}
	else if (((x->sinistra == NULL) || (x->sinistra->i == 0)) && (x->i == 1)) {
		x->i = 0;
		StampaAlbero3(x);
	}
	else if (((x->sinistra == NULL) || (x->sinistra->i == 0)) && (x->i == 0) && (x->destra != NULL) && (x->destra->i == 1)) {
		StampaAlbero3(x->destra);
	}
	else if (x->padre != NULL) {
		StampaAlbero3(x->padre);
	}
}

/// FUNZIONE AIUTANTE STAMPA ALBERO CHE TROVA IL NODO PIU' A DESTRA

nodo* nododestra(nodo*x) {
	if (x->destra == NULL)
		return x;
	else
		return nododestra(x->destra);
}

nodo* nodosinistra(nodo*x) {
	if (x->sinistra == NULL)
		return x;
	else
		return nodosinistra(x->sinistra);
}

///FUNZIONI STAMPA DESCRIZIONE E PAROLA

void PrintGeneral(nodo*x) {
	x->i = 1;
	PrintKey(x, x->parola);
	PrintInfo(x, x->descrizione);
}
void PrintInfo(nodo* x, char* descrizione) {
	if (descrizione == "null")
		printf("\t:	[(%s)]\n", descrizione);
	else
		printf("\t:	[%s]\n", descrizione);

}
void PrintKey(nodo* x, char* parola) {
	int lunghezza;
	lunghezza = strlen(parola);
	if (lunghezza < 8)
		printf("%s\t", x->parola);
	else
		printf("%s", x->parola);
}

// FUNZIONE NULLIZZATRICE

nodo *nullizza(nodo*R) {
	R = (nodo*)malloc(sizeof(nodo));
	if (R == NULL) {
		return NULL;
	}
	R->destra = (nodo*)malloc(sizeof(nodo));
	if (R->destra == NULL)
		return NULL;
	R->destra = NULL;
	R->sinistra = (nodo*)malloc(sizeof(nodo));
	if (R->sinistra == NULL)
		return NULL;
	R->sinistra = NULL;
	R->padre = (nodo*)malloc(sizeof(nodo));
	if (R->padre == NULL)
		return NULL;
	R->padre = NULL;
	R->descrizione = (char*)malloc(sizeof(char) * 50);
	if (R->descrizione == NULL)
		return NULL;
	R->descrizione = "null";
	R->parola = (char*)malloc(sizeof(char) * 20);
	if (R->parola == NULL)
		return NULL;
	R->parola = NULL;
	R->i = 2;
	return R;
}

//FUNZIONE CREALBERO DAL FILE DI TESTO

nodo* createFromFile(char* fileTest1617) {
	nodo* R = NULL, *x = NULL, *z = NULL;
	int h = -1, m, l;
	//int i = -1;

	FILE* Mfile = fopen(fileTest1617, "r");
	if (Mfile == NULL) {
		return NULL;
	}
	while (!feof(Mfile)) {	// Fino alla fine del File
							//i++;
		h++;					// Aumenta il numero degli element non scartati		
		if (h == 0) {			// Se è il primo elemento disponibile...
			R = nullizza(R);		// Pongo nulla la radice
			R->indice = 0;
		}

		x = (nodo*)malloc(sizeof(nodo));		// x,nuovo nodo
		if (x == NULL)							// Controlli malloc
			return NULL;
		x->parola = (char*)malloc(sizeof(char) * 20);
		if (x->parola == NULL)
			return NULL;
		m = fscanf(Mfile, "%s", (x->parola));  // Prende la parola
		if (h != 0)
			R = trovaRadice(R);

		if (m != -1) {		// Se è un errore non lo prendo in considerazione
			if (h == 0) {		// Se è il primo elemento
				R->parola = x->parola;
				l = InsNodo(&R, x->parola);
				if ((l == 1) && (h == 0)) {
					h = h--;
					free(R->destra);
					free(R->sinistra);
					free(R->padre);
					free(R);
				}
			}
			else {
				R = trovaRadice(R);
				l = InsNodo(&R, x->parola);
			}
		}
	}
	R = trovaRadice(R);
	fclose(Mfile);
	return R;
}

/// FUNZIONE TROVA RADICE

nodo* trovaRadice(nodo*R) {

	if (R->padre == NULL)
		return R;
	else
		return trovaRadice(R->padre);
}

///FUNZIONE CERCA PAROLA

int CercaParola(nodo* R, char* parola) {
	if (R->parola == parola) {
		return R->indice;
	}

	if (Compara(parola, R->parola) <= -1) {
		if (R->sinistra == NULL)
			return -1;
		else
			return CercaParola(R->sinistra, parola);
	}
	else {
		if (R->destra == NULL)
			return -1;
		else
			return CercaParola(R->destra, parola);
	}
}

//FUNZIONE CONTA PAROLE

int ContaParole(nodo* R) {
	if (R->destra == NULL)
		return (R)->indice + 1;
	else
		return ContaParole(R->destra);
}

///FUNZIONE COMPARA

int Compara(char *s1, char *s2) {
	if (*s1 == '\0' || *s1 != *s2)
		return *s1 - *s2;							//if n=1 s1>s2, if n=-1 s2>s1, if n=0 s1=s2
	else return(Compara(s1 + 1, s2 + 1));
}

///FUNZIONE CONTROLLO LUNGHEZZA (2-20 CARATTERI), CONTROLLO MAIUSCOLE

int ControlloLunghezza(char* s1) {
	unsigned int n = 20, m = 2;
	if (n >= strlen(s1) && m <= strlen(s1)) {					//se è 20 lo prendiamo;
		return 1;
	}
	else
		return -1;
}

char* ControlloMaiuscoloTheReal(char *s1) {
	int i;

	i = ControlloMaiuscola(s1);
	if (i >= 20) {
		return NULL;
	}
	if ((i = -1) || ((i >= 1) && (i <= 19))) {
		s1 = AiutoMaiuscola(s1);
	}
	return s1;
}

int ControlloMaiuscola(char* s1) {      // se ritorni -1(tutte maiuscole) allora le converti,con 0 lasci stare,fra 1-19 converti,20 o piu scarti 
	unsigned int i = 0, conta = 0;
	for (i = 0; i < strlen(s1); i++) {
		if (1 == isupper(s1[i])) {
			if (i == 0) {
				conta = 20;
			}
			else {
				conta = conta + 1;
			}
		}
	}
	if (conta == 19 + strlen(s1)) {
		return -1;
	}
	return conta;
}

char* AiutoMaiuscola(char* s1) {
	unsigned int i = 0;
	for (i = 0; i < strlen(s1); i++) {
		s1[i] = tolower(s1[i]);
	}
	return s1;
}   // da utilizzare  se controlloMaiuscola ti da -1 oppure 1<=x<=19

	///FUNZIONE AGGIUNTIVA CONTROLLO PUNTEGGIATURA

char *compatta_frase(char *a, int calzone)
{
	char *ris, *p;  // Dichiaro 2 puntatori:
					// ris per il risultato
					// p   per inserirvi i caratteri presi da *a
	ris = (char*)malloc(calzone + 1);              // allocazione memoria
	p = ris;                                  // inizializzazione di p
	while (*a != '\0') {                      // fino a quando la frase non è finita
		if (!isspace(*a) && !ispunct(*a)) { // se non è spazio o punteggiatura
			*p++ = *a++;                        // aggiungo il carattere di *a in *p
		}
		else
			*a++;                             // altrimenti avanzo il puntatore *a di una posizione
	}
	*p = '\0';                                // aggiungo fine frase

	return (ris);
}

///FUNZIONE INSERISCI DEFINIZIONE (se la definizione è maggiore a 50 non viene accettata)

int InsDef(nodo*R, char* parola, char* descrizione) {
	int flag, lunghezza;

	flag = CercaParola(R, parola);
	if (flag == -1) {
		printf("\nNon e\' presente alcuna parola con la medesima sintassi!\n\n");
		return 1;
	}
	nodo *x;
	x = getWordAt3(R, flag);
	lunghezza = strlen(descrizione);
	if (lunghezza <= MAX_DEF)
		x->descrizione = descrizione;
	else
		printf("\nLa descrizione e\' troppo lunga, non verra\' accettata!\n\n");
	return 0;
}

//FUNZIONE GETWORDAT

char* getWordAt(nodo* R, int index) {
	nodo *x;

	x = (nodo*)malloc(sizeof(nodo));		// x,nuovo nodo
	if (x == NULL)							// Controlli malloc
		return NULL;
	x->parola = (char*)malloc(sizeof(char) * 20);
	if (x->parola == NULL)
		return NULL;
	x = nullizza(x);
	x = getWordAt2(R, index);
	if (x != NULL) {
		return x->parola;
	}
	return NULL;
}

nodo* getWordAt2(nodo* x, int index) {

	if (x->indice == index)
		return x;

	if ((index < x->indice)) {
		if (x->sinistra == NULL)
			return NULL;
		else
			return getWordAt2(x->sinistra, index);
	}
	else {
		if (x->destra == NULL)
			return NULL;
		else
			return getWordAt2(x->destra, index);
	}

}

//FUNZIONE SEARCHDEF

char* searchDef(nodo* R, char* word) {
	int i;
	nodo* x;

	i = CercaParola(R, word);
	if (i == -1) {
		return NULL;
	}
	else {
		x = getWordAt3(R, i);
		x->descrizione = parolaa(x, word);
		return x->descrizione;
	}
}

/// FUNZIONE CERCA PAROLA RITORNA DEFINIZIONE

char* parolaa(nodo* x, char* parola) {

	int i;

	i = Compara(parola, x->parola);
	if (i == 0)
		return x->descrizione;
	if (i <= -1) {
		if (x->sinistra != NULL)
			return parolaa(x->sinistra, parola);
		else
			return NULL;
	}
	else {
		nodo *R = x;
		R = trovaRadice(R);
		if (x->destra != NULL)
			return parolaa(x->destra, parola);
		else
			return NULL;
	}
}

void addiziono(nodo**R, nodo *x) {

	if ((*R)->destra == NULL) { // Se non c'è nulla a destra...
		(*R)->indice++;
		return;					// Ritorna l'indice +1
	}

	if (((*R)->destra != NULL) && ((*R)->destra->i == 0)) {
		x = (*R)->destra;
		x->i = 2;
		addiziono(&(*R), x);
	}
	else if (((*R)->destra != NULL) && (x->sinistra != NULL) && (x->sinistra->i == 0)) {
		x = x->sinistra;
		addiziono(&(*R), x);
	}
	else if (((*R)->destra != NULL) && (x->destra != NULL) && (x->destra->i == 0)) {
		x->destra->indice++;
		x->destra->i = 1;
		x = x->destra;
		addiziono(&(*R), x);
	}
	else if (((*R)->destra != NULL) && ((x->destra == NULL) || (x->destra->i == 1)) && ((x->sinistra == NULL) || (x->sinistra->i == 1))) {
		if (x->i == 1) {
			x = x->padre;
		}
		else {
			x->indice++;
			x->i = 1;
			x = x->padre;
		}
		if (x == (*R)) {
			(*R)->indice++;
			(*R)->i = 1;
			return;
		}
		addiziono(&(*R), x);
	}
}

void azzero(nodo**R, nodo*x) {

	if ((*R)->destra == NULL) {
		(*R)->i = 0;
		return;
	}

	if (((*R)->destra != NULL) && (x->sinistra != NULL) && (x->sinistra->i == 1)) {
		x = x->sinistra;
		azzero(&(*R), x);
	}
	else if (((*R)->destra != NULL) && (x->destra != NULL) && (x->destra->i == 1)) {
		x->destra->i = 0;
		x = x->destra;
		azzero(&(*R), x);
	}
	else if (((*R)->destra != NULL) && ((x->destra == NULL) || (x->destra->i == 0)) && ((x->sinistra == NULL) || (x->sinistra->i == 0))) {
		if (x->i == 0) {
			x = x->padre;
		}
		else {
			x->i = 0;
			x = x->padre;
		}
		if (x == (*R)) {
			(*R)->i = 0;
			return;
		}
		azzero(&(*R), x);
	}
}

void sottraggo(nodo**R, nodo*x) {
	if ((x->padre == NULL) && ((x->destra == NULL) || (x->destra->i == 1)))
		return;

	if (x->indice == (*R)->indice) {
		if (x->padre != NULL) {
			x->i = 1;
			x = x->padre;
			return sottraggo(&(*R), x);
		}
		else
			return;
	}
	else if ((x->padre != NULL) && (x == x->padre->sinistra)) {
		x = x->padre;
		sottraggo2(&(x), x);
		sottraggo(&(*R), x);
	}
	else if ((x->padre != NULL) && (x == x->padre->destra)) {
		x->i = 1;
		x = x->padre;
		sottraggo(&(*R), x);
	}

}

void sottraggo2(nodo**R, nodo*x) {

	if ((*R)->destra == NULL) { // Se non c'è nulla a destra...
		(*R)->indice--;
		return;					// Ritorna l'indice +1
	}

	if (((*R)->destra != NULL) && ((*R)->destra->i == 0)) {
		x = (*R)->destra;
		x->i = 2;
		sottraggo2(&(*R), x);
	}
	else if (((*R)->destra != NULL) && (x->sinistra != NULL) && (x->sinistra->i == 0)) {
		x = x->sinistra;
		sottraggo2(&(*R), x);
	}
	else if (((*R)->destra != NULL) && (x->destra != NULL) && (x->destra->i == 0)) {
		x->destra->indice--;
		x->destra->i = 1;
		x = x->destra;
		sottraggo2(&(*R), x);
	}
	else if (((*R)->destra != NULL) && ((x->destra == NULL) || (x->destra->i == 1)) && ((x->sinistra == NULL) || (x->sinistra->i == 1))) {
		if (x->i == 1) {
			x = x->padre;
		}
		else {
			x->indice--;
			x->i = 1;
			x = x->padre;
		}
		if (x == (*R)) {
			(*R)->indice--;
			(*R)->i = 1;
			return;
		}
		sottraggo2(&(*R), x);
	}
}

void azzerimo(nodo**R, nodo*x) {

	if ((x->padre == NULL) && ((x->destra == NULL) || (x->destra->i == 1)))
		return;

	if (x->indice == (*R)->indice) {
		if (x->padre != NULL) {
			x->i = 0;
			x = x->padre;
			return azzerimo(&(*R), x);
		}
		else
			return;
	}
	else if ((x->padre != NULL) && (x == x->padre->sinistra)) {
		x = x->padre;
		azzero(&(x), x);
		azzerimo(&(*R), x);
	}
	else if ((x->padre != NULL) && (x == x->padre->destra)) {
		x->i = 0;
		x = x->padre;
		azzerimo(&(*R), x);
	}
}

void sottraggo3(nodo**R, nodo*x) {

	if ((x->padre == NULL) && ((x->destra == NULL) || (x->destra->i == 1)))
		return;

	if (x->indice == (*R)->indice) {
		if (x->padre != NULL) {
			sottraggo2(&(*R), x);
			x = x->padre;
			return sottraggo3(&(*R), x);
		}
		else
			return;
	}
	else if ((x->padre != NULL) && (x == x->padre->sinistra)) {
		x = x->padre;
		sottraggo2(&(x), x);
		sottraggo3(&(*R), x);
	}
	else if ((x->padre != NULL) && (x == x->padre->destra)) {
		x->i = 1;
		x = x->padre;
		sottraggo3(&(*R), x);
	}

}			// Per cancella nodo sposta gli indici, da chiamare prima

void azzerimo3(nodo**R, nodo*x) {

	if ((x->padre == NULL) && ((x->destra == NULL) || (x->destra->i == 1)))
		return;

	if (x->indice == (*R)->indice) {
		if (x->padre != NULL) {
			azzero(&(*R), x);
			x = x->padre;
			return azzerimo3(&(*R), x);
		}
		else
			return;
	}
	else if ((x->padre != NULL) && (x == x->padre->sinistra)) {
		x = x->padre;
		azzero(&(x), x);
		azzerimo3(&(*R), x);
	}
	else if ((x->padre != NULL) && (x == x->padre->destra)) {
		x->i = 0;
		x = x->padre;
		azzerimo3(&(*R), x);
	}

}			// Per cancella nodo sposta gli indici, da chiamare prima
