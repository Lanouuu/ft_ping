#include "ft_ping.h"

void make_packet(t_ping *data) {
    struct icmphdr  *header;
    
    memset(data->packet, 0, sizeof(data->packet));
    header = (struct icmphdr *)data->packet;
    header->type = 8;
    header->code = 0;
    header->un.echo.id = htons(data->packet_id);
    header->un.echo.sequence = htons(data->sequence);
    data->sequence++;
    for (int i = 0; i < 56; i++)
        data->packet[sizeof(struct icmphdr) + i] = i;
    header->checksum = checksum(data->packet, sizeof(data->packet));
    return ;
}