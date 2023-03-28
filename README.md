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

## Note

The `FIPS mode provider available: 1` happens when the config file `fipsmodule.cnf` has the line `activate = 1`. You can comment out this line to see the `FIPS mode provider available: 0`.

```
$ cat /path/to/fipsmodule.cnf
...
[fips_sect]
activate = 1
...
```

The `FIPS mode enabled: 1` happens when the openssl config file `openssl.cnf` has the `default_properties = fips=yes`. You can comment out to see the `FIPS mode enabled: 0`

```
$ cat /path/to/openssl.cnf
...
[algorithm_sect]
default_properties = fips=yes
```

You can test own OpenSSL built from the source with FIPS option with the FIPS config file. Below is the example.

```
$ cat /home/jaruga/.local/openssl-3.0.8-fips/ssl/openssl_fips.cnf
config_diagnostics = 1
openssl_conf = openssl_init

.include /home/jaruga/.local/openssl-3.0.8-fips/ssl/fipsmodule.cnf
#.include ./fipsmodule.cnf

[openssl_init]
providers = provider_sect
alg_section = algorithm_sect

[provider_sect]
fips = fips_sect
base = base_sect

[base_sect]
activate = 1

[algorithm_sect]
default_properties = fips=yes
```

```
$ LD_LIBRARY_PATH=/home/jaruga/.local/openssl-3.0.8-fips/lib/ \
  OPENSSL_CONF=/home/jaruga/.local/openssl-3.0.8-fips/ssl/openssl_fips.cnf \
  ~/git/openssl-test/fips_mode
FIPS mode provider available: 1
FIPS mode enabled: 1
```
