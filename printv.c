#include <stdio.h>
#include <stdlib.h>

#include <openssl/opensslv.h>

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;

/*
   See LibreSSL <openbsd/src/regress/lib/libssl/interop/util.c> print_version
   fuction after compiling it.
*/
#ifdef OPENSSL_VERSION_NUMBER
    printf("OPENSSL_VERSION_NUMBER: %#08lx\n", OPENSSL_VERSION_NUMBER);
#endif
#ifdef OPENSSL_VERSION_TEXT
    printf("OPENSSL_VERSION_TEXT: %s\n", OPENSSL_VERSION_TEXT);
#endif
#ifdef LIBRESSL_VERSION_NUMBER
    printf("LIBRESSL_VERSION_NUMBER: %#08lx\n", LIBRESSL_VERSION_NUMBER);
#endif
#ifdef LIBRESSL_VERSION_TEXT
    printf("LIBRESSL_VERSION_TEXT: %s\n", LIBRESSL_VERSION_TEXT);
#endif
    exit(status);
}
