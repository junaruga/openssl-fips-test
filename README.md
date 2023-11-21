# openssl-test

[![CI](https://github.com/junaruga/openssl-test/actions/workflows/test.yml/badge.svg)](https://github.com/junaruga/openssl-test/actions/workflows/test.yml)

This repository is to test OpenSSL API especially the FIPS related APIs.

## How to use

For convinience, I use the `$OPENSSL_DIR` to describe the installed OpenSSL directory in this document.

```
$ OPENSSL_DIR="$HOME/.local/openssl-3.3.0-dev-fips-debug-1aa08644ec"
```

### Install OpenSSL

See [this document](https://github.com/ruby/openssl/blob/master/CONTRIBUTING.md#with-different-versions-of-openssl) to install OpenSSL with FIPS option.

### Compile the program "fips.c" to check the FIPS status

Compile the program to test if FIPS is enabled or not.

```
$ gcc \
  -I $OPENSSL_DIR/include \
  -L $OPENSSL_DIR/lib \
  -lcrypto \
  "-Wl,-rpath,$OPENSSL_DIR/lib" \
  -o fips \
  fips.c
```

Run the program. The FIPS is off with the command below.

```
$ ./fips
Loaded providers:
  default
Loaded provider number: 1
FIPS enabled: no
```

The FIPS is on with the command below.

```
$ OPENSSL_CONF=$OPENSSL_DIR/ssl/openssl_fips.cnf \
  ./fips
Loaded providers:
  fips
  base
Loaded provider number: 2
FIPS enabled: yes
```

### Compile with make

Compile.

```
$ make \
  INCFLAGS="-I $OPENSSL_DIR/include" \
  LDFLAGS="-L $OPENSSL_DIR/lib"
```

Run the commands.

```
$ OPENSSL_CONF=$OPENSSL_DIR/ssl/openssl_fips.cnf \
  ./fips
Loaded providers:
  fips
  base
Loaded provider number: 2
FIPS enabled: yes

$ OPENSSL_CONF=$OPENSSL_DIR/ssl/openssl_fips.cnf \
  ./fips_set
FIPS: 1
FIPS on.
FIPS: 1
FIPS on 2nd time.
FIPS: 1
FIPS off.
FIPS: 0
FIPS off 2nd time.
FIPS: 0
```
