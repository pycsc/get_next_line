#!/usr/bin/env bash
# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    run_e2e.sh                                             +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                     +########+             #
#                                                           +###+              #
#    Created: 2026/11/17 19:41:55 by lucas                   ##+               #
#    Updated: 2026/11/17 20:10:50 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

set -euo pipefail
IFS=$'\n\t'

TEST_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEST_TMP="$(mktemp -d "${TMPDIR:-/tmp}/gnl-e2e.XXXXXX")"
readonly TEST_ROOT TEST_TMP
readonly TEST_CFLAGS="-std=c11 -Wall -Wextra -Werror -Wpedantic"
readonly -a TEST_FLAGS=(-std=c11 -Wall -Wextra -Werror -Wpedantic)
trap 'make -C "${TEST_ROOT}" fclean >/dev/null; \
  rm -rf "${TEST_TMP}"' EXIT ERR INT TERM
ulimit -t 10

make -C "${TEST_ROOT}" CFLAGS="${TEST_CFLAGS}" BUFFER_SIZE=1
cc "${TEST_FLAGS[@]}" "${TEST_ROOT}/tests/test_e2e.c" \
  "${TEST_ROOT}/libgnl.a" -o "${TEST_TMP}/gnl"
"${TEST_TMP}/gnl" "${TEST_ROOT}/tests/sample.txt" \
  >"${TEST_TMP}/mandatory.out"
cmp "${TEST_ROOT}/tests/sample.txt" "${TEST_TMP}/mandatory.out"

make -C "${TEST_ROOT}" fclean >/dev/null
make -C "${TEST_ROOT}" bonus CFLAGS="${TEST_CFLAGS}" BUFFER_SIZE=1
cc "${TEST_FLAGS[@]}" "${TEST_ROOT}/tests/test_e2e.c" \
  "${TEST_ROOT}/libgnl.a" -o "${TEST_TMP}/gnl_bonus"
"${TEST_TMP}/gnl_bonus" "${TEST_ROOT}/tests/sample.txt" \
  >"${TEST_TMP}/bonus.out"
cmp "${TEST_ROOT}/tests/sample.txt" "${TEST_TMP}/bonus.out"
