<<<<<<< HEAD
NAME		= ft_irc

CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98
RM		= rm -rf
NAME	= ircserv

INCS_DIR	= ./inc/
MAIN_INC	= -I$(INCS_DIR)
INCS		= $(shell find $(INCS_DIR) -type f -name "*.hpp")

SRCS_DIR 	= ./src/
SRCS		= $(shell find $(SRCS_DIR) -type f -name "*.cpp")

OBJS_DIR	= ./obj/
OBJS		= $(SRCS:$(SRCS_DIR)%.cpp=$(OBJS_DIR)%.o)

_CLEAR		= \033[0K\r\c
_OK			= [\033[32mOK\033[0m]
_CLEAN		= [\033[31mCLEAN\033[0m]

$(OBJS_DIR)%.o	: $(SRCS_DIR)%.cpp
			@mkdir -p $(OBJS_DIR)
			@echo "[..] compiling $*.cpp\r\c"
			@$(CC) $(MAIN_INC) -c $< -o $@
			@echo "$(_CLEAR)"

SRCS := ./src/main.cpp \
		./src/socket.cpp \
		./src/select.cpp \
		./src/utils.cpp \

OBJS := $(SRCS:%.cpp=%.o)

$(NAME): $(OBJS)
		@echo "compiler>>>>>>>>" 
		@$(CC) $(CFLAGES) $(OBJS) -o $@ 
		@echo "IRC done!"

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
		@$(CC) $(FLAGS) -o $@ $(OBJS) $(MAIN_INC)
		@echo "$(_OK) $(NAME) compiled"

clean:
	@$(RM) $(OBJS_DIR)


fclean: clean
	@$(RM) $(NAME)
	@echo "$(_CLEAN) $(NAME) Executable removed!"

re: fclean all

.PHONY : clean fclean re