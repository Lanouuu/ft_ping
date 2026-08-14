#include "ft_ping.h"

void    init_data(t_ping *data) {
    data->verbose = 0;
    data->help = 0;
    data->str_count = NULL;
    data->count = 0;
    data->hostname = NULL;
    memset(&data->addr, 0, sizeof(data->addr));
    data->sockfd = -1;
    data->packet_id = (uint16_t)getpid();
    data->sequence = 1;
    memset(&data->display, 0, sizeof(data->display));
    return ;
}