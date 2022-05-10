NAME = ircserv

CC	= clang++

CFLAGES = -Wall -Wextra -Werror #-std=c++98 -fsanitize=address -g3


IFLAGES =  -I./inc

SRCS := ./src/main.cpp \
		./src/socket.cpp \
		./src/utils.cpp \
		./src/select.cpp \
		./src/user.cpp \
		./src/command.cpp \
		
		

OBJS := $(SRCS:%.cpp=%.o)

$(NAME): $(OBJS)
		@echo "compiler>>>>>>>>" 
		@$(CC) $(CFLAGES) $(OBJS) -o $@ 
		@echo "IRC done!"
		@./$(NAME) 8080 123
		

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
	
