#include "ft_ping.h"

ssize_t receiver(t_ping *data) {
    ssize_t             len;
    unsigned char       buf[IP_MAXPACKET];
    struct sockaddr_in  rec_addr;
    socklen_t           addr_len;
    int                 analyze_ret;

    len = 0;
    errno = 0;
    addr_len = sizeof(rec_addr);
    len = recvfrom(
                    data->sockfd,
                    buf,
                    sizeof(buf),
                    0,
                    (struct sockaddr *)&rec_addr,
                    &addr_len
    );
    if (len == -1)
        return (dispatch_err(REC_ERR, NULL, errno));
    analyze_ret = analyzer(data, buf, len);
    if (analyze_ret == -1)
        return (dispatch_err(CLOCK_ERR, NULL, errno));
    else if (analyze_ret == 1)
        return (2);
    else if (analyze_ret == 0)
        display_packet(&data->display);
    return (0);
}
