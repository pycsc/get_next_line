#!/usr/bin/env bash
# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    run_smoke.sh                                           +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                     +########+             #
#                                                           +###+              #
#    Created: 2026/11/17 19:45:05 by lucas                   ##+               #
#    Updated: 2026/11/17 20:10:50 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

set -euo pipefail
IFS=$'\n\t'

TEST_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TEST_TMP="$(mktemp -d "${TMPDIR:-/tmp}/gnl-smoke.XXXXXX")"
readonly TEST_ROOT TEST_TMP
trap 'rm -rf "${TEST_TMP}"' EXIT ERR INT TERM

cc -std=c11 -Wall -Wextra -Werror -Wpedantic \
  "${TEST_ROOT}/tests/test_e2e.c" \
  "${TEST_ROOT}/get_next_line.c" \
  "${TEST_ROOT}/get_next_line_utils.c" \
  "${TEST_ROOT}/ft_calloc.c" \
  "${TEST_ROOT}/ft_bzero.c" \
  "${TEST_ROOT}/ft_memset.c" \
  -o "${TEST_TMP}/gnl_smoke"
ulimit -t 5
"${TEST_TMP}/gnl_smoke" "${TEST_ROOT}/tests/single.txt" \
  >"${TEST_TMP}/smoke.out"
cmp "${TEST_ROOT}/tests/single.txt" "${TEST_TMP}/smoke.out"
