#include "file-check.h"

int checkFileParity(char *file_name, const int nodes, const int edges) {
  // the error is returned as a int that was a binary number
  // 0000000 = 0 - success
  // 0000001 = 1 - node conflict
  // 0000010 = 2 - edge conflict
  // 0000100 = 4 - no file
  // 0001000 = 8 - wrong file format 1-st line
  // 0010000 = 16 - wrong file format nodes
  // 0100000 = 32 - wrong file format edges
  // 1000000 = 64 - reapeating nodes
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

  char singleLetter;
  char *letters = (char *)malloc(sizeof(char) * nodes);
  int count = 0;
  for (int i = 0; i < nodes; i++) {
    if (fscanf(graph_file, " %c", &singleLetter) == EOF)
      break;
    count++;
    letters[i] = singleLetter;
  }

  if (count != nodes)
    error_return_value += 16;
  for (int i = 0; i < nodes; i++) {
    int b = 0;

    for (int j = i + 1; j < nodes - 1; j++) {
      if (letters[i] != letters[j])
        continue;
      error_return_value += 64;
      b = 1;
      break;
    }

    if (b)
      break;
  }
  free(letters);

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
