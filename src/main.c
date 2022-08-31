#include <stdio.h>
#include <stdlib.h>

#include "uri.h"
#include "http.h"
#include "ssl.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: cget <url>\n");
        exit(EXIT_FAILURE);
    }

    Uri uri = parseUri(argv[1]);    

    switch (uri.scheme) {
        case HTTP:
            httpGet(&uri);
            break;
        case HTTPS:
            sslGet(&uri);
            break;
    }
}
