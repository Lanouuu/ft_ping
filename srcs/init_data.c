#include "ft_ping.h"

void    init_data(t_ping *data) {
    memset(data, 0, sizeof(*data));
    data->sockfd = -1;
    data->packet_id = (uint16_t)getpid();
    data->sequence = 1;
    return ;
}