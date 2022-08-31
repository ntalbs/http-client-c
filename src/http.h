#ifndef cget_http_h
#define cget_http_h

#include "uri.h"

void makeRequest(char* buf, Uri* uri, size_t num);
void httpGet(Uri* uri);

#endif