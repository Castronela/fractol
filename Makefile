SRCS	= main.c color.c hooks.c math.c mlx_render.c utils.c
OBJS	= $(SRCS:.c=.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror #-Ofast
LEAKS	= #-L../../LeakSanitizer -llsan
RM		= rm -rf

NAME	= fractol

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LEAKS) -L. -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $(LEAKS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all