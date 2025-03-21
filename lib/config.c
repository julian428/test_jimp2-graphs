#include "config.h"

cJSON *readConfig() {
  FILE *config_file = fopen("config.json", "r");
  if (config_file == NULL) {
    fprintf(stderr, "Nie udało się otworzyć pliku z konfiguracją.");
    return NULL;
  }

  char json_buffer[2048];
  int len = fread(json_buffer, 1, sizeof(json_buffer), config_file);
  fclose(config_file);
  json_buffer[len] = '\0';

  cJSON *config = cJSON_Parse(json_buffer);
  if (config == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      printf("Error: %s\n", error_ptr);
    }
    cJSON_Delete(config);
    return NULL;
  }

  return config;
}

cJSON *getConfigValue(char *value_name) {
  cJSON *config = readConfig();
  cJSON *configValue = cJSON_GetObjectItemCaseSensitive(config, value_name);

  if (configValue == NULL) {
    fprintf(stderr, "Key %s does not exist in config.", value_name);
  }

  return configValue;
}

TestCase *getTests(cJSON *json_array, int *length) {
  if (!cJSON_IsArray(json_array)) {
    fprintf(stderr, "The passed in cJSON object is not an array.");
    return NULL;
  }

  int tests_count = cJSON_GetArraySize(json_array);
  *length = tests_count;
  TestCase *tests = (TestCase *)malloc(tests_count * sizeof(TestCase));

  for (int i = 0; i < tests_count; i++) {
    cJSON *test = cJSON_GetArrayItem(json_array, i);

    // Extract test name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(test, "name");
    if (cJSON_IsString(name)) {
      strncpy(tests[i].name, name->valuestring, sizeof(tests[i].name));
    } else {
      strcpy(tests[i].name, "");
    }

    // Extract edges
    cJSON *edges = cJSON_GetObjectItemCaseSensitive(test, "edges");
    tests[i].edges = cJSON_IsNumber(edges) ? edges->valueint : 1;

    // Extract nodes
    cJSON *nodes = cJSON_GetObjectItemCaseSensitive(test, "nodes");
    tests[i].nodes = cJSON_IsNumber(nodes) ? nodes->valueint : 1;

    // Extract ai
    cJSON *ai = cJSON_GetObjectItemCaseSensitive(test, "ai");
    tests[i].ai = cJSON_IsBool(ai) ? ai->valueint : false;
  }

  return tests;
}
