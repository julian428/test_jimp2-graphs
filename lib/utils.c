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
