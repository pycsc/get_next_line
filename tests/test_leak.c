/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_leak.c                                           +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/01 10:50:44 by lucas                  ##+              */
/*    Updated: 2026/04/01 10:50:44 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tests/sample.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
		free(line);
	close(fd);
	fd = open("tests/empty.txt", O_RDONLY);
	line = get_next_line(fd);
	close(fd);
	return (0);
}
