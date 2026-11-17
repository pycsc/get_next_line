/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_e2e.c                                            +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/11/17 19:41:55 by lucas                  ##+              */
/*    Updated: 2026/11/17 19:42:30 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static int write_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (fputs(line, stdout) == EOF)
		{
			free(line);
			return (4);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int	fd;
	int	status;

	if (argc != 2)
		return (2);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (3);
	status = write_lines(fd);
	if (close(fd) != 0)
		return (5);
	return (status);
}
