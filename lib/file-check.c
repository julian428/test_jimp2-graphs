#include "file-check.h"

// the error is returned as a int that was a binary number
// 000000 = 0 - success
// 000001 = 1 - node conflict
// 000010 = 2 - edge conflict
// 000100 = 4 - no file
// 001000 = 8 - wrong file format 1-st line
// 010000 = 16 - wrong file format nodes
// 100000 = 32 - wrong file format edges

void translateErrors(int error_value, char *title) {
  printf("\t%s. %s\n",
         error_value == 0 ? "\x1b[32mPASSED\x1b[0m" : "\x1b[31mFAILED\x1b[0m",
         title);
  const int error_count = 6;
  const char *errors[] = {
      "Niezgodna ilość wierzchołków.",
      "Niezgodna ilość krawędzi.",
      "Brak pliku.",
      "Nieprawidłowy format deklaracji wierchołków i krawędzi w pliku.",
      "Nieprawidłowy format wierchołków.",
      "Nieprawidłowy format krawędzi."};
  int error_sum = error_value;
  for (int i = 0; i < error_count; i++) {
    int reverse_value = error_count - 1 - i;
    int twoPower = pow(2, reverse_value);
    if (error_sum < twoPower)
      continue;
    error_sum -= twoPower;
    printf("\t\t- %s\n", errors[reverse_value]);
  }
}

char *getNodes(FILE *graph_file, const int nodes) {
  char singleLetter;
  char *nodeLetters = (char *)calloc(nodes, sizeof(char));
  if (nodeLetters == NULL) {
    fprintf(stderr, "Nie udało się zdobyć pamięci dla wierzchołków.\n");
    return NULL;
  }

  for (int i = 0; i < nodes; i++) {
    if (fscanf(graph_file, " %c", &singleLetter) == EOF)
      break;
    nodeLetters[i] = singleLetter;
  }
  return nodeLetters;
}

int getNodeIndex(char *nodeLetters, int length, char node) {
  for (int i = 0; i < length; i++) {
    if (nodeLetters[i] == node)
      return i;
  }
  return -1;
}

int checkFileParity(char *file_name, const int nodes, const int edges) {
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

  char *nodeLetters = getNodes(graph_file, nodes);

  for (int i = 0; i < nodes; i++) {
    if (nodeLetters[i] != 0)
      continue;
    error_return_value += 16;
    break;
  }

  free(nodeLetters);

  // edges
  char first, second;
  int count = 0;
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

int checkGraphParity(char *file_name, const int nodes, const int edges,
                     int *adjecency_matrix) {
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
  char *nodeLetters = getNodes(graph_file, nodes);

  for (int i = 0; i < nodes - 1; i++) {
    int b = 0;
    for (int j = i + 1; j < nodes; j++) {
      if (nodeLetters[i] != nodeLetters[j])
        continue;
      b = 1;
      error_return_value += 16;
      break;
    }
    if (b)
      break;
  }

  // edges
  char first, second;

  for (int i = 0; i < edges; i++) {
    if (fscanf(graph_file, " %c %c", &first, &second) == EOF)
      break;
    int y = getNodeIndex(nodeLetters, nodes, first);
    int x = getNodeIndex(nodeLetters, nodes, second);
    if (y < 0 || x < 0) {
      error_return_value += 32;
      break;
    }
    adjecency_matrix[y * nodes + x] = 1;
  }

  free(nodeLetters);
  fclose(graph_file);
  return error_return_value;
}

int checkImageExistance(char *file_name) {
  return access(file_name, F_OK) == 0;
}
