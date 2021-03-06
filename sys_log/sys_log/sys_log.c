#include "sys_log.h"

#define LOG_BUF 256

void Log_Degug(const char *fmt, ...) {
    char    buf[LOG_BUF];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF - 1, fmt, ap);

    openlog(NULL, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
    syslog(LOG_DEBUG, "<debug> %s", buf);
    closelog();
}

void Log_Warning(const char *fmt, ...) {
    char    buf[LOG_BUF];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF - 1, fmt, ap);

    openlog(NULL, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
    syslog(LOG_WARNING, "<warning> %s", buf);
    closelog();
}

void Log_Err(const char *fmt, ...) {
    char    buf[LOG_BUF];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF - 1, fmt, ap);

    openlog(NULL, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
    syslog(LOG_ERR, "<error> %s", buf);
    closelog();
}

void Log_Emerg(const char *fmt, ...) {
    char    buf[LOG_BUF];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF - 1, fmt, ap);

    openlog(NULL, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
    syslog(LOG_EMERG, "<emerg> %s", buf);
    closelog();
}

#undef LOG_BUF
