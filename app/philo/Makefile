#****************************************************************************#
#                            COMPILER & FLAGS                                #
#****************************************************************************#
.PHONY: all clean fclean re
CC =            gcc
CFLAGS = 		-Wall -Wextra -Werror -ggdb3
PTHFLAG =		-pthread
RM =            rm -rfd
SANITIZE =

#****************************************************************************#
#                                MANDATORY                                   #
#****************************************************************************#
SRCS_DIR =   	./srcs
OBJS_DIR =   	.objs
HEADER_DIR =   ./$(SRCS_DIR)
HEADER =		$(HEADER_DIR)/_philo.h
NAME =			philo

SRCS_FILES =	1_utils.c \
				2_time.c \
				3_threads_mutexes.c \
				4_routine.c \
				5_monitor.c \
				6_init.c \
				7_main.c \
				8_exit.c

SRCS = 			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS =          $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	$(CC) -I$(HEADER_DIR) $(CFLAGS) -c $< -o $@ $(PTHFLAG) $(SANITIZE)

all:	$(NAME)

$(NAME):	$(OBJS_DIR) $(OBJS) $(HEADER)
	$(CC) -I$(HEADER_DIR) $(CFLAGS) $(OBJS) -o $(NAME) $(PTHFLAG) $(SANITIZE)
	@echo -e "\e[1;32mMANDATORY COMPILED SUCCESFULY!\e[0m"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)
	@echo -e "\e[1;32mMANDATORY CLEAN EXECUTED SUCCESFULY!\e[0m"

fclean:	clean
	find -name '$(NAME)' -delete
	@echo -e "\e[1;32mMANDATORY FCLEAN EXECUTED SUCCESFULY!\e[0m"

re:
	@make fclean && make all
	@echo -e "\e[1;32mMANDATORY RE EXECUTED SUCCESFULY!\e[0m"
