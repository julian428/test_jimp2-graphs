#include <stdio.h>
#include <stdlib.h>

#include "lib/file-check.h"

int main(int argc, char **argv) {
  printf("Testowanie programu 'jimp2-graphs'.\n");

  int file_parity = checkFileParity("test.txt", 3, 3);
  printf("File parity sum: %d\n", file_parity);

  int *adjecency_matrix = (int *)calloc(3 * 3, sizeof(int));
  int graph_parity = checkGraphParity("test.txt", 3, 3, adjecency_matrix);
  printf("Graph parity sum: %d\n", graph_parity);
}
