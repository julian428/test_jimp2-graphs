#ifndef FILE_CHECK_H
#define FILE_CHECK_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "log.h"

void translateErrors(int, char *, char *, const char **);
char *getNodes(FILE *, const int);
int getNodeIndex(char *, int, const char);
int checkFileParity(char *, const int, const int);
int checkGraphParity(char *, const int, int, int *);
int checkImageExistance(char *);

#endif
