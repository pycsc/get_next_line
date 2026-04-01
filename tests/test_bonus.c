/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    test_bonus.c                                          +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/01 10:50:44 by lucas                  ##+              */
/*    Updated: 2026/04/01 10:50:44 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*l1;
	char	*l2;

	fd1 = open("tests/sample.txt", O_RDONLY);
	fd2 = open("tests/sample.txt", O_RDONLY);
	l1 = get_next_line(fd1);
	l2 = get_next_line(fd2);
	printf("fd1 line1: [%s]", l1);
	printf("fd2 line1: [%s]", l2);
	free(l1);
	free(l2);
	l1 = get_next_line(fd1);
	l2 = get_next_line(fd2);
	printf("fd1 line2: [%s]", l1);
	printf("fd2 line2: [%s]", l2);
	free(l1);
	free(l2);
	l1 = get_next_line(fd1);
	printf("fd1 line3: [%s]", l1);
	free(l1);
	l1 = get_next_line(fd1);
	printf("fd1 eof: %s\n", l1 == NULL ? "NULL" : "ERROR");
	close(fd1);
	close(fd2);
	return (0);
}
