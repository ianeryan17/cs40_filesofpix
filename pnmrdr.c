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
#include "pnmrdr.h"

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;
    FILE *inputfd = fopen(argv[1], "r");
    // inputfd = stdin;
    // if (argc == 1) {
    //     inputfd = stdin;
    // } else {
    //     inputfd = open_or_abort(argv[1], "r");
    // }

    Pnmrdr_T reader = Pnmrdr_new(inputfd);
    Pnmrdr_mapdata data = Pnmrdr_data(reader);

    // get pixel count
    int width = data.width;
    int height = data.height;

    printf("%s\n%d\n%d\n%d\n", "p5", data.width, data.height, data.denominator);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            printf("%c ", Pnmrdr_get(reader));
        }
        printf("\n");
    }

    fclose(inputfd);
    Pnmrdr_free(&reader);
}