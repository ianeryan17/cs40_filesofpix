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
void free_mem(Table_T *T, Seq_T *originals, Seq_T *alldigits, Seq_T 
              *allinfusions);    

// main
// input: integer for number of command line arguments, char array containing
//        command line arguments
// output: an integer depending on success or failure of function
// purpose: take in a corrupted pgm file and output a raw pgm file containing 
//          the original pgm pre-corruption
int main(int argc, char *argv[]) {
    char *datapp, *infusion;
    int *digits;
    const char *wskey = NULL;
    Table_T T = Table_new(1000, NULL, NULL);
    Seq_T originals = Seq_new(1000);
    Seq_T alldigits = Seq_new(1000);
    Seq_T allinfusions = Seq_new(1000);

    assert(argc <= 2);
    FILE *inputfd;
    if (argc == 1) {
        inputfd = stdin;
    } else {
        inputfd = open_or_abort(argv[1], "r");
    }

    int infusionlen = 0;
    int digitlen = 0;
    int bytes = 0;

    while ((bytes = readaline(inputfd, &datapp)) != 0) {
        digitlen = 0; 
        infusionlen = parsealine(&datapp, &digits, &infusion, &alldigits, &
                                 allinfusions, &digitlen, bytes);
        
        tablecompare(&T, &originals, &digits, &infusion, &wskey, infusionlen);
        free(datapp);
    }
    //adds final original line left remaining in table
    Seq_addhi(originals, (Table_get(T, wskey))); 
    printpgm(&originals, &digitlen);

    free_mem(&T, &originals, &alldigits, &allinfusions);
    fclose(inputfd); 

    return EXIT_SUCCESS;
}

// open_or_abort
// input: string containing the file name, string containing the file access 
//        mode
// output: returns a pointer to a file
// purpose: attempts to open the file in the arguments using the access mode in 
//          the arguments,
//          if unable to it returns an error
static FILE *open_or_abort(char *fname, char *mode) {
    FILE *fp = fopen(fname, mode);
    assert(fp != NULL);
    return fp;
}

// free_mem
// input: a pointer to a table, a pointer to the sequence of original lines,
//        all digits, and all infusions
// output: none
// purpose: frees memory associated with the tables and sequences including the
//          pointers within them
void free_mem(Table_T *T, Seq_T *originals, Seq_T *alldigits, 
              Seq_T *allinfusions){
    int ADlen = Seq_length(*alldigits);
    int AIlen = Seq_length(*allinfusions);
    //iterate through digit and infusion sequences, freeing all pointers created
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