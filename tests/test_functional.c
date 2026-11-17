/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_functional.c                                     +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/11/17 19:40:05 by lucas                  ##+              */
/*    Updated: 2026/11/17 19:40:05 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <assert.h>
#include <string.h>

static void assert_line_equals(int fd, const char *expected)
{
	char	*line;

	line = get_next_line(fd);
	assert(line != NULL);
	assert(strcmp(line, expected) == 0);
	free(line);
}

static void test_gnl_multiline_stream_returns_lines_in_order(void)
{
	int	fds[2];

	assert(pipe(fds) == 0);
	assert(write(fds[1], "alpha\nbeta", 10) == 10);
	assert(close(fds[1]) == 0);
	assert_line_equals(fds[0], "alpha\n");
	assert_line_equals(fds[0], "beta");
	assert(get_next_line(fds[0]) == NULL);
	assert(close(fds[0]) == 0);
}

static void test_gnl_empty_stream_returns_null(void)
{
	int	fds[2];

	assert(pipe(fds) == 0);
	assert(close(fds[1]) == 0);
	assert(get_next_line(fds[0]) == NULL);
	assert(close(fds[0]) == 0);
}

static void test_gnl_invalid_descriptor_returns_null(void)
{
	assert(get_next_line(-1) == NULL);
}

int main(void)
{
	test_gnl_multiline_stream_returns_lines_in_order();
	test_gnl_empty_stream_returns_null();
	test_gnl_invalid_descriptor_returns_null();
	return (0);
}
