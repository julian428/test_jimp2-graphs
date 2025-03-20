#ifndef CONFIG_H
#define CONFIG_H

#include <cjson/cJSON.h>
#include <stdio.h>

cJSON *readConfig();
char *getConfigValue(char *);

#endif
