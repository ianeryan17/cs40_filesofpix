#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "seq.h"
#include "assert.h"

/*
parsealine
input: pointers to pointers to char arrays datapp (holding line to be 
        parsed), digits and infusion (to hold parsed line), sequences alldigits 
        and allinfusions (to hold digits and infusions to allow for memory 
        clean up later), and pointer to integer dlen to keep track of line 
        width for later printing.
output: returns integer length of infusion string to be used later with atoms
purpose: split the given datapp line into strings holding just the digits and 
         just the whitespace infusion characters
*/
int parsealine(char **datapp, int **digits, char **infusion, Seq_T 
                *alldigits, Seq_T *allinfusions, int *dlen, int bytes) {
    if (bytes > 1000) {
        *digits = malloc(bytes * 2);
        *infusion = malloc(bytes * 2);
    } else {
        *digits = malloc(1000);
        *infusion = malloc(1000);
    }
    assert(*digits != NULL);
    assert(*infusion != NULL);

    // counter for datapp parsing, ilen for infusion length, holder for temp 
    // digit storage, dcounter for number of digits read
    int counter = 0; 
    int ilen = 0;
    int holder = 0;
    int dcounter = 0;

    while ((*datapp)[counter] != '\n') {
        if ((*datapp)[counter] >= 48 && (*datapp)[counter] <= 57) {
            //digit case
            holder = holder * 10;
            holder += ((*datapp)[counter] - 48);
            dcounter++;

        } else {
            //infusion case
            (*infusion)[ilen] = (*datapp)[counter];
            //conditional for digits previously read
            if (dcounter > 0) {
                (*digits)[*dlen] = holder;
                (*dlen)++;
                holder = 0;
                dcounter = 0;
            }
            ilen++;
        }
        counter++;
    }
    // leftover digits when newline is encountered
    if (dcounter > 0) {
        (*digits)[*dlen] = holder;
        (*dlen)++;
    }

    // add strings to sequences for later memory cleanup
    Seq_addhi(*alldigits, *digits);
    Seq_addhi(*allinfusions, *infusion);

    return ilen; //returns length of infusion to be used in tablecompare
}