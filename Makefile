# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yciftci <yciftci@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 16:02:00 by yciftci           #+#    #+#              #
#    Updated: 2023/05/20 15:43:42 by yciftci          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@gcc *.c -Wall -Wextra -Werror -o philo
	@echo ✅

datarace:
	@gcc *.c -o philo -pthread -fsanitize=thread

fclean:
	@rm -rf philo
	@echo 🗑️

re:
	@make fclean
	@make all

norm:
	@norminette
