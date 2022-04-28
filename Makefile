# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xuwang <xuwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 13:28:29 by xuwang            #+#    #+#              #
#    Updated: 2022/04/28 11:55:25 by xuwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CC	= clang++

CFLAGES = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3
#CFLAGES = -std=c++98 -fsanitize=address -g3

IFLAGES =  -I./inc

SRCS := ./src/main.cpp \
		./src/socket.cpp \
		./src/select.cpp \
		./src/request.cpp \
		./src/utils.cpp

OBJS := $(SRCS:%.cpp=%.o)

$(NAME): $(OBJS)
		@printf "$(CL_LINE)compiler>>>>>>>> $(NONE)\r"
		$(CC) $(CFLAGES) $(OBJS) -o $@ 
		@echo "webserv done!"
		

all: $(NAME)

clean:
		@rm -rf $(OBJS)
		@echo "Delete>>>>>>"

fclean:clean
		@rm -rf $(NAME)
		@echo "Delete all>>>>>>"

%.o: %.cpp
		$(CC) $(CFLAGES) $(IFLAGES) -c $< -o $@
		
re: fclean all

.PHONY: all clean fclean re
	
