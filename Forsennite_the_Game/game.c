#include"head.c"

static void init_position(_Bool normal_mode){
    if(creata){
        if(normal_mode){
            do {
                ninja.x = (rand () % n_col_row), ninja.y = (rand () % n_col_row);
                ciccio.x = (rand () % n_col_row), ciccio.y = (rand () % n_col_row);
            } while(ciccio.x == ninja.x && ciccio.y == ninja.y);
        } else {
            do {
                ninja.x = (rand () % n_col_row), ninja.y = (rand () % n_col_row);
                ciccio.x = (rand () % n_col_row), ciccio.y = (rand () % n_col_row);
            } while((ciccio.x == ninja.x && ciccio.y == ninja.y) 
                    || (ciccio.x == 0 && ciccio.y == 0) 
                    || (ciccio.x == 0 && ciccio.y == 3)
                    || (ciccio.x == n_col_row-1 && ciccio.y == 0)
                    || (ciccio.x == n_col_row-1 && ciccio.y == n_col_row-1)
                    || (ninja.x == 0 && ninja.y == 0)
                    || (ninja.x == 0 && ninja.y == n_col_row-1) 
                    || (ninja.x == n_col_row-1 && ninja.y == 0)
                    || (ninja.x == n_col_row-1 && ninja.y == n_col_row-1));
        }
    }
}

static void printf_from_file(char *title, char *color){
    char srctitle[30] = "txts/";
    strcat(srctitle, title);
    FILE *file = fopen(srctitle, "r");

    if(file == NULL){
        printf("problemi nell'apertura del file '%s'\n", title);
        return;
    }
    char c;

    printf(color);
    while((c=getc(file))!=EOF){
        printf("%c", c);
    }
    printf(ANSI_COLOR_RESET);

    printf("\n\n");
    fclose(file);
}

void start_menu(){

    srand((unsigned) time(&t));

    torre_ciccio.testa = NULL, torre_ciccio.coda = NULL;
    torre_ninja.testa = NULL, torre_ninja.coda = NULL;

    scacchiera = NULL;
    n_col_row = 0;
    creata = false;
    turno = 0;
    vittorie_ciccio = 0;
    vittorie_ninja = 0;


    printf_from_file("titolo.txt", ANSI_COLOR_YELLOW);

    printf("\t\tPress enter...\n\n");

    fflush(stdout);
}

