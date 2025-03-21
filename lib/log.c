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

void logTestData(TestCase test, char *graph_file_name) {}

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
