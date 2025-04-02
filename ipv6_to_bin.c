#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

// argc is the argument count
// argv contains the argument we want to process 
int main(int argc, char *argv[]) {
    // Ensure the user has provided an IP address as an argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IP_address>\n", argv[0]);
        return 1;
    }

    struct sockaddr_in6 sa6;
    const char *ip = argv[1];  // Get the IP address from the command-line argument

    // Convert IP string to binary form
    // inet_pton() returns -1 on error, or 0 if the address is messed up
    if (inet_pton(AF_INET6, ip, &(sa6.sin6_addr)) <= 0) {
        perror("inet_pton");
        return 1;
    }

    // Print the original IP address and its binary representation
    printf("Original IP: %s\n", ip);

    // Print the binary representation (in hexadecimal)
    printf("Binary representation: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x", sa6.sin6_addr.s6_addr[i]);
        if (i < 15) {
            printf(":");
        }
    }
    printf("\n");

    return 0;
}
