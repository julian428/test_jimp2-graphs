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

char *getConfigValue(char *value_name) {
  cJSON *config = readConfig();
  cJSON *configValue = cJSON_GetObjectItemCaseSensitive(config, value_name);

  if (cJSON_IsString(configValue) && (configValue->valuestring != NULL)) {
    char *value = configValue->valuestring;
    return value;
  }

  cJSON_Delete(config);
  return NULL;
}
