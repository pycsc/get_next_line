#!/usr/bin/env bash
# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    run_acceptance.sh                                      +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                     +########+             #
#                                                           +###+              #
#    Created: 2026/11/17 19:43:17 by lucas                   ##+               #
#    Updated: 2026/11/17 20:10:50 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

set -euo pipefail
IFS=$'\n\t'

TEST_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEST_TMP="$(mktemp -d "${TMPDIR:-/tmp}/gnl-acceptance.XXXXXX")"
readonly TEST_ROOT TEST_TMP
readonly TEST_CFLAGS="-std=c11 -Wall -Wextra -Werror -Wpedantic"
readonly -a TEST_FLAGS=(-std=c11 -Wall -Wextra -Werror -Wpedantic)
trap 'make -C "${TEST_ROOT}" fclean >/dev/null; \
  rm -rf "${TEST_TMP}"' EXIT ERR INT TERM

test_variant()
{
  local target="$1"
  local size="$2"
  local suffix="$3"

  make -C "${TEST_ROOT}" fclean >/dev/null
  make -C "${TEST_ROOT}" "${target}" \
    CFLAGS="${TEST_CFLAGS}" BUFFER_SIZE="${size}" >/dev/null
  cc "${TEST_FLAGS[@]}" "${TEST_ROOT}/tests/test_e2e.c" \
    "${TEST_ROOT}/libgnl.a" -o "${TEST_TMP}/gnl_${suffix}"
  "${TEST_TMP}/gnl_${suffix}" "${TEST_ROOT}/tests/sample.txt" \
    >"${TEST_TMP}/${suffix}.out"
  cmp "${TEST_ROOT}/tests/sample.txt" "${TEST_TMP}/${suffix}.out"
}

ulimit -t 20
for size in 1 42 9999; do
  test_variant all "${size}" "mandatory_${size}"
  test_variant bonus "${size}" "bonus_${size}"
  cc "${TEST_FLAGS[@]}" "${TEST_ROOT}/tests/test_acceptance_bonus.c" \
    "${TEST_ROOT}/libgnl.a" -o "${TEST_TMP}/bonus_state_${size}"
  "${TEST_TMP}/bonus_state_${size}" \
    "${TEST_ROOT}/tests/sample.txt" "${TEST_ROOT}/tests/single.txt"
done
