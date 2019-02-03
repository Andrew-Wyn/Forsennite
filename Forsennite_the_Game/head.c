#include"game.h"
#include"list.h"
#include"filel.h"

time_t t;
int n_col_row = 0;
_Bool creata = false;
unsigned int turno = 0;
unsigned int vittorie_ciccio, vittorie_ninja = 0;
int n_max = 0;
int p_nessun_pericolo = 0, p_trappola = 0, p_alieno = 0; 
int p_nessun_oggetto = 0, p_medikit = 0, p_pozione = 0, p_materiale = 0, p_colpi_lanciarazzi = 0;

Cella *scacchiera;

static Giocatore ciccio;
static Giocatore ninja;

static Torre torre_ciccio;
static Torre torre_ninja;

//game.c
static void stampa_scacchiera(_Bool ingame); //funzione per stampare la scacchiera, in modalita game o in modalita creazione
static void crea_scacchiera(); //funzione per la creazione della scacchiera
static void crea_mappa(); //menu di scelta per creare-caricare-salvare la scacchiera
static void gioca(_Bool normal_mode); //funzione per avviare il gioco, in due modalità a scelta dell'utente
static void usa_oggetto(Giocatore *attuale); //funzione per l'utlizzo dell'oggetto con relativo menu
static void get_item_from_scacchiera(Giocatore *attuale, int x, int y); //funzione per prendere l'oggetto dalla cella della scacchiera
static int  trigger_cella(Giocatore *attuale); //trigger per l'eventuale pericolo della cella
static int  muovi(Giocatore *attuale); //funzione per muovere il personaggio nella scacchiera
static void restringimento(_Bool normal_mode); //funzione per restringere la cella ha due funzionalità, modalita normale e  alternativa
static void reset_game(); // reinizzializza tutte le variabili di gioco
static void printstats(Giocatore attuale); //stampa le statistiche del personaggio
static void scontro_finale(); //funzione per lo scontro finale
static void termina_gioco(); //funzione che si richiama prima di terminare il gioco stampa le statistiche di vittoria
static void press_enter(); //effetto press_enter
static void printf_from_file(char *title, char *color); //la stringa passata da tastiera puo causare warnings!
static void init_position(_Bool normal_mode); //inizializza la posizione dei giocatori in modo pseudo-casuale
