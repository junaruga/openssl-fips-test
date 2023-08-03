#!/bin/bash

set -euxo pipefail

function print_version_str {
  local MAJOR
  local MINOR
  local PATCH
  local PRE_RELEASE_TAG
  local VERSION

  MAJOR="$(grep '^MAJOR=' VERSION.dat | cut -d '=' -f 2)"
  MINOR="$(grep '^MINOR=' VERSION.dat | cut -d '=' -f 2)"
  PATCH="$(grep '^PATCH=' VERSION.dat | cut -d '=' -f 2)"
  PRE_RELEASE_TAG="$(grep '^PRE_RELEASE_TAG=' VERSION.dat | cut -d '=' -f 2)"
  VERSION="${MAJOR}.${MINOR}.${PATCH}"

  if [ "${PRE_RELEASE_TAG}" = "" ]; then
    echo "${VERSION}"
  else
    echo "${VERSION}.${PRE_RELEASE_TAG}"
  fi
}

HEAD_COMMIT=$(git rev-parse HEAD)
HEAD_COMMIT_SHORT=${HEAD_COMMIT:0:10}
echo "HEAD_COMMIT_SHORT: ${HEAD_COMMIT_SHORT}"

# OPENSSL_VERSION=3.0.9
if ${#} -gt 0; then
  OPENSSL_VERSION="${1}"
else
  OPENSSL_VERSION="$(print_version_str)"
fi

OPENSSL_DIR_NAME="openssl-${OPENSSL_VERSION}-fips-debug-${HEAD_COMMIT_SHORT}"
# Set the directory manually to test a pull-request.
# OPENSSL_DIR_NAME="openssl-${OPENSSL_VERSION}-fips-debug-6bcb6d297e-plus-pr-21519"
# OPENSSL_DIR_NAME="openssl-${OPENSSL_VERSION}-fips-debug-06a0d40322-issue-20657"
OPENSSL_PREFIX="${HOME}/.local/${OPENSSL_DIR_NAME}"
echo "OPENSSL_PREFIX: ${OPENSSL_PREFIX}"

# The no-docs option is available in OpenSSL 3.2 and later versions.
# https://github.com/openssl/openssl/pull/21240
# https://github.com/openssl/openssl/commit/956b4c75dc3f8710bf7b4e1cf01b4ef6d5ca2b45
configure_args_extra=''
if grep -q '"docs",' Configure; then
  configure_args_extra='no-docs'
fi

# exit

./Configure \
  --prefix="${OPENSSL_PREFIX}" \
  --libdir=lib \
  shared \
  enable-fips \
  enable-trace \
  "${configure_args_extra}" \
  -O0 -g3 -ggdb3 -gdwarf-5

# exit

make -j"$(nproc)"
make -j"$(nproc)" install

LD_LIBRARY_PATH="${OPENSSL_PREFIX}/lib/" \
  "${OPENSSL_PREFIX}/bin/openssl" version
