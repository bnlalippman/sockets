/*
** showip.c -- show IP addresses for a host given on the command line
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    // struct addrinfo {
    //   int              ai_flags;
    //   int              ai_family;     // AF_INET, AF_INET6, etc.
    //   int              ai_socktype;   // SOCK_STREAM, SOCK_DGRAM, etc.
    //   int              ai_protocol;   // Usually 0
    //   size_t           ai_addrlen;
    //   struct sockaddr *ai_addr;       // Pointer to the address info
    //   char            *ai_canonname;
    //   struct addrinfo *ai_next;       // Pointer to the next result
    // };
    
    // hints = a struct addrinfo (a normal variable, not a pointer)
    // *res = a pointer that points to the start of the linked list
    // *p = another pointer that will loop through linked list
    struct addrinfo hints, *res, *p;
    
    // setup variable that will be used to check if getaddrinfo()
    // function call was successful or not. Any return code that
    // is not 0 will return an error to the console
    int status;
    
    // INET6_ADDRSTRLEN is a constant from #include <arpa/inet.h>
    char ipstr[INET6_ADDRSTRLEN];

    // If the number of arguments is not 2, exit program
    if (argc != 2) {
        fprintf(stderr,"usage: showip hostname\n");
        return 1;
    }

    // Set all the bytes in memory occupied by hints to 0
    memset(&hints, 0, sizeof hints);

    // Tells addrinfo struct that address can be IPv4 or IPv6
    hints.ai_family = AF_UNSPEC;
    
    // Tells addrinfo struct that we want to deal with TCP
    hints.ai_socktype = SOCK_STREAM;

    // If addrinfo() call does not return 0, something went wrong
    // and we should exit this program.
    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }
 
    printf("IPs for %s:\n\n", argv[1]);
    
    // for (part 1; part 2; part 3; { code }
    // 
    // part 1 = executed once before code
    // p = res means we start with first node in linked list
    // 
    // part 2 = defines condition for executing code
    // p != NULL means that the element from addrinfo() must
    // not be empty
    // 
    // part 3 = executed every time after code is run inside loop
    // p->ai_next is a pointer to linked list which moves us to next
    // node in the list
    for(p = res;p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        // If the pointer points to an ai_family
        // that is an IPv4 (AF_INET)
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        // If the pointer points to an ai_family
        // that is IPv6 (AF_INET6)
        else if (p->ai_family == AF_INET6) { 
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        else {
            fprintf(stderr, "Unknown ai_family: %d\n", p->ai_family);
            continue;
        }

        // Convert the IP to a string and print it
        // ntop = network to presentation or bytes to ip
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);
    }
    
    // getaddrinfo() dynamically stores memory for
    // its results. The OS gives this program heap memory
    // to store our addrinfo structs. For this tiny c 
    // program it's probably not necessary to free the memory
    // on each loop, but in a larger application this is crucial.
    freeaddrinfo(res); 

    return 0;
}
