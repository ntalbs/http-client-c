#include <memory.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "uri.h"

int conn(Uri* uri) {
    struct addrinfo hints = {0};
    struct addrinfo *servinfo;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(uri->hostname, uri->port, &hints, &servinfo) != 0) {
        perror("Couldn't get addr info");
        exit(EXIT_FAILURE);
    }

    int sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (sock == -1) {
        perror("Socker error");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
        perror("Couldn't connect to the server");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(servinfo);
    
    return sock;
}
