#include "ft_ping.h"

static void display_verbose(char *ip, uint8_t type, uint8_t code,
                            uint16_t sequence) {
    fprintf(stderr, "From %s, icmp_seq=%u ", ip, sequence);
    if (type == ICMP_DEST_UNREACH) {
        fprintf(stderr, "Destination Unreachable");
        if (code == 0)
            fprintf(stderr, " (Network Unreachable)");
        else if (code == 1)
            fprintf(stderr, " (Host Unreachable)");
        else if (code == 3)
            fprintf(stderr, " (Port Unreachable)");
        fprintf(stderr, "\n");
    }
    else if (type == ICMP_TIME_EXCEEDED)
        fprintf(stderr, "ttl exceeded\n");
    else
        fprintf(stderr, "ICMP type=%u, code=%u\n", type, code);
    return ;
}

void    verbose(const unsigned char *buf, struct iphdr *ip_hdr,
                struct icmphdr *icmp_hdr, ssize_t len) {
    struct iphdr   *packet_ip;
    struct icmphdr *packet_icmp;
    char            ip[INET_ADDRSTRLEN];
    uint16_t        sequence;
    uint8_t         type;
    uint8_t         code;
    size_t          offset;
    
    offset = ip_hdr->ihl * 4 + sizeof(struct icmphdr);
    if (len < (ssize_t)(offset + sizeof(struct iphdr)))
        return ;
    packet_ip = (struct iphdr *)(buf + offset);
    if (packet_ip->ihl < 5)
        return ;
    if (packet_ip->protocol != IPPROTO_ICMP)
        return ;
    if (len < (ssize_t)(ip_hdr->ihl * 4 + sizeof(struct icmphdr)
        + packet_ip->ihl * 4 + sizeof(struct icmphdr)))
        return ;
    packet_icmp = (struct icmphdr *)((unsigned char *)packet_ip
                    + packet_ip->ihl * 4);
    sequence = ntohs(packet_icmp->un.echo.sequence);
    inet_ntop(AF_INET, &ip_hdr->saddr, ip, sizeof(ip));
    type = icmp_hdr->type;
    code = icmp_hdr->code;
    display_verbose(ip, type, code, sequence);
    return ;
}
