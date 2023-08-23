#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/trace.h>

int main(int argc, char *argv[])
{
    int status = EXIT_SUCCESS;
    BIO *trace_trace_bio = NULL;
    BIO *trace_decoder_bio = NULL;
    int trace_trace_enabled = 0;
    int trace_decoder_enabled = 0;

    /*
     * Traces the OpenSSL trace API itself by setting the category
     * OSSL_TRACE_CATEGORY_TRACE. See `man 3 OSSL_trace_set_channel`.
     */
    trace_trace_bio = BIO_new_fp(stderr, BIO_NOCLOSE | BIO_FP_TEXT);
    OSSL_trace_set_channel(OSSL_TRACE_CATEGORY_TRACE, trace_trace_bio);
    OSSL_trace_set_prefix(OSSL_TRACE_CATEGORY_TRACE, "BEGIN TRACE TRACE");
    OSSL_trace_set_suffix(OSSL_TRACE_CATEGORY_TRACE, "END TRACE TRACE");

    trace_trace_enabled = OSSL_trace_enabled(OSSL_TRACE_CATEGORY_TRACE);
    printf("TRACE - Trace enabled: %d\n", (trace_trace_enabled) ? 1 : 0);

    /*
     * Traces decoder operations by setting the category
     * OSSL_TRACE_CATEGORY_DECODER.
     */
    trace_decoder_bio = BIO_new_fp(stderr, BIO_NOCLOSE | BIO_FP_TEXT);
    OSSL_trace_set_channel(OSSL_TRACE_CATEGORY_DECODER, trace_decoder_bio);
    OSSL_trace_set_prefix(OSSL_TRACE_CATEGORY_DECODER, "BEGIN DECODER TRACE");
    OSSL_trace_set_suffix(OSSL_TRACE_CATEGORY_DECODER, "END DECODER TRACE");

    trace_decoder_enabled = OSSL_trace_enabled(OSSL_TRACE_CATEGORY_DECODER);
    printf("DECODER - Trace enabled: %d\n", (trace_decoder_enabled) ? 1 : 0);

    return status;
}
