#!/usr/bin/env bash
# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    run_performance.sh                                     +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                     +########+             #
#                                                           +###+              #
#    Created: 2026/11/17 19:44:24 by lucas                   ##+               #
#    Updated: 2026/11/17 19:44:24 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

set -euo pipefail
IFS=$'\n\t'

readonly TEST_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
readonly TEST_TMP="$(mktemp -d "${TMPDIR:-/tmp}/gnl-performance.XXXXXX")"
trap 'rm -rf "${TEST_TMP}"' EXIT ERR INT TERM

awk 'BEGIN { for (i = 0; i < 20000; i++) printf "%064d\n", i }' \
  >"${TEST_TMP}/fixture.txt"
cc -std=c11 -O2 -Wall -Wextra -Werror -Wpedantic \
  -D BUFFER_SIZE=4096 \
  "${TEST_ROOT}/tests/test_performance.c" \
  "${TEST_ROOT}/get_next_line.c" \
  "${TEST_ROOT}/get_next_line_utils.c" \
  "${TEST_ROOT}/ft_calloc.c" \
  "${TEST_ROOT}/ft_bzero.c" \
  "${TEST_ROOT}/ft_memset.c" \
  -o "${TEST_TMP}/test_performance"
ulimit -t 5
"${TEST_TMP}/test_performance" "${TEST_TMP}/fixture.txt"
