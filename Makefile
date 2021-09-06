# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoyoo <yoyoo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/06 13:05:42 by yoyoo             #+#    #+#              #
#    Updated: 2021/09/06 16:19:44 by yoyoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -O2
LIBFT			= libft.a
MINILIBX		= libmlx.a

SRCS_DIR		= ./src
SRCS			= $(addprefix $(SRCS_DIR)/, check_argv.c color.c event.c fractol.c init.c main.c put_pixel.c)
OBJS_DIR		= ./obj
OBJS			= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
NAME			= fractol


B_SRCS_DIR		= ./bonus
B_SRCS			= $(addprefix $(B_SRCS_DIR)/, main.c)
B_OBJS			= $(addprefix $(OBJS_DIR)/, $(notdir $(B_SRCS:.c=.o)))
B_NAME			= fractol_bonus

# mandatory
all				: $(LIBFT) $(OBJS_DIR) $(NAME) $(MINILIBX) $(SRCS_DIR)/fractol.h

$(OBJS_DIR)     :
	@mkdir $(OBJS_DIR)

vpath %.c $(SRCS_DIR)

$(LIBFT)        :
	@make -C libft

$(OBJS_DIR)/%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(MINILIBX)		:
	@make -C minilibX

$(NAME)			: $(OBJS) $(MINILIBX)
	@$(CC) $(CFLAGS) -framework OpenGl -framework Appkit -l ft -L ./libft ./minilibX/$(MINILIBX) $(OBJS) -o $@ 
	@printf "   \033[0;32m[fractol build success❄️]]\n\e[0m"


bonus			: all

clean			:
	@make clean -C libft
	@make clean -C minilibX
	@rm -f $(OBJS)
	@printf "   \033[0;32m[execute clean🥡]\n\e[0m"

fclean			: clean
	@make fclean -C libft
	@rm -f $(NAME) 
	@rm -rf $(OBJS_DIR)
	@printf "   \033[0;32m[execute fclean🚽]\n\e[0m"

re				: fclean all

.PHONY			: all clean fclean re bonus
