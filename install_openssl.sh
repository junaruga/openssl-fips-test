#!/bin/bash

set -euxo pipefail

# OPENSSL_VERSION=3.0.9
if ${#} -lt 1; then
  echo "Argument version is required." 2>&1
fi
OPENSSL_VERSION="${1}"

./Configure \
  --prefix="${HOME}/.local/openssl-${OPENSSL_VERSION}-fips-debug" \
  --libdir=lib \
  shared \
  enable-fips \
  enable-trace \
  -O0 -g3 -ggdb3 -gdwarf-5
make -j"$(nproc)"
make install

LD_LIBRARY_PATH="${HOME}/.local/openssl-${OPENSSL_VERSION}-fips-debug/lib/" \
  "${HOME}/.local/openssl-${OPENSSL_VERSION}-fips-debug/bin/openssl" version
