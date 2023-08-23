#include <stdio.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;
    int fips_enabled = 0;

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS: %d\n", fips_enabled);

    printf("FIPS on.\n");
    if (!EVP_default_properties_enable_fips(NULL, 1)) {
        status = EXIT_FAILURE;
        goto err;
    }

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS: %d\n", fips_enabled);

    printf("FIPS on 2nd time.\n");
    if (!EVP_default_properties_enable_fips(NULL, 1)) {
        status = EXIT_FAILURE;
        goto err;
    }

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS: %d\n", fips_enabled);

    printf("FIPS off.\n");
    if (!EVP_default_properties_enable_fips(NULL, 0)) {
        status = EXIT_FAILURE;
        goto err;
    }

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS: %d\n", fips_enabled);

    printf("FIPS off 2nd time.\n");
    if (!EVP_default_properties_enable_fips(NULL, 0)) {
        status = EXIT_FAILURE;
        goto err;
    }

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS: %d\n", fips_enabled);
err:
    return status;
}
