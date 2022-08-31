#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "sock.h"
#include "uri.h"
#include "http.h"

void makeRequest(char* buf, Uri* uri, size_t num) {
    snprintf(
        buf, num,
        "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "User-Agent: cget\r\n"
        "Connection: close\r\n"
        "\r\n",
        uri->path_query_fragment,
        uri->hostname
    );
}

void httpGet(Uri* uri) {
    int sock = conn(uri);
    char buf[BUF_SIZE] = {0};

    makeRequest(buf, uri, sizeof(buf));

    if (send(sock, buf, strlen(buf), 0) == -1) {
        perror("Error while sending request");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int nread = recv(sock, buf, sizeof(buf) - 1, 0);
        if (nread == -1) {
            perror("Error while receiving data");
            exit(EXIT_FAILURE);
        } else if (nread == 0) {
            break;
        }

        buf[nread] = '\0';
        printf("%s", buf);
    }
    printf("\n");

    close(sock);
}
