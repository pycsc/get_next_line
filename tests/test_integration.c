/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_integration.c                                    +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/11/17 19:40:56 by lucas                  ##+              */
/*    Updated: 2026/11/17 19:40:56 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <assert.h>
#include <fcntl.h>
#include <string.h>

static void assert_file_line_equals(int fd, const char *expected)
{
	char	*line;

	line = get_next_line(fd);
	assert(line != NULL);
	assert(strcmp(line, expected) == 0);
	free(line);
}

static void test_gnl_regular_file_returns_exact_sequence(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	assert(fd >= 0);
	assert_file_line_equals(fd, "Hello World\n");
	assert_file_line_equals(fd, "This is line 2\n");
	assert_file_line_equals(fd, "Line 3 no newline");
	assert(get_next_line(fd) == NULL);
	assert(close(fd) == 0);
}

static void test_gnl_single_line_file_returns_line_then_eof(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	assert(fd >= 0);
	assert_file_line_equals(fd, "single\n");
	assert(get_next_line(fd) == NULL);
	assert(close(fd) == 0);
}

static void test_gnl_empty_file_returns_null(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	assert(fd >= 0);
	assert(get_next_line(fd) == NULL);
	assert(close(fd) == 0);
}

int main(int argc, char **argv)
{
	assert(argc == 4);
	test_gnl_regular_file_returns_exact_sequence(argv[1]);
	test_gnl_single_line_file_returns_line_then_eof(argv[2]);
	test_gnl_empty_file_returns_null(argv[3]);
	return (0);
}
