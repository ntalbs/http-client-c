#ifndef cget_uri_h
#define cget_uri_h

typedef enum {
    HTTP,
    HTTPS
} Scheme;

typedef struct {
    Scheme scheme;
    char hostname[256];
    char port[6];
    char path_query_fragment[2048];
} Uri;

Uri parseUri(const char* uri_str);
void debugUri(Uri* uri);

#endif
