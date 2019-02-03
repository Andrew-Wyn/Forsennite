#include"game.h"
#include"list.h"

// ****lista doppiamente linkata****

void ins_piano(Torre *torre, int numero){
    Piano *new; //variabile puntatore nodo
	new = malloc(sizeof(Piano)); //allocazione della memoria
    new -> n_piano = numero;
    new -> prossimo_piano = NULL;
	if(torre -> testa == NULL) {
        //inserisco in testa
        torre -> testa = new;
        new -> piano_precedente = NULL;
    }

    if(torre -> coda != NULL) {
        //cambio succesivo alla coda
        torre -> coda -> prossimo_piano = new;
        new -> piano_precedente = torre -> coda;
    }

    //inserisco in coda
    torre -> coda = new;
}

void stampa_torre(Piano *piano){ //get testa della lista
    if(piano == NULL){
        return;
    }
    printf("- piano: %d -\n", piano -> n_piano);
    stampa_torre(piano -> piano_precedente);
}

void delete_last(Torre *torre){
    if(torre->coda != NULL){
        Piano *appo = torre -> coda -> piano_precedente;
        free(torre -> coda);
        if(appo != NULL){
            torre -> coda = appo;
            torre -> coda -> prossimo_piano = NULL;
        } else {
            torre -> testa = NULL;
            torre -> coda = NULL;
        }
    }
}

void delete_all(Piano *piano){
  if(piano == NULL) return;
  delete_all(piano->prossimo_piano);
  free(piano);
}