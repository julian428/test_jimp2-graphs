#include <stdio.h>
#include <stdlib.h>

#include "lib/config.h"
#include "lib/file-check.h"
#include "lib/utils.h"

int main(int argc, char **argv) {
  char *graph_file_name = "test_inputs/graph.txt";
  char *model = getConfigValue("model")->valuestring;
  char *endpoint = getConfigValue("api")->valuestring;

  int test_count;
  TestCase *tests = getTests(getConfigValue("tests"), &test_count);
  printf("\nParsed %d test cases:\n", test_count);

  for (int i = 0; i < test_count; i++) {
    printf("Test %d. %s\n", i + 1, tests[i].name);
    int nodes = tests[i].nodes;
    int edges = tests[i].edges;

    int file_parity = checkFileParity(graph_file_name, nodes, edges);
    printf("File parity sum: %d\n", file_parity);

    int *adjecency_matrix = (int *)calloc(nodes * nodes, sizeof(int));
    int graph_parity =
        checkGraphParity(graph_file_name, nodes, edges, adjecency_matrix);
    printf("Graph parity sum: %d\n", graph_parity);

    int isDirectional = graphIsDirectional(adjecency_matrix, nodes);
    printf("Is graph directional: %d\n", isDirectional);
  }
  free(tests);

  return 0;
}
