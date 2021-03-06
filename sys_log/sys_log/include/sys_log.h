#ifndef _SYS_LOG_H
#define _SYS_LOG_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

extern void Log_Degug(const char *fmt, ...);
extern void Log_Warning(const char *fmt, ...);
extern void Log_Err(const char *fmt, ...);
extern void Log_Emerg(const char *fmt, ...);

#endif
