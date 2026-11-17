/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_acceptance_bonus.c                               +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/11/17 19:43:17 by lucas                  ##+              */
/*    Updated: 2026/11/17 19:43:17 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"
#include <assert.h>
#include <fcntl.h>
#include <string.h>

static void assert_line_equals(int fd, const char *expected)
{
	char	*line;

	line = get_next_line(fd);
	assert(line != NULL);
	assert(strcmp(line, expected) == 0);
	free(line);
}

static void test_bonus_interleaved_files_keep_independent_state(char **paths)
{
	int	first;
	int	second;

	first = open(paths[1], O_RDONLY);
	second = open(paths[2], O_RDONLY);
	assert(first >= 0 && second >= 0);
	assert_line_equals(first, "Hello World\n");
	assert_line_equals(second, "single\n");
	assert_line_equals(first, "This is line 2\n");
	assert(get_next_line(second) == NULL);
	assert_line_equals(first, "Line 3 no newline");
	assert(get_next_line(first) == NULL);
	assert(close(first) == 0);
	assert(close(second) == 0);
}

int main(int argc, char **argv)
{
	assert(argc == 3);
	test_bonus_interleaved_files_keep_independent_state(argv);
	return (0);
}
