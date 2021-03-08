#ifndef _SERIAL_H
#define _SERIAL_H

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys_log.h>
#include <sys_utils.h>
#include <termios.h>
#include <unistd.h>

extern int32_t serial_Open(const uint8_t* dev, uint32_t baudrate, uint32_t databit, uint32_t stopbit, uint32_t parity);
extern void    Serial_Close(int32_t serial_fd);
extern void    Serial_Clear(int32_t serial_fd);

#endif
