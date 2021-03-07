#include "sys_log.h"

int main(int argc, char* argv[]) {
    Log_Degug("this message is debug\n");
    Log_Warning("this message is warning\n");
    Log_Err("this message is error\n");
    Log_Emerg("this message is emerg\n");
    return 0;
}
