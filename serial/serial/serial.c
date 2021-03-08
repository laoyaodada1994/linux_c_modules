#include "serial.h"

static uint32_t speed_arr[] = {
    B921600, B460800, B230400, B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300,
};
static uint32_t name_arr[] = {
    921600, 460800, 230400, 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300,
};

bool Serial_Set_Speed(uint32_t serial_fd, uint32_t speed) {
    struct termios option;

    tcgetattr(serial_fd, &option);
    cfmakeraw(&option);
    for (uint32_t i = 0; i < sizeof(speed_arr) / sizeof(uint32_t); i++) {
        if (speed == name_arr[i]) {
            tcflush(serial_fd, TCIOFLUSH);
            cfsetispeed(&option, speed_arr[i]);
            cfsetospeed(&option, speed_arr[i]);
            if (tcsetattr(serial_fd, TCSANOW, &option))
                Log_Err("%s-->%s() line %u: tcsetattr setting fail.\n", __FILE__, __func__, __LINE__);
            return true;
        }
        tcflush(serial_fd, TCIOFLUSH);
    }
    return false;
}

static bool Serial_Set_Parity(uint32_t serial_fd, int32_t databits, int32_t stopbits, int32_t parity) {
    struct termios option;

    if (tcgetattr(serial_fd, &option)) {
        Log_Err("%s-->%s() line %u: tcsetattr setting fail.\n", __FILE__, __func__, __LINE__);
        return false;
    }
    option.c_cflag &= ~CSIZE;
    option.c_oflag = 0;
    switch (databits) /*设置数据位数*/ {
        case 7: option.c_cflag |= CS7; break;
        case 8: option.c_cflag |= CS8; break;
        default:
            Log_Err("%s-->%s() line %u: databits %d is unsupport.\n", __FILE__, __func__, __LINE__, databits);
            return false;
    }
    switch (parity) {
        case 'n':
        case 'N':
            option.c_cflag &= ~PARENB; /* Clear parity enable */
            option.c_iflag &= ~INPCK;  /* Enable parity checking */
            break;
        case 'o':
        case 'O':
            option.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
            option.c_iflag |= INPCK;             /* Disnable parity checking */
            break;
        case 'e':
        case 'E':
            option.c_cflag |= PARENB;  /* Enable parity */
            option.c_cflag &= ~PARODD; /* 转换为偶效验*/
            option.c_iflag |= INPCK;   /* Disnable parity checking */
            break;
        case 'S':
        case 's': /*as no parity*/
            option.c_cflag &= ~PARENB;
            option.c_cflag &= ~CSTOPB;
            break;
        default:
            Log_Err("%s-->%s() line %u: parity '%c' is unsupport.\n", __FILE__, __func__, __LINE__, parity);
            return false;
    }

    switch (stopbits) {
        case 1: option.c_cflag &= ~CSTOPB; break;
        case 2: option.c_cflag |= CSTOPB; break;
        default:
            Log_Err("%s-->%s() line %u: stopbits %d is unsupport.\n", __FILE__, __func__, __LINE__, stopbits);
            return false;
    }
    /* Set input parity option */
    if (parity != 'n') option.c_iflag |= INPCK;

    option.c_cc[VTIME] = 150;  // 15 seconds
    option.c_cc[VMIN]  = 0;

    option.c_lflag &= ~(ECHO | ICANON);

    tcflush(serial_fd, TCIFLUSH); /* Update the option and do it NOW */
    if (tcsetattr(serial_fd, TCSANOW, &option) != 0) {
        Log_Err("%s-->%s() line %u: tcsetattr setting fail.\n", __FILE__, __func__, __LINE__);
        return false;
    }
    return true;
}

void Serial_Close(int32_t serial_fd) { close(serial_fd); }

void Serial_Clear(int32_t serial_fd) { tcflush(serial_fd, TCIOFLUSH); }

int32_t Serial_Open(const uint8_t* dev, uint32_t baudrate, uint32_t databit, uint32_t stopbit, uint32_t parity) {
    ASSERT(dev != NULL);
    uint32_t       speed;
    struct termios option;
    uint32_t       serial_fd = open(dev, O_RDWR);
    if (serial_fd < 0) {
        Log_Err("%s-->%s() line %u: open serial %s fail.\n", __FILE__, __func__, __LINE__, dev);
        return -1;
    }
    Serial_Set_Speed(serial_fd, baudrate);
    if (!Serial_Set_Parity(serial_fd, 8, 1, 'N')) {
        close(serial_fd);
        return -1;
    }
    return serial_fd;
}

int32_t Serial_Read(int32_t serial_fd, uint8_t* buffer, size_t size) {
    int32_t ret = read(serial_fd, buffer, size);
    if (-1 == ret) {
        Log_Err("%s-->%s() line %u: read serial fail, %s.\n", __FILE__, __func__, __LINE__, strerror(errno));
    }
    return ret;
}

int32_t Serial_Write(int32_t serial_fd, uint8_t* data, size_t size) {
    int32_t ret = write(serial_fd, data, size);
    Log_Err("%s-->%s() line %u: write serial fail, %s.\n", __FILE__, __func__, __LINE__, strerror(errno));
    return ret;
}

int32_t Serial_Readline(int32_t serial_fd, char* buffer, size_t maxsize, uint32_t timeout_ms) {
    size_t len;

    while (timeout_ms) {
        timeout_ms--;
        if (read(serial_fd, buffer, 1) < 1) {
            usleep(1000);
            // printf("%s %d \n",__func__,__LINE__);
            continue;
        } else if (buffer[0] == '\n' || buffer[0] == '\r') {
            usleep(1000);
            //  printf("%s %d \n",__func__,__LINE__);
            continue;
        } else
            break;
    }

    len = 1;

    while (timeout_ms--) {
        if (len >= maxsize)
            break;
        else if (read(serial_fd, buffer + len, 1) < 1) {
            usleep(1000);
            //  printf("%s %d \n",__func__,__LINE__);
            continue;
        } else if (buffer[len] == '\n' || buffer[len] == '\r') {
            len++;
            break;
        } else if (isprint(buffer[len]) == false) {
            return 0;
        }
        len++;
    }
    buffer[len] = 0;

    return len;
}
