#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/provider.h>

static int print_provider(OSSL_PROVIDER *prov, void *unused)
{
    printf("  %s\n", OSSL_PROVIDER_get0_name(prov));
    return 1;
}

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;
    int fips_enabled = 0;

    printf("Loaded providers:\n");
    OSSL_PROVIDER_do_all(NULL, &print_provider, NULL);

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS mode enabled: %d\n", fips_enabled);

    exit(status);
}
