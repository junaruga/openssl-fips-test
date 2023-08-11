#include <stdio.h>
#include <stdlib.h>


#include <sys/types.h>
#include <sys/socket.h>

#include <err.h>
#include <netdb.h>
#include <openssl/err.h>
#include <openssl/ssl.h>


#include <openssl/opensslv.h>
#include <openssl/crypto.h>


int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;

/*
 * See LibreSSL <openbsd/src/regress/lib/libssl/interop/util.c> print_version
 * fuction after compiling it.
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
/*
 * The values used for the ruby/openssl `OpenSSL.OPENSSL_LIBRARY_VERSION`.
 * See <https://github.com/ruby/openssl/blob/db633c52f7b364ded8185b661fb557e9db2f6383/ext/openssl/ossl.c#L1144-L1148>.
 */
#ifdef OPENSSL_VERSION
    printf("OpenSSL_version(OPENSSL_VERSION): %s\n",
        OpenSSL_version(OPENSSL_VERSION));
#endif
#ifdef SSLEAY_VERSION
    printf("SSLeay_version(SSLEAY_VERSION): %s\n",
        SSLeay_version(SSLEAY_VERSION));
#endif
    exit(status);
}
