#include "seq.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/*
printpgm
input: pointer to original line sequence, pointer to digitlen for width
output: nothing returned
purpose: for each original line stored in the originals sequence, print out the 
         digits as ascii characters
*/
void printpgm(Seq_T *originals, int *digitlen) {
    // header
    int width = *digitlen;
    int height = Seq_length(*originals);
    char *magicnumber = "P5";
    printf("%s\n%d %d\n%d\n", magicnumber, width, height, 255);   
    
    int *line_to_print;
    for (int i = 0; i < height; i++) {
        line_to_print = Seq_get(*originals, i);
        for (int j = 0; j < width; j++) {
            printf("%c", line_to_print[j]);
        }
    }
}