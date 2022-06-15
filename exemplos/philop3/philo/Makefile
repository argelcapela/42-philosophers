NAME 			= philo

SRCS_DIR 		= ./src
OBJS_DIR 		= ./obj
INCLUDES_DIR 	= ./includes

CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror $(LEAKCHECK)
LEAKCHECK 		= -fsanitize=address
LFLAGS 			= -lpthread
IFLAGS			= -I$(INCLUDES_DIR)

RM 				= rm -f
NORM			= norminette

INCLUDES_FILES 	= philosophers.h

INCLUDES 		= $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# **************************************************************************** #
#                                 MANDATORY                                    #
# **************************************************************************** #

SRCS = 				philosophers.c \
					lifecicle.c \
					threads.c \
					utils.c

OBJS 			= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

# **************************************************************************** #
#                                   MAKE                                       #
# **************************************************************************** #

$(NAME): 		$(OBJS) $(INCLUDES)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS) $(IFLAGS)

all: 			$(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
				@mkdir -p $(OBJS_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

.PHONY:			all bonus

# **************************************************************************** #
#                                   CLEAN                                      #
# **************************************************************************** #

clean:
				@$(RM) $(OBJS)

fclean: 		clean
				@$(RM) $(NAME)
				@rm -rf $(OBJS_DIR)

re: 			fclean all

.PHONY:			clean fclean re

# **************************************************************************** #
#                                NORMINETTE                                    #
# **************************************************************************** #

norm:
				@$(NORM) $(SRCS_DIR)/*.c $(INCLUDES_DIR)/*.h

.PHONY:			norm
