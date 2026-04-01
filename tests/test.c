/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test.c                                                +##               */
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
	int		i;

	fd = open("tests/sample.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: [%s]", i, line);
		free(line);
		i++;
	}
	close(fd);
	printf("\n--- Test invalid fd ---\n");
	line = get_next_line(-1);
	printf("fd -1: %s\n", line == NULL ? "NULL (correct)" : "ERROR");
	printf("\n--- Test empty file ---\n");
	fd = open("tests/empty.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("empty: %s\n", line == NULL ? "NULL (correct)" : "ERROR");
	close(fd);
	return (0);
}
