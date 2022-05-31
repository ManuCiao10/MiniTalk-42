NAME		= client server

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCS 		= client.c server.c
				 
OBJS		= $(SRCS:.c=.o)

all:	$(NAME)

clean:
			@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
