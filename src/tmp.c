#include "log.h"

int main(int argc, char **argv)
{
    libco_log_start(1, 2);
    libco_log_out(0, "%s", argv[1]);
    libco_log_out(1, "%s", argv[2]);
    libco_log_out(2, "%s", argv[2]);
    libco_log_end(1);
    return 0;
}
