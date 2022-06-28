# Config

.PHONY: all clean fclean re
CC =            clang
CFLAGS = 		-Wall -Wextra -Werror -ggdb3
PTHFLAG =		-pthread
RM =            rm -rfd

# Bonus

SRCS_DIR =   	./srcs_bonus
OBJS_DIR =   	$(SRCS_DIR)/.objects_bonus
HEADER_DIR =   ./$(SRCS_DIR)
HEADER =		$(HEADER_DIR)/_philosophers_bonus.h
NAME =			philo_bonus

SRCS_FILES =	1_utils_bonus.c \
				2_time_bonus.c \
				3_processes_bonus.c \
				4_routine_bonus.c \
				5_init_bonus.c \
				6_main_bonus.c \
				7_exit_bonus.c

SRCS = 			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS =          $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	$(CC) -I$(HEADER_DIR) $(CFLAGS) -c $< -o $@ $(PTHFLAG)

all:	$(NAME)

$(NAME):	$(OBJS_DIR) $(OBJS) $(HEADER)
	$(CC) -I$(HEADER_DIR) $(CFLAGS) $(OBJS) -o $(NAME) $(PTHFLAG)
	@echo -e "\e[1;32mBONUS COMPILED SUCCESFULY!\e[0m"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)
	@echo -e "\e[1;32mCLEAN EXECUTED SUCCESFULY!\e[0m"

fclean:	clean
	find -name '$(NAME)' -delete
	@echo -e "\e[1;32mFCLEAN EXECUTED SUCCESFULY!\e[0m"

re:
	@make fclean && make all
	@echo -e "\e[1;32mRE EXECUTED SUCCESFULY!\e[0m"
