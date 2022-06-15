# Config

.PHONY: all clean fclean re
CC =            clang
CFLAGS = 		-Wall -Wextra -Werror -ggdb3
AR =            ar -rcs
RM =            rm -rfd


# Bonus

SRCS_DIR =   	./
OBJS_DIR =   	$(SRCS_DIR)/.objs
HEADER_DIR =   ./
HEADER =		$(HEADER_DIR)/philo_bonus.h
NAME =			philo_bonus

SRCS_FILES =	philo_bonus.c

SRCS = 			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS =          $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	$(CC) -I$(HEADER_DIR) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS_DIR) $(OBJS) $(HEADER)
	$(CC) -I$(HEADER_DIR) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1;32mMANDATORY COMPILED SUCCESFULY!\033[0m"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)
	@echo "\033[1;32mCLEAN EXECUTED SUCCESFULY!\033[0m"

fclean:	clean
	find -name '$(NAME)' -delete
	@echo "\033[1;32mFCLEAN EXECUTED SUCCESFULY!\033[0m"

re:
	@make fclean && make all
	@echo "\033[1;32mRE EXECUTED SUCCESFULY!\033[0m"


# Test

t:	$(NAME)
	@./$(NAME)

seg:	$(NAME)
	@valgrind --track-origins=yes ./$(NAME)

leak:	$(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./$(NAME)
