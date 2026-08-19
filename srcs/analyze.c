#include "ft_ping.h"

static void fill_rtt_stats(t_ping * data, double time) {
    if (time > data->stats.rtt_max)
        data->stats.rtt_max = time;
    if (data->stats.rtt_min == 0)
        data->stats.rtt_min = time;
    else {
        if (time < data->stats.rtt_min)
            data->stats.rtt_min = time;
    }
    data->stats.rtt_avg = 
        ((data->stats.rtt_avg * (data->stats.received - 1)) + time)
        / data->stats.received;
    data->stats.rtt_squared += time * time;
    return ;
}

static void fill_display(t_ping *data, struct iphdr *ip, struct icmphdr *icmp, ssize_t len) {
    data->display.len = len - ip->ihl * 4;
    inet_ntop(
        AF_INET,
        &ip->saddr,
        data->display.ip,
        sizeof(data->display.ip));
    data->display.sequence = ntohs(icmp->un.echo.sequence);
    data->display.ttl = ip->ttl;
    data->display.time = (data->receive_time.tv_sec - data->send_time.tv_sec)
                        * 1000.0
                        + (data->receive_time.tv_nsec - data->send_time.tv_nsec)
                        / 1000000.0;
    fill_rtt_stats(data, data->display.time);
    return ;
}

int analyzer(t_ping *data, const unsigned char *buf, ssize_t len) {
    struct iphdr    *ip_header;
    struct icmphdr  *icmp_header;
    
    if (len < (ssize_t)sizeof(struct iphdr))
        return (1);
    ip_header = (struct iphdr *)buf;
    if (ip_header->ihl < 5)
        return (1);
    if (len < (ssize_t)(ip_header->ihl * 4))
        return (1);
    if (ip_header->protocol != IPPROTO_ICMP)
        return (1);
    if (len < (ssize_t)(ip_header->ihl * 4 + sizeof(struct icmphdr)))
        return (1);
    icmp_header = (struct icmphdr *)(buf + ip_header->ihl * 4);
    if (icmp_header->type != ICMP_ECHOREPLY) {
        if (data->verbose)
            verbose(buf, ip_header, icmp_header, len);
        return (1);
    }
    if (icmp_header->code != 0) {
        if (data->verbose)
            verbose(buf, ip_header, icmp_header, len);
        return (1);
    }
    if (ntohs(icmp_header->un.echo.id) != data->packet_id)
        return (1);
    if (ntohs(icmp_header->un.echo.sequence) != data->sequence)
        return (1);
    data->sequence++;
    data->stats.received++;
    if (clock_gettime(CLOCK_MONOTONIC, &data->receive_time) == -1)
        return (-1);
    fill_display(data, ip_header, icmp_header, len);
    return (0);
}
