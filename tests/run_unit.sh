#!/usr/bin/env bash
# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    run_unit.sh                                            +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                     +########+             #
#                                                           +###+              #
#    Created: 2026/11/17 19:38:03 by lucas                   ##+               #
#    Updated: 2026/11/17 19:39:08 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

set -euo pipefail
IFS=$'\n\t'

readonly TEST_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
readonly TEST_TMP="$(mktemp -d "${TMPDIR:-/tmp}/gnl-unit.XXXXXX")"
trap 'rm -rf "${TEST_TMP}"' EXIT ERR INT TERM

cc -std=c11 -Wall -Wextra -Werror -Wpedantic \
  -fsanitize=address,undefined \
  "${TEST_ROOT}/tests/test_unit.c" \
  "${TEST_ROOT}/get_next_line_utils.c" \
  "${TEST_ROOT}/ft_calloc.c" \
  "${TEST_ROOT}/ft_bzero.c" \
  "${TEST_ROOT}/ft_memset.c" \
  -o "${TEST_TMP}/test_unit"
ulimit -t 5
"${TEST_TMP}/test_unit"
