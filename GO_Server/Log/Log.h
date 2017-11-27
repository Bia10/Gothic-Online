#ifndef LOG_H
#define LOG_H

#include <io.h>
#include <stdarg.h>
#include <stdio.h>

#define LOG go_log

void go_log(const char* format, ...);

#endif //LOG_H