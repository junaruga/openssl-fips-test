# openssl-test

[![CI](https://github.com/junaruga/openssl-test/actions/workflows/test.yml/badge.svg)](https://github.com/junaruga/openssl-test/actions/workflows/test.yml)

This repository is to test OpenSSL API especially the FIPS mode related APIs.

## How to use

### Prepare OpenSSL

The `enable-fips` option is to install the FIPS mododule.

```
$ git clone https://github.com/openssl/openssl.git

$ cd openssl

$ git checkout openssl-3.0.8

$ ./Configure \
  --prefix=$HOME/.local/openssl-3.0.8-fips-debug-trace \
  shared \
  enable-fips \
  enable-trace \
  -O0 -g3 -ggdb3 -gdwarf-5

$ make -j$(nproc)

$ make install

$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.8-fips-debug-trace/lib64/ \
  $HOME/.local/openssl-3.0.8-fips-debug-trace/bin/openssl version
OpenSSL 3.0.8 7 Feb 2023 (Library: OpenSSL 3.0.8 7 Feb 2023)
```

Set the following file.

```
$ cat $HOME/.local/openssl-3.0.8-fips-debug-trace/ssl/openssl_fips.cnf
config_diagnostics = 1
openssl_conf = openssl_init

.include /home/jaruga/.local/openssl-3.0.8-fips-debug-trace/ssl/fipsmodule.cnf
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

### Directly with gcc

Compile the program to test if FIPS mode is enabled or not.

```
$ gcc \
  -I /home/jaruga/.local/openssl-3.0.8-fips-debug-trace/include \
  -L /home/jaruga/.local/openssl-3.0.8-fips-debug-trace/lib64 \
  -lcrypto \
  -o fips_mode \
  fips_mode.c
```

Run the program. The FIPS mode is off with the command below.

```
$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.8-fips-debug-trace/lib64/ \
  ./fips_mode
Loaded providers:
  default
FIPS mode enabled: 0
```

The FIPS mode is on with the command below.

```
$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.8-fips-debug-trace/lib64/ \
  OPENSSL_CONF=/home/jaruga/.local/openssl-3.0.8-fips-debug-trace/ssl/openssl_fips.cnf \
  ./fips_mode
Loaded providers:
  fips
  base
FIPS mode enabled: 1
```

### With make

Compile.

```
$ make \
  INCFLAGS="-I /home/jaruga/.local/openssl-3.0.8-fips-debug-trace/include" \
  LDFLAGS="-L /home/jaruga/.local/openssl-3.0.8-fips-debug-trace/lib64"
```

Run the commands.

```
$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.8-fips-debug-trace/lib64/ \
  OPENSSL_CONF=/home/jaruga/.local/openssl-3.0.8-fips-debug-trace/ssl/openssl_fips.cnf \
  ./fips_mode
...

$ LD_LIBRARY_PATH=$HOME/.local/openssl-3.0.8-fips-debug-trace/lib64/ \
  OPENSSL_CONF=/home/jaruga/.local/openssl-3.0.8-fips-debug-trace/ssl/openssl_fips.cnf \
  ./fips_mode_set
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
