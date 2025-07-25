//parsaline:
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "seq.h"
#include "assert.h"

void parsealine(char **datapp, char **digits, char **infusion, Seq_T 
                *alldigits, Seq_T *allinfusions){
    // printf("parsing\n\n");
    *digits = malloc(1000);
    assert(*digits != NULL);
    *infusion = malloc(1000);
    assert(*infusion != NULL);

    int i = 0;
    int dlen = 0;
    int ilen = 0;

    bool digitread = false;
    while ((*datapp)[i] != '\n') {
        if ((*datapp)[i] >= 48 && (*datapp)[i] <= 57) {
            (*digits)[dlen] = (*datapp)[i];
            dlen++;
            digitread = true;
        } else {
            (*infusion)[ilen] = (*datapp)[i];
            ilen++;
            if (digitread == true) {
                (*digits)[dlen] = ' ';
                dlen++;
                digitread = false;
            }
        }
        i++;
    }
    (*digits)[dlen] = '\0';
    (*infusion)[ilen] = '\0';
    dlen++;
    ilen++;

    printf("before adding to sequences\n\n");
    printf("digits: %s\n\n", *digits);
    assert(alldigits != NULL);
    assert(*alldigits != NULL);
    Seq_addhi(*alldigits, *digits);

    printf("infusion: %s\n\n", *infusion);
    assert(allinfusions != NULL);
    assert(*allinfusions != NULL);
    printf("allinfusions length: %d\n\n", Seq_length(*allinfusions));
    Seq_addhi(*allinfusions, *infusion);
}

//restoration
#include "readaline.h"
#include "parsealine.c"
#include "tablecompare.c"
#include "printpgm.c"
#include "table.h"
#include "seq.h"
#include "atom.h"
#include "except.h"

#include "assert.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

static FILE *open_or_abort(char *fname, char *mode);
int get_width(char **lastline);
void free_mem(Table_T *T, Seq_T *originals, Seq_T *alldigits, Seq_T 
              *allinfusions);    

// function contraccccttttt
int main(int argc, char *argv[]) {
    char *datapp, *infusion, *digits;
    const char *wskey = NULL;

    Table_T T = Table_new(1000, NULL, NULL);
    Seq_T originals = Seq_new(1000);
    Seq_T alldigits = Seq_new(1000);
    Seq_T allinfusions = Seq_new(1000);

    char fname[25];
    assert(argc <= 2);
    if (argc == 1) {
        scanf("%s", fname);
    } else {
        strcpy(fname, argv[1]);
    }
    FILE *inputfd = open_or_abort(fname, "r");
    while (readaline(inputfd, &datapp) != 0) {
        parsealine(&datapp, &digits, &infusion, &alldigits, &allinfusions);
        tablecompare(&T, &originals, &digits, &infusion, &wskey);
        free(datapp);
    }

    // get final original line stored in table
    Seq_addhi(originals, Table_get(T, wskey));
    printpgm(&originals);

    free_mem(&T, &originals, &alldigits, &allinfusions);
    fclose(inputfd); 

    return EXIT_SUCCESS;
}

// function contract!!!
static FILE *open_or_abort(char *fname, char *mode) {
    FILE *fp = fopen(fname, mode);
    assert(fp != NULL);
    // if (fp == NULL) {
    //         int rc = errno;
    //         fprintf(stderr,
    //                 "Could not open file %s with mode %s\n",
    //                 fname,
    //                 mode);
    //         exit(rc);
    // }
    return fp;
}

void free_mem(Table_T *T, Seq_T *originals, Seq_T *alldigits, 
              Seq_T *allinfusions){
    int ADlen = Seq_length(*alldigits);
    int AIlen = Seq_length(*allinfusions);
    for (int i = 0; i < ADlen; i++) {
        void *line = Seq_get(*alldigits, i);
        if (line != NULL){
            free(line);
        }
    }
    for (int i = 0; i < AIlen; i++) {
        void *line = Seq_get(*allinfusions, i);
        if (line != NULL){
            free(line);
        }
    }
    
    Table_free(T);
    Seq_free(originals);
    Seq_free(alldigits);
    Seq_free(allinfusions);
}

/*
- runtime errors
    - input is expected but not supplied?
    - ferror?
- testing
- comments and contracts
- add higher than 1000 functionality to readaline
*/