#include "ft_ping.h"

ssize_t sender(t_ping *data) {
    ssize_t ret;
    
    ret = 0;
    errno = 0;
    if (clock_gettime(CLOCK_MONOTONIC, &data->send_time) == -1)
        return (dispatch_err(CLOCK_ERR, NULL, errno));
    ret = sendto(
                data->sockfd,
                data->packet,
                sizeof(data->packet),
                0,
                (struct sockaddr *)&data->addr,
                sizeof(data->addr)
    );
    if (ret == -1)
        return (dispatch_err(SEND_ERR, NULL, errno));
    if (clock_gettime(CLOCK_MONOTONIC, &data->deadline) == -1)
        return (dispatch_err(CLOCK_ERR, NULL, errno));
    data->deadline.tv_sec += 1;
    data->stats.sended++;
    return (0);
}
