/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printmask.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wayden <wayden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:00:59 by wayden            #+#    #+#             */
/*   Updated: 2024/02/06 20:07:10 by wayden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t parseIPAddress(char *ip_str) {
    uint32_t ip = 0;
    char *token = strtok(ip_str, ".");
    int i = 24;
    while (token != NULL) {
        ip |= (atoi(token) << i);
        i -= 8;
        token = strtok(NULL, ".");
    }
    return ip;
}

uint32_t parseSubnetMask(char *mask_str) {
    if (mask_str[0] == '/') {
        int subnet_bits = atoi(mask_str + 1);
        uint32_t mask = 0xFFFFFFFF << (32 - subnet_bits);
        return mask;
    } else {
        return parseIPAddress(mask_str);
    }
}

void printIPAddress(uint32_t ip) {
    printf("%d.%d.%d.%d\n", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <IP address> <Subnet mask>\n", argv[0]);
        return 1;
    }

    uint32_t ip_address = parseIPAddress(argv[1]);
    uint32_t subnet_mask = parseSubnetMask(argv[2]);

    uint32_t network_address = ip_address & subnet_mask;
    uint32_t broadcast_address = network_address | ~subnet_mask;
    uint32_t first_address = network_address + 1;
    uint32_t last_address = broadcast_address - 1;

    printf("Adresse réseau: ");
    printIPAddress(network_address);
    printf("Adresse de diffusion: ");
    printIPAddress(broadcast_address);
    printf("Première adresse disponible: ");
    printIPAddress(first_address);
    printf("Dernière adresse disponible: ");
    printIPAddress(last_address);

    return 0;
}
