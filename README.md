# openssl-test

[![CI](https://github.com/junaruga/openssl-test/actions/workflows/test.yml/badge.svg)](https://github.com/junaruga/openssl-test/actions/workflows/test.yml)

This repository is to test OpenSSL API especially the FIPS related APIs.

## How to use

### Prepare OpenSSL

The `enable-fips` option is to install the FIPS mododule.

```
$ git clone https://github.com/openssl/openssl.git

$ cd openssl

$ git checkout openssl-3.0.9

$ ./Configure \
  --prefix=${HOME}/.local/openssl-3.0.9-fips-debug \
  --libdir=lib \
  shared \
  enable-fips \
  enable-trace \
  -O0 -g3 -ggdb3 -gdwarf-5

$ make -j$(nproc)

$ make install

$ LD_LIBRARY_PATH="${HOME}/.local/openssl-3.0.9-fips-debug/lib/" \
  "${HOME}/.local/openssl-3.0.9-fips-debug/bin/openssl" version
OpenSSL 3.0.9 30 May 2023 (Library: OpenSSL 3.0.9 30 May 2023)
```

Set the following file.

```
$ cat ~/.local/openssl-3.0.9-fips-debug/ssl/openssl_fips.cnf
config_diagnostics = 1
openssl_conf = openssl_init

# Need to set the absolute path.
# https://github.com/openssl/openssl/issues/17704
.include /home/jaruga/.local/openssl-3.0.9-fips-debug/ssl/fipsmodule.cnf

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

### Directly with gcc

Compile the program to test if FIPS is enabled or not.

```
$ gcc \
  -I /home/jaruga/.local/openssl-3.0.9-fips-debug/include \
  -L /home/jaruga/.local/openssl-3.0.9-fips-debug/lib \
  -lcrypto \
  -o fips \
  fips.c
```

Run the program. The FIPS is off with the command below.

```
$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.9-fips-debug/lib/ \
  ./fips
Loaded providers:
  default
FIPS enabled: no
```

The FIPS is on with the command below.

```
$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.9-fips-debug/lib/ \
  OPENSSL_CONF=/home/jaruga/.local/openssl-3.0.9-fips-debug/ssl/openssl_fips.cnf \
  ./fips
Loaded providers:
  fips
  base
FIPS enabled: yes
```

### With make

Compile.

```
$ make \
  INCFLAGS="-I /home/jaruga/.local/openssl-3.0.9-fips-debug-/include" \
  LDFLAGS="-L /home/jaruga/.local/openssl-3.0.9-fips-debug/lib"
```

Run the commands.

```
$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.9-fips-debug/lib/ \
  OPENSSL_CONF=/home/jaruga/.local/openssl-3.0.9-fips-debug/ssl/openssl_fips.cnf \
  ./fips
...

$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.9-fips-debug/lib/ \
  OPENSSL_CONF=/home/jaruga/.local/openssl-3.0.9-fips-debug/ssl/openssl_fips.cnf \
  ./fips_set
FIPS: 0
FIPS on.
FIPS: 1
FIPS on 2nd time.
FIPS: 1
FIPS off.
FIPS: 0
FIPS off 2nd time.
FIPS: 0
```

## Note

The `FIPS provider available: 1` happens when the config file `fipsmodule.cnf` has the line `activate = 1`. You can comment out this line to see the `FIPS provider available: 0`.

```
$ cat /path/to/fipsmodule.cnf
...
[fips_sect]
activate = 1
...
```

The `FIPS enabled: yes` happens when the openssl config file `openssl.cnf` has the `default_properties = fips=yes`. You can comment out to see the `FIPS mode enabled: no`

```
$ cat /path/to/openssl.cnf
...
[algorithm_sect]
default_properties = fips=yes
```
