#include "utils.h"

int graphIsDirectional(int *adjecencyMatrix, const int nodes) {
  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < nodes; j++) {
      if (i == j)
        continue;
      if (adjecencyMatrix[i * nodes + j] == 1 &&
          adjecencyMatrix[j * nodes + i] == 1)
        return 0;
    }
  }
  return 1;
}

char *concat(const char *s1, const char *s2) {
  const size_t len1 = strlen(s1);
  const size_t len2 = strlen(s2);
  char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
  memcpy(result, s1, len1);
  memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
  return result;
}

int generateGraphFiles(TestCase test, char *model, char *endpoint) {
  char *command = "./jimp2-graphs/bin/graphgen";
  char *new_command = NULL;
  if (test.ai) {
    char *ai =
        (char *)malloc((12 + strlen(model) + strlen(endpoint)) * sizeof(char));
    sprintf(ai, " ai -m %s -u %s", model, endpoint);
    new_command = concat(command, ai);
    free(ai);
  } else
    new_command = command;

  FILE *graphgen = popen(new_command, "w");
  if (test.ai) {
    free(new_command);
  }
  if (graphgen == NULL) {
    fprintf(stderr, "Couldn't open process for graph generation.");
    return 1;
  }

  fprintf(graphgen, "%d %d", test.nodes, test.edges);
  fclose(graphgen);
  return system("mv graph.* test_inputs/");
}
