/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_unit.c                                           +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/11/17 19:38:03 by lucas                  ##+              */
/*    Updated: 2026/11/17 19:38:03 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <assert.h>

static void test_ft_strlen_boundaries_returns_expected_lengths(void)
{
	assert(ft_strlen("") == 0);
	assert(ft_strlen("line\n") == 5);
}

static void test_ft_strchr_states_returns_expected_pointer(void)
{
	const char	*text;

	text = "line\n";
	assert(ft_strchr(text, '\n') == text + 4);
	assert(ft_strchr(text, 'x') == NULL);
	assert(ft_strchr(NULL, 'x') == NULL);
}

static void test_ft_strjoin_inputs_returns_owned_join(void)
{
	char	*left;
	char	*joined;

	left = ft_calloc(3, 1);
	assert(left != NULL);
	left[0] = 'a';
	left[1] = 'b';
	joined = ft_strjoin(left, "cd");
	assert(joined != NULL);
	assert(ft_strlen(joined) == 4);
	assert(ft_strchr(joined, 'd') == joined + 3);
	free(joined);
}

static void test_memory_helpers_ranges_return_expected_bytes(void)
{
	unsigned char	*bytes;

	bytes = ft_calloc(4, 1);
	assert(bytes != NULL && bytes[3] == 0);
	ft_memset(bytes, 0xA5, 4);
	assert(bytes[0] == 0xA5 && bytes[3] == 0xA5);
	ft_bzero(bytes + 1, 2);
	assert(bytes[0] == 0xA5 && bytes[1] == 0);
	assert(bytes[2] == 0 && bytes[3] == 0xA5);
	free(bytes);
}

int main(void)
{
	test_ft_strlen_boundaries_returns_expected_lengths();
	test_ft_strchr_states_returns_expected_pointer();
	test_ft_strjoin_inputs_returns_owned_join();
	test_memory_helpers_ranges_return_expected_bytes();
	return (0);
}
