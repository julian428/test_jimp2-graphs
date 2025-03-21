#ifndef UTILS_H
#define UTILS_H

#include <time.h>

#include "config.h"

char *getLogName();
int graphIsDirectional(int *, const int);
char *concat(const char *, const char *);
int generateGraphFiles(TestCase, char *, char *);

#endif
