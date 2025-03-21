#include <stdio.h>
#include <stdlib.h>

#include "lib/config.h"
#include "lib/file-check.h"
#include "lib/utils.h"

int main(int argc, char **argv) {
  char *graph_file_name = "test_inputs/graph.txt";
  char *graph_image_name = "test_inputs/graph.png";

  char *model = getConfigValue("model")->valuestring;
  char *endpoint = getConfigValue("api")->valuestring;

  int test_count;
  TestCase *tests = getTests(getConfigValue("tests"), &test_count);
  printf("Testowanie programu \x1b[34mjimp2-graphs\x1b[0m.\n\n");

  for (int i = 0; i < test_count; i++) {
    printf("Test %d. %s\n", i + 1, tests[i].name);
    int nodes = tests[i].nodes;
    int edges = tests[i].edges;

    generateGraphFiles(tests[i], model, endpoint);

    int file_parity = checkFileParity(graph_file_name, nodes, edges);
    translateErrors(file_parity, "Zgodność pliku z założeniami.");

    int imageExists = checkImageExistance(graph_image_name);
    printf("\t%s. Zdjęcie grafu zostało wygenerowane.\n",
           imageExists ? "\x1b[32mPASSED\x1b[0m" : "\x1b[31mFAILED\x1b[0m");

    int *adjecency_matrix = (int *)calloc(nodes * nodes, sizeof(int));
    int graph_parity =
        checkGraphParity(graph_file_name, nodes, edges, adjecency_matrix);
    translateErrors(graph_parity, "Zgodność grafu z założeniami.");

    int isDirectional = graphIsDirectional(adjecency_matrix, nodes);
    printf("\t%s. Graf jest skierowany.\n",
           isDirectional ? "\x1b[32mPASSED\x1b[0m" : "\x1b[31mFAILED\x1b[0m");
  }
  free(tests);

  return 0;
}
