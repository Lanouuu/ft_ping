#include "ft_ping.h"

void    free_ping(t_ping *data) {
    if (data->sockfd != -1)
        close(data->sockfd);
    return ;
}
