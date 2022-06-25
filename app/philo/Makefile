# Config

.PHONY: all clean fclean re
CC =            clang
CFLAGS = 		-Wall -Wextra -Werror -ggdb3
PTHFLAG =		-pthread
AR =            ar -rcs
RM =            rm -rfd


# Mandatory

SRCS_DIR =   	./
OBJS_DIR =   	.objs
HEADER_DIR =   ./$(SRCS_DIR)
HEADER =		$(HEADER_DIR)/philo.h
NAME =			philo

SRCS_FILES =	1_main.c \
				2_routine.c \
				3_utils_1.c \
				4_utils_2.c

SRCS = 			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS =          $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	$(CC) -I$(HEADER_DIR) $(CFLAGS) -c $< -o $@ $(PTHFLAG)

all:	$(NAME)

$(NAME):	$(OBJS_DIR) $(OBJS) $(HEADER)
	$(CC) -I$(HEADER_DIR) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo -e "\e[1;32mMANDATORY COMPILED SUCCESFULY!\e[0m"

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