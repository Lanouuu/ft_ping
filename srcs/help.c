#include "ft_ping.h"

void    print_help(void) {
    fprintf(stdout,
        "usage:"
            "\n\tft_ping [OPTION] HOST\n\n");
    fprintf(stdout,
        "options:"
            "\n\t-v : verbose"
            "\n\t-? [no HOST, no OPTIONS] : display help"
            "\n\t-c COUNT : stop after sending COUNT packets\n");
    return ;
}
