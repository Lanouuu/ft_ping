#include "ft_ping.h"

uint16_t    checksum(const unsigned char *packet, size_t size) {
    uint16_t    paire;
    uint32_t    sum;

    sum = 0;
    for (int i = 0; i < size; i += 2) {
        paire = (packet[i] << 8) | packet[i + 1];
        sum += paire;
        // check si sum > FFFF ou 65535
    }
    // check si sum > FFFF ou 65535
}