#include "ft_ping.h"

void    display_packet(t_display *display) {
    fprintf(
        stdout,
        "%ld bytes from %s: icmp_seq=%u ttl=%u time=%.2f ms\n",
        display->len,
        display->ip,
        display->sequence,
        display->ttl,
        display->time
    );
    return ;
}
