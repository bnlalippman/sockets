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

    struct sockaddr_in sa;
    const char *ip = argv[1];  // Get the IP address from the command-line argument

    // Convert IP string to binary form
    // inet_pton() returns -1 on error, or 0 if the address is messed up
    if (inet_pton(AF_INET, ip, &(sa.sin_addr)) <= 0) {
        perror("inet_pton");
        return 1;
    }

    // Print the original IP address and its binary representation
    printf("Original IP: %s\n", ip);
    printf("Binary representation: %x\n", sa.sin_addr.s_addr); // s_addr is the 32-bit IP

    return 0;
}
