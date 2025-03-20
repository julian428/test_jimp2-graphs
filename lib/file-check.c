#include "file-check.h"

int checkFileParity(char *file_name, const int nodes, const int edges) {
  // the error is returned as a int that was a binary number
  // 000000 = 0 - success
  // 000001 = 1 - node conflict
  // 000010 = 2 - edge conflict
  // 000100 = 4 - no file
  // 001000 = 8 - wrong file format 1-st line
  // 010000 = 16 - wrong file format nodes
  // 100000 = 32 - wrong file format edges
  int error_return_value = 0;
  FILE *graph_file = fopen(file_name, "r");
  if (graph_file == NULL)
    return 4;

  int file_edges_count = 0, file_nodes_count = 0;
  if (fscanf(graph_file, "%d %d", &file_nodes_count, &file_edges_count) != 2)
    error_return_value += 8;

  if (file_edges_count != edges)
    error_return_value += 2;
  if (file_nodes_count != nodes)
    error_return_value += 1;

  // nodes
  char singleLetter;

  int count = 0;
  for (int i = 0; i < nodes; i++) {
    if (fscanf(graph_file, " %c", &singleLetter) == EOF)
      break;
    count++;
  }

  if (count != nodes)
    error_return_value += 16;

  // edges
  char first, second;
  count = 0;
  for (int i = 0; i < edges; i++) {
    if (fscanf(graph_file, " %c %c", &first, &second) == EOF)
      break;
    count++;
  }
  if (count != edges)
    error_return_value += 32;

  fclose(graph_file);
  return error_return_value;
}

int checkGraphParity(char *file_name, const int nodes, const int edges) {
  return 0;
}
