#include "ft_ping.h"

ssize_t receiver(t_ping *data) {
    ssize_t             len;
    unsigned char       buf[IP_MAXPACKET];
    struct sockaddr_in  rec_addr;

    len = 0;
    errno = 0;
    len = recvfrom(
                    data->sockfd,
                    buf,
                    sizeof(buf),
                    0,
                    (struct sockaddr *)&rec_addr,
                    sizeof(rec_addr)
    );
    if (len == -1)
        return (dispatch_err(REC_ERR, NULL, errno));
    if (analyzer(data, buf, len) == 0)
        display_packet(data, buf, len);
    return (0);
}