# openssl-test

[![CI](https://github.com/junaruga/openssl-test/actions/workflows/test.yml/badge.svg)](https://github.com/junaruga/openssl-test/actions/workflows/test.yml)

This repository is to test OpenSSL API especially the FIPS mode related APIs.

## How to use

```
$ make

$ ./fips_mode
FIPS mode provider available: 0
FIPS mode enabled: 0

$ ./fips_mode_set
FIPS mode: 0
FIPS mode on.
FIPS mode: 1
FIPS mode on 2nd time.
FIPS mode: 1
FIPS mode off.
FIPS mode: 0
FIPS mode off 2nd time.
FIPS mode: 0
```
