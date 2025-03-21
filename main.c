#include <stdio.h>
#include <stdlib.h>

#include "lib/config.h"
#include "lib/file-check.h"
#include "lib/utils.h"

int main(int argc, char **argv) {
  char *graph_file_name = "graph.txt";
  char *graph_image_name = "graph.png";
  int nodes = 15;
  int edges = 60;

  printf("Graph AI Model: %s\n", getConfigValue("graph_model")->valuestring);
  printf("Graph Image Model: %s\n", getConfigValue("image_model")->valuestring);
  printf("AI Endpoint: %s\n", getConfigValue("api")->valuestring);
  printf("Tests count: %d\n", cJSON_GetArraySize(getConfigValue("tests")));

  printf("Testowanie programu 'jimp2-graphs'.\n");

  int file_parity = checkFileParity(graph_file_name, nodes, edges);
  printf("File parity sum: %d\n", file_parity);

  int *adjecency_matrix = (int *)calloc(nodes * nodes, sizeof(int));
  int graph_parity =
      checkGraphParity(graph_file_name, nodes, edges, adjecency_matrix);
  printf("Graph parity sum: %d\n", graph_parity);

  int isDirectional = graphIsDirectional(adjecency_matrix, nodes);
  printf("Is graph directional: %d\n", isDirectional);
}
