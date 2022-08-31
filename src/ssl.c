#include <stdbool.h>
#include <unistd.h>
#include <openssl/ssl.h>

#include "sock.h"
#include "uri.h"
#include "http.h"
#include "ssl.h"

void sslGet(Uri* uri) {
    int sock = conn(uri);

    SSLeay_add_ssl_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *client_method = TLS_client_method();
    SSL_CTX *ctx = SSL_CTX_new(client_method);

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) != 1) {
        perror("SSL connection failed");
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE] = {0};
    makeRequest(buf, uri, sizeof(buf));

    if (SSL_write(ssl, buf, strlen(buf)) <= 0) {
        perror("SSL write failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int nread = SSL_read(ssl, buf, sizeof(buf) - 1);
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

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sock);
}
