#include "ft_ping.h"

int init_socket(t_ping *data) {
    errno = 0;
    data->sockfd= socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (data->sockfd == -1)
        return (dispatch_err(SOCK_ERR, NULL, errno));
    return (0);
}
