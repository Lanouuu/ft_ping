#include "ft_ping.h"

ssize_t sender(t_ping *data) {
    ssize_t ret;
    
    ret = 0;
    errno = 0;
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
    return (0);
}