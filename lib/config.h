#ifndef CONFIG_H
#define CONFIG_H

#include <cjson/cJSON.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char name[256];
  int edges;
  int nodes;
  int expected_edges;
  int expected_nodes;
  bool ai;
} TestCase;

cJSON *readConfig();
cJSON *getConfigValue(char *);
TestCase *getTests(cJSON *, int *);

#endif
