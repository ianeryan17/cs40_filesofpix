#include "readaline.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "assert.h"

// readaline
// input: file pointer to the corrupted pgm file, pointer to char array to hold 
//        first line
// output: returns length of line in bytes
// purpose: read one line from the provided file
size_t readaline(FILE *inputfd, char **datapp) {
    // checked runtime errors
    assert(datapp != NULL);
    assert(inputfd != NULL);

    int length = 0;
    char c;
    c = fgetc(inputfd);
    if (c == EOF) {
        *datapp = NULL;
        return 0;
    }
    int heapsize = 1000;
    *datapp = malloc(heapsize);
    assert(*datapp != NULL);

    while (c != '\n') {
        (*datapp)[length] = c;
        length++;
        c = fgetc(inputfd);
        assert(ferror(inputfd) == 0);
        // assert(length <= 1000);
        if (length == heapsize){
            heapsize += 1000;
            *datapp = realloc(*datapp, heapsize);
        }
    }
    
    // add newline as sentinel value for later
    (*datapp)[length] = '\n';
    length++;
    
    return length;
}