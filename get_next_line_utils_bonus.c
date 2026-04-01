/* ************************************************************************** */
/*                                                                            */
/*                                                           +#               */
/*    get_next_line_utils_bonus.c                           +##               */
/*                                                        +###+               */
/*    By: lucas <lucas@tsiaraso.com>                  +########+              */
/*                                                          +###+             */
/*    Created: 2026/04/01 10:50:44 by lucas                  ##+              */
/*    Updated: 2026/04/01 10:50:44 by lucas                 #+                */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len1;
	size_t	i;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	res = malloc(len1 + ft_strlen(s2) + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	free(s1);
	return (res);
}
