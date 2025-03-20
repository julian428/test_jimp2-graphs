#ifndef FILE_CHECK_H
#define FILE_CHECK_H

#include <stdio.h>
#include <stdlib.h>

char *getNodes(FILE *, const int);
int getNodeIndex(char *, int, const char);
int checkFileParity(char *, const int, const int);
int checkGraphParity(char *, const int, int, int *);

#endif
