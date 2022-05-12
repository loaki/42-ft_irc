# COMPILATION
CC		= clang++
CFLAGS 	= -Wall -Wextra -Werror -std=c++98 #-O2 #-fsanitize=address -g3
IFLAGS 	= -I./inc -I./inc/cmd

# DIRECTORIES
BUILD 			:= .build
SRC_DIR 		:= src
OBJ_DIR 		:= $(BUILD)/obj
SUB_DIR			:= command
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))


# FILES
NAME			:= ircserv
SRC				:= main.cpp \
				   socket.cpp \
				   utils.cpp \
				   select.cpp \
				   user.cpp \
				   command.cpp \
				   invoker.cpp
SUB_SRC			:= ping.cpp \
				   nick.cpp
SRC				+= $(addprefix command/, $(SUB_SRC))

OBJ				:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)


# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m


# MAKEFILE
$(NAME): $(OBJ)
	@printf "$(CL_LINE)"
	@echo "[1 / 1] - $(B_MAGENTA)$@$(NONE)"
	@$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo "$(B_GREEN)Compilation done !$(NONE)"

all: $(NAME)

clean:
	@rm -Rf $(BUILD)
	@echo "$(B_RED)$(BUILD)$(NONE): $(B_GREEN)Delete$(NONE)"

fclean: clean
	@rm -Rf $(NAME)
	@echo "$(B_RED)$(NAME)$(NONE): $(B_GREEN)Delete$(NONE)"

re: fclean all

debug:
	@echo SRC = $(SRC)
	@echo OBJ = $(OBJ)

.PHONY: all clean fclean re debug

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp | $(BUILD)
	@printf "$(CL_LINE)Compiling srcs object : $(B_CYAN)$< $(NONE)...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@