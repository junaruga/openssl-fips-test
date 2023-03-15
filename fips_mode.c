#include <stdio.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{
    OSSL_LIB_CTX *libctx = NULL;
    int status = EXIT_SUCCESS;
    int fips_enabled = 0;

    libctx = OSSL_LIB_CTX_new();
    fips_enabled = EVP_default_properties_is_fips_enabled(libctx);
    OSSL_LIB_CTX_free(libctx);
    printf("FIPS mode: %d\n", fips_enabled);
    exit(status);
}