void my_fflush_stdin(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

static void press_enter(){
    printf("\npress enter...\n");
    
    fflush(stdout);

    //flush out all the data in the stdin
    my_fflush_stdin();
    
    fflush(stdout);
    my_fflush_stdin();
    system("clear");
}

static void crea_scacchiera(){
    int random;

    if(scacchiera != NULL){
        free(scacchiera);
        scacchiera = NULL;
    }

    printf("**Crea Scacchiera**\n");
    
    do{
        printf("inserisci n(minimo 2): ");
        fflush(stdout);
        scanf("%d", &n_col_row);
    } while(n_col_row < 2);
    
    do{
        printf("\ninserisci probabilità dei pericoli (somma = 100):\n");
        printf("- 'nessun pericolo' (range: 0-100): ");
        fflush(stdout);
        scanf("%d", &p_nessun_pericolo);
        if(p_nessun_pericolo>100) continue;
        printf("- 'trappola' (range: 0-%d): ", (100 - p_nessun_pericolo));
        fflush(stdout);
        scanf("%d", &p_trappola);
        if(p_nessun_pericolo+p_trappola>100) continue;
        printf("- 'alieno' (range: 0-%d): ", (100 - p_nessun_pericolo-p_trappola));
        fflush(stdout);
        scanf("%d", &p_alieno);
    } while((p_nessun_pericolo + p_trappola + p_alieno)!=100);

    do{
        printf("\ninserisci probabilità degli oggetti (somma = 100):\n");
        printf("- 'nessun oggetto' (range: 0-100): ");
        fflush(stdout);
        scanf("%d", &p_nessun_oggetto);
        if(p_nessun_oggetto>100) continue;
        printf("- 'medikit' (range: 0-%d): ", (100 - p_nessun_oggetto));
        fflush(stdout);
        scanf("%d", &p_medikit);
        if(p_nessun_oggetto + p_medikit>100) continue;
        printf("- 'pozione' (range: 0-%d): ", (100 - p_nessun_oggetto - p_medikit));
        fflush(stdout);
        scanf("%d", &p_pozione);
        if(p_nessun_oggetto + p_medikit + p_pozione>100) continue;
        printf("- 'materiale' (range: 0-%d): ", (100 - p_nessun_oggetto - p_medikit - p_pozione));
        fflush(stdout);
        scanf("%d", &p_materiale);
        if(p_nessun_oggetto + p_medikit + p_pozione + p_materiale >100) continue;
        printf("- 'colpi lanciarazzi' (range: 0-%d): ", (100 - p_nessun_oggetto - p_medikit - p_pozione - p_materiale));
        fflush(stdout);
        scanf("%d", &p_colpi_lanciarazzi);
    } while((p_nessun_oggetto + p_medikit + p_pozione + p_materiale + p_colpi_lanciarazzi)!=100);

    scacchiera = malloc(n_col_row * n_col_row * sizeof(struct Cella));

    for(int i=0; i<n_col_row; i++){
        for(int j=0; j<n_col_row; j++){

            random = (rand () % 100)+1;

            if(random >0 && random <=p_nessun_pericolo){
                scacchiera[i * n_col_row + j].pericolo = nessun_pericolo;
            }else if(random >p_nessun_pericolo && random <=p_nessun_pericolo+p_trappola){
                 scacchiera[i * n_col_row + j].pericolo = trappola;
            } else if(random >p_nessun_pericolo+p_trappola && random <=p_nessun_pericolo+p_trappola+p_alieno){
                 scacchiera[i * n_col_row + j].pericolo = alieno;
            }

            random = (rand () % 100)+1;

            if(random >0 && random <=p_nessun_oggetto){
                scacchiera[i * n_col_row + j].oggetto = nessun_oggetto;
            }else if(random >p_nessun_oggetto && random <=p_nessun_oggetto+p_medikit){
                 scacchiera[i * n_col_row + j].oggetto = medikit;
            } else if(random >p_nessun_oggetto+p_medikit && random <=p_nessun_oggetto+p_medikit+p_pozione){
                 scacchiera[i * n_col_row + j].oggetto = pozione;
            } else if(random >p_nessun_oggetto+p_medikit+p_pozione && random <=p_nessun_oggetto+p_medikit+p_pozione+p_materiale){
                 scacchiera[i * n_col_row + j].oggetto = materiale;
            } else if(random >p_nessun_oggetto+p_medikit+p_pozione+p_materiale && random <=p_nessun_oggetto+p_medikit+p_pozione+p_materiale+p_colpi_lanciarazzi){
                 scacchiera[i * n_col_row + j].oggetto = colpi_lanciarazzi;
            }

        }
    }
    creata = true;
    stampa_scacchiera(false);
}

static void stampa_scacchiera(_Bool ingame){
    if(creata){
        printf("\n");

        printf("MAPPA:\n\n");

        if(ingame){
            printf(ANSI_COLOR_GREEN " <*>" ANSI_COLOR_RESET);
            printf(" -> Ciccio\t");
            printf(ANSI_COLOR_RED " [*]" ANSI_COLOR_RESET);
            printf(" -> Ninja\n\n");

            for(int i=0; i<(n_max-n_col_row)/2; i++){
                printf("\n\n");
            }

            for(int i=n_col_row-1; i>=0; i--){
                for(int i=0; i<(n_max-n_col_row)/2; i++){
                    printf("     ");
                }
                for(int j=0; j<n_col_row; j++){
                    if(i == ciccio.y && j == ciccio.x && i == ninja.y && j == ninja.x){
                        printf(ANSI_COLOR_MAGENTA "[<*>]" ANSI_COLOR_RESET);
                    } else if(i == ciccio.y && j == ciccio.x){
                        printf(ANSI_COLOR_GREEN " <*> " ANSI_COLOR_RESET);
                    } else if( i == ninja.y && j == ninja.x){
                        printf(ANSI_COLOR_RED " [*] " ANSI_COLOR_RESET);
                    } else {
                        printf("  *  ");
                    }
                }
                printf("\n\n");
            }
            for(int i=0; i<(n_max-n_col_row)/2; i++){
                printf("\n\n");
            }
        } else {
            printf("MY View\n\nLeggenda:\n\tpericolo-oggetto\n\n");
            for(int i=n_col_row-1; i>=0; i--){
                if(i<=9){
                    printf(ANSI_COLOR_BLUE "%d  |" ANSI_COLOR_RESET, i);
                } else {
                    printf(ANSI_COLOR_BLUE "%d |" ANSI_COLOR_RESET, i);
                }
                for(int j=0; j<n_col_row; j++){
                    printf("  %d-%d  ", scacchiera[j*n_col_row+i].pericolo,scacchiera[j*n_col_row+i].oggetto);
                }
                if(i != 0){
                    printf("\n\n");
                } else {
                    printf("\n");
                }
                
            }
            printf("    ");
            for(int j=0; j<n_col_row; j++){
                printf(ANSI_COLOR_BLUE"   _   " ANSI_COLOR_RESET);
            }
            printf("\n");
            printf("    ");
            for(int j=0; j<n_col_row; j++){
                if(j<=9){
                    printf(ANSI_COLOR_BLUE"   %d   " ANSI_COLOR_RESET, j);
                } else {
                    printf(ANSI_COLOR_BLUE"   %d  " ANSI_COLOR_RESET, j);
                }   
            }
            printf("\n");
            /*printf("\n\n");
            printf("NORMAL View\n\n");
            for(int i=0; i<n_col_row; i++){
                for(int j=0; j<n_col_row; j++){
                    printf("  %d-%d  ", scacchiera[i*n_col_row+j].pericolo,scacchiera[i*n_col_row+j].oggetto);
                }
                printf("\n\n");
            }*/
        }
    } else {
        printf("Crea la mappa\n");
    }
}

static void crea_mappa(){
    while(1){
        int choose;
        char nomefile[20];
        printf_from_file("mappamenu.txt", ANSI_COLOR_CYAN);
        printf("\nCHOOSE:\n1) Crea scacchiera\n2) Stampa scacchiera\n3) Salva scacchiera\n4) Carica scacchiera\n5) Termina creazione\n");
        fflush(stdout);
        scanf("%d", &choose);
        system("clear");
        switch(choose){
            case 1:
                printf_from_file("mappamenu.txt", ANSI_COLOR_CYAN);
                crea_scacchiera();
                press_enter();
                break;
            case 2:
                printf_from_file("mappamenu.txt", ANSI_COLOR_CYAN);
                stampa_scacchiera(false);
                press_enter();
                break;
            case 3:
                printf_from_file("mappamenu.txt", ANSI_COLOR_CYAN);
                if(creata){
                    printf("inserisci il nome del file da salvare: ");
                    fflush(stdout);
                    scanf("%s",nomefile);
                    save_scacchiera(nomefile);
                    system("clear");
                } else {
                    printf("Crea la scacchiera\n");
                    press_enter();
                }
                break;
            case 4:
                printf_from_file("mappamenu.txt", ANSI_COLOR_CYAN);
                printf("I file salvati sono:\n\n");
                if(!print_files_name()){
                    printf("\ninserisci il nome del file da caricare (senza estensione): ");
                    fflush(stdout);
                    scanf("%s",nomefile);
                    load_scacchiera(nomefile);
                    if(creata){
                        stampa_scacchiera(false);
                    }
                }
                press_enter();
                break;
            case 5:
                if(creata){
                    return;
                }
                printf_from_file("mappamenu.txt", ANSI_COLOR_CYAN);
                printf("Crea la scacchiera\n");
                press_enter();
                break;
            default:
                break;
        }
        n_max = n_col_row; //un posto migliore
    }
}

static void usa_oggetto(Giocatore *attuale){
    printf("\n");
    int choose;

    printf("lo zaino contiene:\n");
    printf("Medikit: %d\n", attuale -> oggetti[0]);
    printf("Pozione: %d\n", attuale -> oggetti[1]);
    printf("Materiali: %d\n", attuale -> oggetti[2]);
    printf("Colpi Lanciarazzi: %d\n", attuale -> oggetti[3]);

    printf("scegliere cosa utilizzare:\n");
    fflush(stdout);
    scanf("%d", &choose);

    switch(choose){
        case 1:
            if(attuale -> oggetti[0]){
                printf("Medikit utilizzato\n");
                attuale -> oggetti[0]--;
                if(attuale->stato == vulnerabile){
                    attuale -> stato = solo_vita;
                    printf("Passato a stato ( solo vita )\n");
                }
                if(attuale -> stato == solo_scudo){
                    attuale -> stato = scudo_vita;
                    printf("Passato a stato ( scudo vita )\n");
                }
            } else {
                printf("Medikit terminati\n");
                turno--;
            }
            break;
        case 2:
            if(attuale -> oggetti[1]){
                printf("Pozione utilizzata\n");
                attuale -> oggetti[1]--;
                if(attuale->stato == vulnerabile){
                    attuale -> stato = solo_scudo;
                }
                if(attuale->stato == solo_vita){
                    attuale -> stato = scudo_vita;
                }
            } else {
                printf("Pozioni terminate\n");
                turno--;
            }
            break;
        default:
            printf("Non puoi utilizzarli\n");
            turno--;
            break;
    }
}

static void get_item_from_scacchiera(Giocatore *attuale, int x, int y){
    printf("\n");
    if(attuale -> oggetti[(scacchiera[x * n_col_row + y].oggetto)-1] < 3){
        attuale -> oggetti[(scacchiera[x * n_col_row + y].oggetto)-1]++;
        printf("Sulla terra è presente ");
        switch((scacchiera[x * n_col_row + y].oggetto)-1){
            case 0:
                printf("un 'medikit', aggiunto allo zaino!\n");
                break;
            case 1:
                printf("una 'pozione', aggiunto allo zaino!\n");
                break;
            case 2:
                printf("un 'materiale', aggiunto allo zaino!\n");
                break;
            case 3:
                printf("un 'colpo lanciarazzi', aggiunto allo zaino!\n");
                break;
        }
        scacchiera[x * n_col_row + y].oggetto = nessun_oggetto;
    } else {
        printf("Troppi oggetti dello stesso tipo\n");
    }
}

static int trigger_cella(Giocatore *attuale){
    printf("\n");
    fflush(stdout);
    int x = attuale->x, y = attuale->y;
    fflush(stdout);
    int choose;
    printf("spostato... nella cella (x:%d - y:%d)\n", x, y);
    fflush(stdout);
    switch(scacchiera[x * n_col_row + y].pericolo){
        case nessun_pericolo:
            if(scacchiera[x * n_col_row + y].oggetto > 0){
                get_item_from_scacchiera(attuale, x, y);
            } else {
                printf("nessun oggetto sulla cella\n");
            }
            break;
        case trappola:
            if(turno%2 == 0){
                printf("Sulla cella è presente una trappola, Ninja WINS\n");
                vittorie_ninja++;
            } else {
                printf("Sulla cella è presente una trappola, Ciccio WINS\n");
                vittorie_ciccio++;
            }
            return 0;
            break;
        case alieno:
            printf("Sulla cella è presente un alieno, combatti?\n1) si\n2) no\n");
            fflush(stdout);
            scanf("%d", &choose);
            switch(choose){
                case 1:
                    printf("combattimento...\n");
                    scacchiera[x * n_col_row + y].pericolo = nessun_pericolo;
                    attuale -> kills++;
                    if((rand () % 100) < 35){
                        printf("- sei stato colpito -\n");
                        if(attuale -> stato == vulnerabile){
                            if(turno%2 == 0){
                                printf("Ninja WINS\n");
                                vittorie_ninja++;
                            } else {
                                printf("Ciccio WINS\n");
                                vittorie_ciccio++;
                            }
                            return 0;
                        }
                        if((rand () % 100) < 65){
                           if(attuale -> stato == solo_vita || attuale -> stato == solo_scudo){
                                attuale -> stato = vulnerabile;
                                printf("ouch!... , passato a stato 'vulnerabile'\n");
                           } else {
                                attuale -> stato = solo_vita;
                                printf("ouch!... , passato a stato 'solo vita'\n");
                           }
                        } else {
                            if(attuale -> stato == solo_vita || attuale -> stato == solo_scudo){
                                attuale -> stato = vulnerabile;
                                printf("ouch!... , passato a stato 'vulnerabile'\n");
                           } else {
                               attuale -> stato = solo_scudo;
                               printf("ouch!... , passato a stato 'solo scudo'\n");
                           }
                        }
                    } else {
                        printf("nessun danno\n");
                    }
                    if(scacchiera[x * n_col_row + y].oggetto > 0){
                        get_item_from_scacchiera(attuale, x, y);
                    } else {
                        printf("nessun oggetto sulla cella\n");
                    }
                    break;
                case 2:
                    printf("non combatti e non prendi nulla\n");
                    break;
                default:
                    printf("non combatti e non prendi nulla\n");//non si combatte lo stesso se non si preme 1
                    break;
            }
            break;
    }
    return 1;
}

static int muovi(Giocatore *attuale){
    printf("\n");
    int choose;
    printf("Spostati sulla scacchiera:\n1) su\n2) giu\n3) destra\n4) sinistra\n");
    fflush(stdout);
    scanf("%d", &choose);
    switch(choose){
        case 1: 
            if(attuale -> y < (n_col_row-1)){
                attuale -> y += 1;

                if(!trigger_cella(attuale)){
                    fflush(stdout);
                    return 0;
                }
            } else {
                printf("non puoi andare piu su\n");
            }
            break;
        case 2:
            if(attuale -> y > 0){
                attuale -> y -= 1;

                if(!trigger_cella(attuale)){
                    fflush(stdout);
                    return 0;
                }
            } else {
                printf("non puoi andare piu giu\n");
            }
            return 1;
            break;
        case 3:
            if(attuale -> x < (n_col_row-1)){
                attuale -> x += 1;

                if(!trigger_cella(attuale)){
                    fflush(stdout);
                    return 0;
                }
            } else {
                printf("non puoi andare piu a destra\n");
            }
            break;
        case 4:
            if(attuale -> x > 0){
                attuale -> x -= 1;

                if(!trigger_cella(attuale)){
                    fflush(stdout);
                    return 0;
                }
            } else {
                printf("non puoi andare piu a sinistra\n");
            }
            break;
        default:
            printf("ritenta...\n");
            turno--;
            break;
    }
    return 1;
}

static void restringimento(_Bool normal_mode){

    if(normal_mode){
        int random;

        n_col_row /= 2;

        if(scacchiera != NULL){
            free(scacchiera);
            scacchiera = NULL;
        }

        scacchiera = malloc(n_col_row * n_col_row * sizeof(struct Cella));

        for(int i=0; i<n_col_row; i++){
            for(int j=0; j<n_col_row; j++){

                random = (rand () % 100)+1;

                if(random >0 && random <=p_nessun_pericolo){
                    scacchiera[i * n_col_row + j].pericolo = nessun_pericolo;
                }else if(random >p_nessun_pericolo && random <=p_nessun_pericolo+p_trappola){
                    scacchiera[i * n_col_row + j].pericolo = trappola;
                } else if(random >p_nessun_pericolo+p_trappola && random <=p_nessun_pericolo+p_trappola+p_alieno){
                    scacchiera[i * n_col_row + j].pericolo = alieno;
                }
                
                random = (rand () % 100)+1;

                if(random >0 && random <=p_nessun_oggetto){
                    scacchiera[i * n_col_row + j].oggetto = nessun_oggetto;
                }else if(random >p_nessun_oggetto && random <=p_nessun_oggetto+p_medikit){
                    scacchiera[i * n_col_row + j].oggetto = medikit;
                } else if(random >p_nessun_oggetto+p_medikit && random <= p_nessun_oggetto+p_medikit+p_pozione){
                    scacchiera[i * n_col_row + j].oggetto = pozione;
                } else if(random >p_nessun_oggetto+p_medikit+p_pozione && random <= p_nessun_oggetto+p_medikit+p_pozione+p_materiale){
                    scacchiera[i * n_col_row + j].oggetto = materiale;
                } else if(random >p_nessun_oggetto+p_medikit+p_pozione+p_materiale && random <= p_nessun_oggetto+p_medikit+p_pozione+p_materiale+p_colpi_lanciarazzi){
                    scacchiera[i * n_col_row + j].oggetto = colpi_lanciarazzi;
                }

            }
        }

        ninja.x = (rand () % n_col_row), ninja.y = (rand () % n_col_row);
        ciccio.x = (rand () % n_col_row), ciccio.y = (rand () % n_col_row);
    } else {
        int ap_n_col_row = n_col_row-2;

        Cella *appoggioscach = calloc((ap_n_col_row)*(ap_n_col_row), sizeof(struct Cella));

        for(int i=1; i<n_col_row-1; i++){
            for(int j=1; j<n_col_row-1; j++){
                appoggioscach[(i-1) * ap_n_col_row + (j-1)].oggetto =  scacchiera[i * n_col_row + j].oggetto;
                appoggioscach[(i-1) * ap_n_col_row + (j-1)].pericolo =  scacchiera[i * n_col_row + j].pericolo;
            }
        }

        fflush(stdout);

        n_col_row = ap_n_col_row;

        scacchiera = realloc(scacchiera, sizeof(struct Cella)*(n_col_row)*(n_col_row));

        for(int i=0; i<n_col_row; i++){
            for(int j=0; j<n_col_row; j++){
                scacchiera[i * n_col_row + j].oggetto = appoggioscach[i * n_col_row + j].oggetto;
                scacchiera[i * n_col_row + j].pericolo = appoggioscach[i * n_col_row + j].pericolo;
            }
        }
        free(appoggioscach);
    }
}

static void reset_game(){
    /*Re-Init stats Giocatori*/
    ciccio.kills = 0, ninja.kills = 0;
    for(int i=0; i<4; i++){
        ciccio.oggetti[i]=0;
        ninja.oggetti[i]=0;
    }
    ciccio.stato = solo_vita, ninja.stato = solo_vita;

    creata = false;

    /*Re-Init scacchiera*/
    free(scacchiera);
    scacchiera = NULL;

    /*Re-Init torri*/
    delete_all(torre_ciccio.testa);
    delete_all(torre_ninja.testa);

    torre_ciccio.testa = NULL;
    torre_ciccio.coda = NULL;
    torre_ninja.testa = NULL;
    torre_ninja.coda = NULL;
}

static void printstats(Giocatore attuale){
    printf("Stats:\n");
    printf("\t- Stato( ");
    switch(attuale.stato){
        case vulnerabile:
            printf("vulnerabile )\n");
            break;
        case solo_vita:
            printf("solo_vita )\n");
            break;
        case solo_scudo:
            printf("solo_scudo )\n");
            break;
        case scudo_vita:
            printf("scudo_vita )\n");
            break;
    }

    printf("\t- Kills( %d )\n", attuale.kills);
    printf("\t- Posizione ( x:%d-y:%d )\n", attuale.x, attuale.y);
    printf("\t- Lo zaino contiene:\n");
    printf("\t\tMedikit: %d\n", attuale.oggetti[0]);
    printf("\t\tPozione: %d\n", attuale.oggetti[1]);
    printf("\t\tMateriali: %d\n", attuale.oggetti[2]);
    printf("\t\tColpi Lanciarazzi: %d\n\n", attuale.oggetti[3]);

}

static void scontro_finale(){
    printf("Scontro Finale\n");
    fflush(stdout);

    //a seconda del numero di kills i giocatori avranno dei colpi lanciarazzi in più (ogni 2 kill una in più)
    ninja.oggetti[3] += (ninja.kills/2);
    ciccio.oggetti[3] += (ciccio.kills/2);


    // vince chi dopo l'uso dei lanciarazzi ha piu materiale o chi rimane con piu lanciarazzi in caso di stessa quantita di materiale
    if(ciccio.oggetti[2] == 0 && ninja.oggetti[2] == 0){
        printf("nessuno dei due ha materiale\n");
        if(ciccio.oggetti[3] == ninja.oggetti[3]){
            printf("partita patta, entrambi hanno lo stesso numero di 'colpi lanciarazzi'\n");
            return;
        } else if(ciccio.oggetti[3] > ninja.oggetti[3]){
            printf("Ciccio WINS, ha piu 'colpi lanciarazzi'\n");
            vittorie_ciccio++;
            return;
        } else {
            printf("Ninja WINS, ha piu 'colpi lanciarazzi'\n");
            vittorie_ninja++;
            return;
        }
    } else {
        if(ciccio.oggetti[2] == 0){
            printf("Ninja WINS, Ciccio non ha materiale\n");
            vittorie_ninja++;
            return;
        }
        if(ninja.oggetti[2] == 0){
            printf("Ciccio WINS, Ninja non ha materiale\n");
            vittorie_ciccio++;
            return;
        }
        for(int i=0; i<ciccio.oggetti[2]; i++){
            //aggiungi piano
            ins_piano(&torre_ciccio, i+1);
        }
        for(int i=0; i<ninja.oggetti[2]; i++){
            //aggiungi piano
            ins_piano(&torre_ninja, i+1);
        }

        printf("\n**Stampa Torre Ciccio**\n");
        stampa_torre(torre_ciccio.coda);

        printf("\n**Stampa Torre Ninja**\n");
        stampa_torre(torre_ninja.coda);

        if(ciccio.oggetti[3]>0){
            printf("\n**Ciccio colpisci!!**\n");
            while(ciccio.oggetti[3]>0 && ninja.oggetti[2] > 0){
                int choose;
                printf("Colpisci ?: colpi rimasti( %d )\n1) si!\n2) no!\n", ciccio.oggetti[3]);
                fflush(stdout);
                scanf("%d", &choose);
                if(choose == 1){
                    if((rand() % 101)>50){
                        ninja.oggetti[2]--;
                        ciccio.oggetti[3]--;
                        delete_last(&torre_ninja);
                        printf("distrutto l'ultimo piano!\n");
                    } else {
                        ciccio.oggetti[3]--;
                        printf("colpo mancato\n");
                    }
                } else if(choose == 2){
                    break;
                }
            }
            if(ninja.oggetti[2] > 0){
                printf("\n**Stampa Torre Ninja**\n");
                stampa_torre(torre_ninja.coda);
            }
        }

        if(ninja.oggetti[3]>0){
            printf("\n**ninja colpisci!!**\n");
            while(ninja.oggetti[3]>0 && ciccio.oggetti[2] > 0){
                int choose;
                printf("Colpisci ?: colpi rimasti( %d )\n1) si!\n2) no!\n", ninja.oggetti[3]);
                fflush(stdout);
                scanf("%d", &choose);
                if(choose == 1){
                    if((rand() % 101)>50){
                        ciccio.oggetti[2]--;
                        ninja.oggetti[3]--;
                        delete_last(&torre_ciccio);
                        printf("distrutto l'ultimo piano!\n");
                    } else {
                        ninja.oggetti[3]--;
                        printf("colpo mancato\n");
                    }
                } else if(choose == 2){
                    break;
                }
            }
            if(ciccio.oggetti[2] > 0){
                printf("\n**Stampa Torre Ciccio**\n");
                stampa_torre(torre_ciccio.coda);
            }
        }

        printf("\n");

        if(ninja.oggetti[2] == ciccio.oggetti[2]){
            if(ninja.oggetti[3] == ciccio.oggetti[3]){
                printf("partita patta!!, stesso numero di piani sulle torri e stesso numero di 'colpi lanciarazzi'\n");
                return;
            } else if(ninja.oggetti[3] > ciccio.oggetti[3]){
                printf("Ninja WINS, stesso numero di piani sulle torri ma più 'colpi lanciarazzi'\n");
                vittorie_ninja++;
                return;
            } else {
                printf("Ciccio WINS, stesso numero di piani sulle torri ma più 'colpi lanciarazzi'\n");
                vittorie_ciccio++;
                return;
            }
        } else if(ninja.oggetti[2] > ciccio.oggetti[2]){
            printf("Ninja WINS, ha più piani sulla torre\n");
            vittorie_ninja++;
            return;
        } else {
            printf("Ciccio WINS, ha più piani sulla torre\n");
            vittorie_ciccio++;
            return;
        }
    }
}

static void gioca(_Bool normal_mode){
    system("clear");
    turno = 0;
    while(1){
        if(turno % 2 == 0){
            printf_from_file("turnociccio.txt", ANSI_COLOR_GREEN);
        } else {
            printf_from_file("turnoninja.txt", ANSI_COLOR_RED);
        }
        if(normal_mode){
            if((turno) % (n_col_row) == 0 && turno != 0){
                printf("\nrestringimento !!!!\n\n");
                restringimento(true);
                if(ciccio.x == ninja.x && ciccio.y == ninja.y){
                    fflush(stdout);
                    system("clear");
                    printf_from_file("scontrofinale.txt", ANSI_COLOR_MAGENTA);
                    stampa_scacchiera(true);
                    scontro_finale();
                    reset_game();
                    press_enter();
                    return;
                }
                stampa_scacchiera(true);
            } else {
                stampa_scacchiera(true);
            }
        } else {
            if(turno % 4 == 0 && turno != 0 && n_col_row > 2){
                printf("\nrestringimento !!!!\n\n");
                ciccio.x--, ciccio.y--;
                ninja.x--, ninja.y--;
                restringimento(false);
                stampa_scacchiera(true);
                if((((ninja.x < 0) || (ninja.x > (n_col_row-1))) || ((ninja.y < 0) || (ninja.y > (n_col_row-1)))) && (((ciccio.x < 0) || (ciccio.x > (n_col_row-1))) || ((ciccio.y < 0) || (ciccio.y > (n_col_row-1))))){
                    printf("Entrambi morti per causa della tempesta\n");
                    reset_game();
                    press_enter();
                    return;
                } else if(((ninja.x < 0) || (ninja.x > (n_col_row-1))) || ((ninja.y < 0) || (ninja.y > (n_col_row-1)))){
                    printf("Ninja morto per causa della tempesta\n");
                    vittorie_ciccio++;
                    reset_game();
                    press_enter();
                    return;
                } else if(((ciccio.x < 0) || (ciccio.x > (n_col_row-1))) || ((ciccio.y < 0) || (ciccio.y > (n_col_row-1)))){
                    printf("Ciccio morto per causa della tempesta\n");
                    vittorie_ninja++;
                    reset_game();
                    press_enter();
                    return;
                }
            } else {
                stampa_scacchiera(true);
            }
        }
        if(turno % 2 == 0){ //turno di ciccio
            //printf("\n*** Turno di Ciccio ***\n\n");
            printstats(ciccio);
            int choose;
            printf("CHOOSE:\n1)Muovi\n2)Usa Oggetto\n3)Termina partita\n");
            fflush(stdout);
            scanf("%d", &choose);

            switch(choose){
                case 1:
                    fflush(stdout);
                    if(!muovi(&ciccio)){
                        reset_game();
                        press_enter();
                        return;
                    }
                    if(ciccio.x == ninja.x && ciccio.y == ninja.y){
                        press_enter();
                        printf_from_file("scontrofinale.txt", ANSI_COLOR_MAGENTA);
                        stampa_scacchiera(true);
                        scontro_finale();
                        reset_game();
                        press_enter();
                        return;
                    }
                    press_enter();
                    break;
                case 2:
                    usa_oggetto(&ciccio);
                    press_enter();
                    break;
                case 3:
                    reset_game();
                    printf("Ciccio ha abbandonato\n");
                    press_enter();
                    return;
                default:
                    printf("ritenta...\n");
                    turno--;
                    press_enter();
                    break;
            }
        } else { //turno di ninja
            //printf("\n--- Turno di Ninja ---\n\n");
            printstats(ninja);
            int choose;
            printf("CHOOSE:\n1)Muovi\n2)Usa Oggetto\n3)Termina partita\n");
            fflush(stdout);
            scanf("%d", &choose);

            switch(choose){
                case 1:
                    if(!muovi(&ninja)){
                        reset_game();
                        press_enter();
                        return;
                    }
                    if(ciccio.x == ninja.x && ciccio.y == ninja.y){
                        press_enter();
                        printf_from_file("scontrofinale.txt", ANSI_COLOR_MAGENTA);
                        stampa_scacchiera(true);
                        scontro_finale();
                        reset_game();
                        press_enter();
                        return;
                    }
                    press_enter();
                    break;
                case 2:
                    usa_oggetto(&ninja);
                    press_enter();
                    break;
                case 3:
                    reset_game();
                    printf("Ninja ha abbandonato\n");
                    press_enter();
                    return;
                default:
                    printf("ritenta...\n");
                    turno--;
                    press_enter();
                    break;
            }
        }
        turno ++;
    }
}

static void termina_gioco(){
    printf("Il gioco termina con la seguente situazione:\nCiccio -> vittorie ( %d )\nNinja  -> vittorie ( %d )\n", vittorie_ciccio, vittorie_ninja);
}

static void choose_game(){
    while(1){
        int choose;
        printf_from_file("mainmenu.txt", ANSI_COLOR_GREEN);
        printf("\nCHOOSE:\n1) Modalita' normale\n2) Modalita alternativa -> 'restringemento con mantenimento della memoria dinamica e con offset dei soli bordi'\n3) Indietro\n");
        fflush(stdout);
        scanf("%d", &choose);
        system("clear");

        switch(choose){
            case 1:
                init_position(true);
                gioca(true);
                return;
                break;
            case 2:
                init_position(false);
                gioca(false);
                return;
                break;
            case 3:
                return;
            default:
                break;
        }
    }
}

void init_menu(){

    /*ninja.oggetti[2] = 3;
    ciccio.oggetti[2] = 3;
    ninja.oggetti[3] = 3;
    ciccio.oggetti[3] = 3;

    scontro_finale();
    //reset_game();
    scontro_finale();*/

    system("clear");
    ciccio.stato = solo_vita;
    ninja.stato = solo_vita;
    while(1){
        int choose;
        printf_from_file("mainmenu.txt", ANSI_COLOR_GREEN);
        printf("\nCHOOSE:\n1) Crea mappa\n2) Gioca\n3) Termina Gioco\n");
        fflush(stdout);
        scanf("%d", &choose);
        system("clear");

        switch(choose){
            case 1:
                crea_mappa();
                break;
            case 2:
                if(creata){
                    choose_game();
                } else {
                    printf_from_file("mainmenu.txt", ANSI_COLOR_GREEN);
                    printf("Crea la mappa\n");
                    press_enter();
                }
                break;
            case 3:
                printf_from_file("mainmenu.txt", ANSI_COLOR_GREEN);
                termina_gioco();
                return;
            default:
                break;
        }
    }
}
