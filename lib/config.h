#ifndef CONFIG_H
#define CONFIG_H

#include <cjson/cJSON.h>
#include <stdio.h>

cJSON *readConfig();
cJSON *getConfigValue(char *);

#endif
