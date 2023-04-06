#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/provider.h>

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;
    int base_available = 0;
    int fips_available = 0;
    int fips_enabled = 0;

    base_available = OSSL_PROVIDER_available(NULL, "base");
    printf("Base provider available: %d\n", base_available);

    fips_available = OSSL_PROVIDER_available(NULL, "fips");
    printf("FIPS provider available: %d\n", fips_available);

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS mode enabled: %d\n", fips_enabled);

    exit(status);
}
