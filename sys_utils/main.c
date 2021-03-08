#include "sys_utils.h"

int main(int argc, const char* argv[]) {
    // uint8_t temp[1024];
    // Run_Shell_Read("ddddddd -a", temp);

    // printf("%s\n", temp);
    char* temp_path;
    temp_path = Get_Cur_Path();
    if (temp_path) { printf("the path is %s\n", temp_path); }

    // free(temp_path);
    return 0;
}
