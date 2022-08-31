# Simple Http Client
This is a simple HTTP client written in C, as part of onboarding tasks. It supports only `GET` method. Responses will be printed out to console including headers and body. It uses `openssl` to handle TLS.

## Build
`brazil-build` will create an executable named `cget` under `build` directory.


## Run
You need to set `LD_LIBRARY_PATH` before execute the binary.
```
$ export LD_LIBRARY_PATH=$(brazil-path build.libfarm)/lib
```

Now you can run:
```
$ ./build/cget https://example.com
```

```
HTTP/1.1 200 OK
Age: 586789
Cache-Control: max-age=604800
Content-Type: text/html; charset=UTF-8
Date: Thu, 01 Sep 2022 16:38:34 GMT
Etag: "3147526947+ident"
Expires: Thu, 08 Sep 2022 16:38:34 GMT
Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT
Server: ECS (nyb/1D11)
Vary: Accept-Encoding
X-Cache: HIT
Content-Length: 1256
Connection: close

<!doctype html>
<html>
<head>
    <title>Example Domain</title>
...
```
