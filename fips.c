#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/provider.h>

static int print_provider(OSSL_PROVIDER *prov, void *unused)
{
    printf("  %s\n", OSSL_PROVIDER_get0_name(prov));
    return 1;
}

static int count_provider(OSSL_PROVIDER *prov, void *cbdata)
{
    int *num_p = (int *)cbdata;
    (*num_p)++;
}

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;
    int fips_enabled = 0;

    printf("Loaded providers:\n");
    OSSL_PROVIDER_do_all(NULL, &print_provider, NULL);

    /* Count providers */
    int provider_num = 0;
    OSSL_PROVIDER_do_all(NULL, &count_provider, (void*)&provider_num);
    printf("Loaded provider number: %d\n", provider_num);

    fips_enabled = EVP_default_properties_is_fips_enabled(NULL);
    printf("FIPS enabled: %s\n", (fips_enabled) ? "yes" : "no");

    return status;
}
