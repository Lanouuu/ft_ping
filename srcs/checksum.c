#include "ft_ping.h"

uint16_t    checksum(const unsigned char *packet, size_t size) {
    uint16_t    paire;
    uint32_t    sum;
    uint16_t    checksum;

    sum = 0;
    for (size_t i = 0; i < size; i += 2) {
        paire = (packet[i] << 8) | packet[i + 1];
        sum += paire;
        while (sum > 0xFFFF)
            sum = (sum & 0xFFFF) + (sum >> 16);
    }
    while (sum > 0xFFFF)
            sum = (sum & 0xFFFF) + (sum >> 16);
    checksum = ~sum;
    return (htons(checksum));
}
