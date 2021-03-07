#include "sys_utils.h"

int main(int argc, const char* argv[]) {
    uint8_t temp[1024];
    Run_Shell_Read("ddddddd -a", temp);
    printf("%s\n", temp);

    return 0;
}
