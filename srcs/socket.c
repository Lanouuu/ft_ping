#include "ft_ping.h"

int init_socket(t_ping *data) {
    errno = 0;
    data->sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (data->sockfd == -1)
        return (dispatch_err(SOCK_ERR, NULL, errno));
    if (data->verbose)
    {
        fprintf(
            stderr,
            "ping: sock4.fd: %d (socktype: SOCK_RAW), "
            "hints.ai_family: AF_INET\n\n",
            data->sockfd
        );
        fprintf(
            stderr,
            "ai->ai_family: AF_INET, ai->ai_canonname: '%s'\n",
            data->hostname
        );
    }
    return (0);
}
