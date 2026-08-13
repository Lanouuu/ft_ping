#include "ft_ping.h"

int dispatch_err(int e, char *s, int ret) {
    if (e == MISS_HOST_OP || e == BAD_OP || e == BAD_OPT || e == HELP_ERR) {
        if (e == MISS_HOST_OP)
            fprintf(stderr, "ft_ping: missing host operand\n\n");
        else if (e == BAD_OP)
            fprintf(stderr, "ft_ping: bad operands\n\n");
        else if (e == HELP_ERR)
            fprintf(stderr, "ft_ping: -?: invalid usage\n\n");
        else
            fprintf(stderr, "ft_ping: %s: unknown option\n\n", s);
        print_help();
    }
    if (e == INV_COUNT)
        fprintf(stderr, "ft_ping: -c: invalid count \n");
    if (e == GAI_ERR)
        fprintf(stderr, "ft_ping: %s: %s\n", s, gai_strerror(ret));
    if (e == SOCK_ERR)
        fprintf(stderr, "ft_ping: socket: %s\n", strerror(ret));
    if (e == SEND_ERR)
        fprintf(stderr, "ft_ping: sendto: %s\n", strerror(ret));
    if (e == REC_ERR)
        fprintf(stderr, "ft_ping: recvfrom: %s\n", strerror(ret));
    return (1);
}