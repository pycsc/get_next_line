/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_performance.c                                    +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/11/17 19:44:24 by lucas                  ##+              */
/*    Updated: 2026/11/17 19:44:24 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <assert.h>
#include <fcntl.h>
#include <time.h>

#define EXPECTED_LINES 20000
#define CPU_BUDGET_SECONDS 2.0

static size_t consume_file(const char *path)
{
	char	*line;
	int		fd;
	size_t	count;

	fd = open(path, O_RDONLY);
	assert(fd >= 0);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	assert(close(fd) == 0);
	return (count);
}

static void test_gnl_bounded_fixture_completes_within_cpu_budget(char *path)
{
	clock_t	start;
	double	elapsed;
	size_t	count;

	start = clock();
	count = consume_file(path);
	elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
	assert(count == EXPECTED_LINES);
	assert(elapsed < CPU_BUDGET_SECONDS);
}

int main(int argc, char **argv)
{
	assert(argc == 2);
	test_gnl_bounded_fixture_completes_within_cpu_budget(argv[1]);
	return (0);
}
