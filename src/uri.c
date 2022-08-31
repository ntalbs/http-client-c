#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uri.h"

static bool starts_with(const char* str, const char* prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

static void scheme(Uri* uri, const char* uri_str) {
    if (starts_with(uri_str, "https://")) {
        uri->scheme = HTTPS;
    } else if (starts_with(uri_str, "http://")) {
        uri->scheme=HTTP;
    } else {
        fprintf(stderr, "Not supported scheme in the URI: %s\n", uri_str);
        exit(EXIT_FAILURE);
    }
}

static char* hostname_and_port(Uri* uri, const char* uri_str) {
    char* start = strstr(uri_str, "//");
    char* end = strpbrk(start + 2, "/?");

    if (end == NULL) {
        end = start + strlen(start);
    }

    char authority[128] = {0};
    strncpy(authority, start+2, end - start - 2);

    char* hostname = strtok(authority, ":");
    strncpy(uri->hostname, hostname, sizeof(uri->hostname));

    char* port = strtok(NULL, ":");
    if (port==NULL) {
        strncpy(uri->port, (uri->scheme==HTTP) ? "80" : "443", sizeof(uri->port));
    } else {
        strncpy(uri->port, port, sizeof(uri->port));
    }

    return end;
}

void debugUri(Uri* uri) {
    printf(">>> scheme: %s\n", (uri->scheme == HTTPS) ? "https" : "http");
    printf(">>> hostname: %s\n", uri->hostname);
    printf(">>> port: %s\n", uri->port);
    printf(">>> path&query: %s\n", uri->path_query_fragment);
}

Uri parseUri(const char* uri_str) {
    Uri uri;

    scheme(&uri, uri_str);
    char* path_query_fragment = hostname_and_port(&uri, uri_str);

    if (path_query_fragment==NULL || path_query_fragment[0] == '\0') {
        strncpy(uri.path_query_fragment, "/", sizeof(uri.path_query_fragment));
    } else {
        strncpy(uri.path_query_fragment, path_query_fragment, sizeof(uri.path_query_fragment));
    }

    return uri;
}
