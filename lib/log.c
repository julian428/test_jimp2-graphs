#include "log.h"

void initializeLog(char *log_file_name) {
  int createLogDir = system("mkdir -p logs 2> /dev/null");
  FILE *log_file = fopen(log_file_name, "w");
  if (log_file == NULL) {
    fprintf(stderr, "Nie udało się zainicjalizować pliku z logami.\n");
    return;
  }

  fprintf(log_file, "nazwa pliku: %s\n", log_file_name);
  fclose(log_file);
  return;
}

void logTestData(TestCase test, char *log_file_name, char *graph_file_name,
                 int *adjecency_matrix) {
  FILE *log_file = fopen(log_file_name, "a");
  if (log_file == NULL) {
    fprintf(stderr, "Nie udało się otworzyć pliku z logami.");
    return;
  }

  fprintf(log_file, "\n\n--- Szczegóły Testu: %s ---\n\n", test.name);

  fprintf(log_file, "podane wierzchołki: %d | oczekiwane wierzchołki: %d\n",
          test.nodes, test.expected_nodes);
  fprintf(log_file, "podane krawędzie: %d | oczekiwane krawędzie: %d\n",
          test.edges, test.expected_edges);
  fprintf(log_file, "generowane przez ai: %s\n", test.ai ? "true" : "false");

  fprintf(log_file, "\nMacierz Sąsiedztwa: \n");
  for (int i = 0; i < test.expected_nodes * test.expected_nodes; i++) {
    if (i % test.expected_nodes == 0)
      fprintf(log_file, "\n");
    fprintf(log_file, "%d ", adjecency_matrix[i]);
  }

  fprintf(log_file, "\n\nWygenerowany graf: \n\n");
}

void log_printf(char *log_file_name, const char *format, ...) {
  va_list args;

  // Print to stdout
  va_start(args, format);
  vprintf(format, args);
  va_end(args);

  // Print to log file
  FILE *log = fopen(log_file_name, "a");
  if (log) {
    va_start(args, format);
    vfprintf(log, format, args);
    va_end(args);
    fclose(log);
  }
}
