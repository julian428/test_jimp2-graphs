#include "file-check.h"
#include <stdio.h>

// 0 - success
// 1 - node conflict
// 2 - edge conflict
// 3 - no file
int checkFileParity(char *file_name, int nodes, int edges) {
  FILE *graph_file = fopen(file_name, "r");
  if (graph_file == NULL)
    return 3;

  fclose(graph_file);
  return 0;
}
