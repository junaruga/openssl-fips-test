#include <stdio.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;
    int fips_enabled = 0;

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS mode: %d\n", fips_enabled);
    exit(status);
}
