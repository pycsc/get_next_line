# **************************************************************************** #
#                                                                              #
#                                                            +#                #
#    Makefile                                               +##                #
#                                                         +###+                #
#    By: lucas <lucas@tsiaraso.com>                   +########+               #
#                                                           +###+              #
#    Created: 2026/04/23 20:00:00 by lucas                   ##+               #
#    Updated: 2026/04/23 20:00:00 by lucas                  #+                 #
#                                                                              #
# **************************************************************************** #

NAME		= libgnl.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
ifdef BUFFER_SIZE
CFLAGS		+= -D BUFFER_SIZE=$(BUFFER_SIZE)
endif

SRCS		= get_next_line.c get_next_line_utils.c \
					ft_calloc.c ft_bzero.c ft_memset.c
OBJS		= $(SRCS:.c=.o)

SRCS_BONUS	= get_next_line_bonus.c get_next_line_utils_bonus.c \
							ft_calloc.c ft_bzero.c ft_memset.c
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
