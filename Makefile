# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xuwang <xuwang@42.student.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 13:28:29 by xuwang            #+#    #+#              #
#    Updated: 2022/04/29 16:05:59 by xuwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = irc

CC	= clang++

CFLAGES = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3


IFLAGES =  -I./inc

SRCS := ./src/main.cpp \
		./src/socket.cpp \
		./src/select.cpp \
		./src/utils.cpp

OBJS := $(SRCS:%.cpp=%.o)

$(NAME): $(OBJS)
		@echo "compiler>>>>>>>>" 
		@$(CC) $(CFLAGES) $(OBJS) -o $@ 
		@echo "IRC done!"
		

all: $(NAME)

clean:
		@rm -rf $(OBJS)
		@echo "Delete"

fclean:clean
		@rm -rf $(NAME)
		@echo "Delete all"

%.o: %.cpp
		@$(CC) $(CFLAGES) $(IFLAGES) -c $< -o $@
		
re: fclean all

.PHONY: all clean fclean re
	
