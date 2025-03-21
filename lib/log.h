#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

void initializeLog(char *);
void logTestData(TestCase, char *);
void log_printf(char *, const char *, ...);

#endif
