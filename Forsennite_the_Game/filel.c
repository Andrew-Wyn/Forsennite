#include"game.h"
#include"filel.h"


// ****Caricamento scacchiera da file binario****

extern int n_col_row;
extern _Bool creata;
extern unsigned int turno;
extern unsigned int vittorie_ciccio, vittorie_ninja;
extern int n_max;
extern int p_nessun_pericolo, p_trappola, p_alieno; 
extern int p_nessun_oggetto, p_medikit, p_pozione, p_materiale, p_colpi_lanciarazzi;
extern Cella *scacchiera;

void save_scacchiera(char *fileName){
    char appo[30] = "./saved/";
    strcat(appo, fileName);
    strcat(appo, ".bin");
    FILE *file;
    file=fopen(appo,"wb");
    if (!file){
        printf("problemi nell'apertura del file '%s'", appo);
        return;
    }

    for(int i=0; i<n_col_row; i++){
        for(int j=0; j<n_col_row; j++){
            fwrite((scacchiera + (i * n_col_row + j)), sizeof(Cella), 1, file);
        }
    }

    fclose(file);
}

int print_files_name(){
    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir("./saved/");

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return true;
    }

    _Bool _void = true;

    // for readdir()
    while ((de = readdir(dr)) != NULL){
        if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            printf("- %s\n", de->d_name), _void = false;
    }

    if(_void){
        printf("Nessun file salvato\n");
    }
    closedir(dr);

    return _void;
}

void load_scacchiera(char* fileName){
    creata = false;
    n_col_row = 0;
    char appo[30] = "./saved/";
    strcat(appo, fileName);
    strcat(appo, ".bin");
    FILE *file = fopen(appo, "rb");
    //Beta-Tested by: ALEXX   
    
    int n_nessun_pericolo = 0, n_trappola = 0, n_alieno = 0;
    int n_nessun_oggetto = 0, n_medikit = 0, n_pozione = 0, n_materiale = 0, n_colpi_lanciarazzi = 0;

    if (file == NULL && !file){
        printf("problemi nell'apertura del file '%s'\n", appo);
        fflush(stdout);
        return; //could not open file
    } else {
        if(scacchiera != NULL){
            free(scacchiera);
            scacchiera = NULL;
        }

        scacchiera = malloc(sizeof(Cella));

        Cella appocella;
        while (1) {
            fread(&appocella, sizeof(Cella), 1, file);
            if(feof(file)) {
                break;
            }

            switch(appocella.pericolo){
              case nessun_pericolo:
                n_nessun_pericolo++;
                break;
              case trappola:
                n_trappola++;
                break;
              case alieno:
                n_alieno++;
                break;
            }

            switch(appocella.oggetto){
              case nessun_oggetto:
                n_nessun_oggetto++;
                break;
              case medikit:
                n_medikit++;
                break;
              case pozione:
                n_pozione++;
                break;
              case materiale:
                n_materiale++;
                break;
              case colpi_lanciarazzi:
                n_colpi_lanciarazzi++;
                break;
            }

            *(scacchiera + n_col_row) = appocella;
            scacchiera = realloc(scacchiera, sizeof(Cella)*((++n_col_row)+1));
            fflush(stdout);
        }

        p_nessun_pericolo = (n_nessun_pericolo*100)/n_col_row;
        p_trappola = (n_trappola*100)/n_col_row;
        p_alieno = (n_alieno*100)/n_col_row;

        while(p_nessun_pericolo + p_trappola + p_alieno < 100){
          p_nessun_pericolo++;
        }

        p_nessun_oggetto = (n_nessun_oggetto*100)/n_col_row;
        p_medikit = (n_medikit*100)/n_col_row;
        p_pozione = (n_pozione*100)/n_col_row;
        p_materiale = (n_materiale*100)/n_col_row;
        p_colpi_lanciarazzi = (n_colpi_lanciarazzi*100)/n_col_row;

        //sostituire
        while(p_nessun_oggetto + p_medikit + p_pozione + p_materiale + p_colpi_lanciarazzi < 100){
          p_nessun_oggetto++;
        }

        n_col_row = sqrt(n_col_row);
        creata = true;
        fclose(file);
    }
}
