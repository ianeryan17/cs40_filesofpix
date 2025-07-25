#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "table.h"
#include "atom.h"
#include "seq.h"

// tablecompare
// input: a pointer to a Hanson table, a pointer to a Hanson sequence, 3
//        pointers to pointers to char arrays, an integer containing the
//        length of the infusion sequence
// output: none
// purpose: creates a Hanson atom from the infusion sequence in the arguments,
//          then uses that atom as the key and the digit sequence as the value
//          in a table entry. If a value is output while performing table_put,
//          that value is added to the original line sequence, and that
//          infusion sequence is saved as the whitespace key.
void tablecompare(Table_T *T, Seq_T *originals, int **digits, char **infusion,
                  const char **wskey, int ilen){
    const char *infusion_atom = Atom_new(*infusion, ilen); 
    int *line = Table_put(*T, infusion_atom, *digits); 

    if (line != NULL){ //if a value is output, it is an original line
        Seq_addhi(*originals, line);
        if (*wskey == NULL){ //saves infusion string as the whitespace key
            *wskey = infusion_atom;
        }
    }
}