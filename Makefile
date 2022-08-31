CC = /usr/bin/gcc
CFLAG = -g

LIBFARM = $(shell brazil-path build.libfarm)
OPENSSL_SSL_LIB = ${LIBFARM}/lib/libssl.so.3
OPENSSL_CRYPTO_LIB=${LIBFARM}/lib/libcrypto.so.3

OPTION =  -g -v \
	-I ${LIBFARM}/include \
	-L ${LIBFARM}/lib \
	-D OPENSSL_SSL_LIBRARY=${OPENSSL_SSL_LIB} \
	-D OPENSSL_CRYPTO_LIBRARY=${OPENSSL_CRYPTO_LIB} \
	-lssl -lcrypto \
	${CFLAG}

BUILD_DIR := build

release: default

default: cget

cget: init
	$(CC) ${OPTION} src/*.c -o ${BUILD_DIR}/cget

init:
	@mkdir -p ${BUILD_DIR}

clean:
	@rm -rf ${BUILD_DIR}
	@rm -f .attach_pid*
