#include "ft_ping.h"

int analyzer(t_ping *data, const unsigned char *buf, ssize_t len) {
    struct iphdr    *ip_header;
    
    if (len < sizeof(struct iphdr))
        return (1);
    ip_header = (struct iphdr *)buf;
    if (len < ip_header->ihl * 4)
        return (1);
    return (0);
}