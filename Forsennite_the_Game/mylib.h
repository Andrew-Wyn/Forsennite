/******mylib.h*******/
#ifndef mylib
#define mylib

    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdbool.h>
    #include<time.h>
    #include<math.h>
    #include<dirent.h>

    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_GREEN   "\x1b[32m"
    #define ANSI_COLOR_YELLOW  "\x1b[33m"
    #define ANSI_COLOR_BLUE    "\x1b[34m"
    #define ANSI_COLOR_MAGENTA "\x1b[35m"
    #define ANSI_COLOR_CYAN    "\x1b[36m"
    #define ANSI_COLOR_RESET   "\x1b[0m"

    typedef enum Tipopericolo{nessun_pericolo, trappola, alieno} Tipopericolo;
    typedef enum Stato_giocatore{vulnerabile, scudo_vita, solo_vita, solo_scudo} Stato_giocatore;
    typedef enum Tipoogetto{nessun_oggetto, medikit, pozione, materiale, colpi_lanciarazzi} Tipoogetto;

    typedef struct Cella{
        Tipopericolo pericolo;
        Tipoogetto oggetto;
    } Cella;

    typedef struct Giocatore{
        Stato_giocatore stato;
        int x, y;
        int oggetti[4]; //0) medikit, 1) pozione, 2) materiale, 3) colpi_lanciarazzi
        int kills;
    } Giocatore;

    typedef struct Piano{
        unsigned int n_piano;
        struct Piano *piano_precedente;
        struct Piano *prossimo_piano;
    } Piano;

    typedef struct Torre{
        Piano *testa;
        Piano *coda;
    } Torre;

    //interfaccia
    void init_menu();
    void start_menu();
    void my_fflush_stdin();


#endif
///////////////////
