#include <stdio.h>
#include <stdlib.h>

#include "lib/config.h"
#include "lib/file-check.h"
#include "lib/log.h"
#include "lib/utils.h"

int main(int argc, char **argv) {
  char *graph_file_name = "test_inputs/graph.txt";
  char *graph_image_name = "test_inputs/graph.png";
  char *log_name = getLogName();
  initializeLog(log_name);

  char *model = getConfigValue("model")->valuestring;
  char *endpoint = getConfigValue("api")->valuestring;

  int test_count;
  TestCase *tests = getTests(getConfigValue("tests"), &test_count);
  printf("Testowanie programu \x1b[34mjimp2-graphs\x1b[0m.\n\n");

  for (int i = 0; i < test_count; i++) {
    log_printf(log_name, "\x1b[1mTest %d\x1b[0m. %s\n", i + 1, tests[i].name);
    int nodes = tests[i].expected_nodes;
    int edges = tests[i].expected_edges;

    generateGraphFiles(tests[i], model, endpoint);

    int file_parity = checkFileParity(graph_file_name, nodes, edges);
    translateErrors(file_parity, "Zgodność pliku z założeniami.", log_name);

    int imageExists = checkImageExistance(graph_image_name);
    log_printf(log_name, "\t%s. Zdjęcie grafu zostało wygenerowane.\n",
               imageExists ? "\x1b[32mPASSED\x1b[0m" : "\x1b[31mFAILED\x1b[0m");

    int *adjecency_matrix = (int *)calloc(nodes * nodes, sizeof(int));
    int graph_parity =
        checkGraphParity(graph_file_name, nodes, edges, adjecency_matrix);
    translateErrors(graph_parity, "Zgodność grafu z założeniami.", log_name);

    int isDirectional =
        graphIsDirectional(adjecency_matrix, nodes) && (file_parity == 0);
    log_printf(log_name, "\t%s. Graf jest skierowany.\n",
               isDirectional ? "\x1b[32mPASSED\x1b[0m"
                             : "\x1b[31mFAILED\x1b[0m");
  }
  free(tests);

  return 0;
}
